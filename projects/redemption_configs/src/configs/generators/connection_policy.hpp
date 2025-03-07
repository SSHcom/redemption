/*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*   Product name: redemption, a FLOSS RDP proxy
*   Copyright (C) Wallix 2010-2015
*   Author(s): Jonathan Poelen
*/

#pragma once

#include "configs/attributes/spec.hpp"
#include "configs/generators/utils/spec_writer.hpp"
#include "configs/generators/utils/write_template.hpp"
#include "configs/generators/utils/names.hpp"
#include "configs/generators/sesman_default_map.hpp"
#include "configs/enumeration.hpp"



#include "configs/generators/python_spec.hpp"
#include "utils/sugar/algostring.hpp"

#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <cerrno>
#include <cstring>


namespace cfg_generators {

namespace connection_policy_writer {

using namespace cfg_attributes;

namespace json
{
    namespace impl
    {
        using python_spec_writer::impl::exprio;


        using python_spec_writer::impl::stringize_integral;

        inline std::string stringize_bool(bool x)
        {
            return x ? "true" : "false";
        }

        inline exprio stringize_bool(cpp::expr e)
        {
            return {e.value};
        }

        struct io_quoted
        {
            char const * s;

            io_quoted(char const * s) : s(s) {}
            io_quoted(std::string const & str) : s(str.c_str()) {}

            friend std::ostream & operator<<(std::ostream & out, io_quoted const & q)
            {
                if (auto s = q.s) {
                    for (; *s; ++s) {
                        switch (*s) {
                            case '\n':
                                if (s[1]) {
                                    out << "\\n";
                                }
                                break;
                            case '\t':
                                out << "\\t";
                                break;
                            case '"':
                            case '\\':
                                out << '\\' << *s;
                                break;
                            default:
                                out << *s;
                        }
                    }
                }
                return out;
            }
        };

        inline exprio quoted(cfg_attributes::cpp::expr e) { return {e.value}; }
        template<class T> static io_quoted quoted(T const & s) { return s; }
        template<unsigned n> static char const* quoted(types::fixed_string<n>) { return ""; }
        // template<class T> static char const * quoted(types::list<T> const &) { return ""; }
    }

    template<class T>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<bool>, T const& x)
    {
        out <<
            "          \"type\": \"bool\",\n"
            "          \"default\": " << impl::stringize_bool(x) << ",\n"
        ;
    }

    template<class T>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<std::string>, T const& s)
    {
        out <<
            "          \"type\": \"string\",\n"
            "          \"default\": \"" << impl::quoted(s) << "\",\n"
        ;
    }

    template<class Int, class T>
    std::enable_if_t<
        std::is_base_of<types::integer_base, Int>::value
        or
        std::is_integral<Int>::value
    >
    write_type(std::ostream& out, type_enumerations& /*enums*/, type_<Int>, T const& i)
    {
        out << "          \"type\": \"integer\",\n";
        if (std::is_unsigned<Int>::value || std::is_base_of<types::unsigned_base, Int>::value) {
            out << "          \"min\": 0,\n";
        }
        out << "          \"default\": " << impl::stringize_integral(i) << ",\n";
    }

    template<class Int, long min, long max, class T>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<types::range<Int, min, max>>, T const& i)
    {
        out <<
            "          \"type\": \"integer\",\n"
            "          \"min\": " << min << ",\n"
            "          \"max\": " << max << ",\n"
            "          \"default\": " << impl::stringize_integral(i) << ",\n"
        ;
    }

    template<class Ratio>
    struct ratio_to_unit;

#define RATIO_TO_MULTIPLICATOR(type, unit) \
    template<> struct ratio_to_unit<type>  \
    { static constexpr char const* value = #unit ; }

    RATIO_TO_MULTIPLICATOR(std::milli, ms);
    RATIO_TO_MULTIPLICATOR(std::centi, cs);
    RATIO_TO_MULTIPLICATOR(std::deci, ds);
    RATIO_TO_MULTIPLICATOR(std::chrono::seconds::period, s);
    RATIO_TO_MULTIPLICATOR(std::chrono::minutes::period, min);
    RATIO_TO_MULTIPLICATOR(std::chrono::hours::period, h);

#undef RATIO_TO_MULTIPLICATOR

    template<class T, class Ratio, class U>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<std::chrono::duration<T, Ratio>>, U const& i)
    {
        out <<
            "          \"type\": \"integer\",\n"
            "          \"min\": 0,\n"
            "          \"default\": " << impl::stringize_integral(i) << ",\n"
            "          \"subtype\": \"duration\",\n"
            "          \"unit\": \"" << ratio_to_unit<Ratio>::value << "\",\n"
        ;
    }

    template<unsigned N, class T>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<types::fixed_binary<N>>, T const& x)
    {
        out <<
            "          \"type\": \"binary\",\n"
            "          \"min\": " << N*2 << ",\n"
            "          \"max\": " << N*2 << ",\n"
            "          \"default\": \"" << io_hexkey{x.c_str(), N} << "\",\n"
        ;
    }

    template<unsigned N, class T>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<types::fixed_string<N>>, T const& x)
    {
        out <<
            "          \"type\": \"string\",\n"
            "          \"maxlen\": " << N << ",\n"
            "          \"default\": \"" << impl::quoted(x) << "\",\n"
        ;
    }

    template<class T>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<types::dirpath>, T const& x)
    {
        out <<
            "          \"type\": \"dirpath\",\n"
            "          \"default\": \"" << impl::quoted(x) << "\",\n"
        ;
    }

    template<class T>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<types::ip_string>, T const& x)
    {
        write_type(out, type_<std::string>{}, x);
    }

    template<class T, class L>
    void write_type(std::ostream& out, type_enumerations& /*enums*/, type_<types::list<T>>, L const& x)
    {
        static_assert(sesman_default_map::python::is_integral_type_v<T>, "not implemented");
        out <<
            "          \"type\": \"integer\",\n"
        ;
        if (std::is_unsigned<T>::value || std::is_base_of<types::unsigned_base, T>::value) {
            out << "          \"min\": 0,\n";
        }
        out <<
            "          \"multivalue\": true,\n"
            "          \"default\": [" << x << "],\n"
        ;
    }

    namespace impl
    {
        // uppercase for first letter and replace '_' by ' '
        struct io_label
        {
            char const* label;

            friend std::ostream & operator<<(std::ostream & out, io_label const & q)
            {
                auto toupper = [](char c){
                    return ('a' <= c && c <= 'z') ? char(c + ('A' - 'a')) : c;
                };

                auto label = q.label;

                out << toupper(label[0]);

                while (*++label) {
                    out << (*label == '_' ? ' ' : *label);
                }

                return out;
            }
        };

        template<class T>
        void write_enum_value(std::ostream& out, type_enumeration const & e, T default_value)
        {
            if (e.flag == type_enumeration::flags) {
                out <<
                    "          \"type\": \"integer\",\n"
                    "          \"min\": 0,\n"
                    "          \"max\": " << e.max() << ",\n"
                    "          \"default\": " << default_value << ",\n"
                    "          \"subtype\": \"bitset\",\n"
                ;
            }
            else {
                out << "          \"type\": \"option\",\n";
                if (e.is_string_parser) {
                    auto& v = e.values[default_value];
                    out << "          \"default\": \"" << (v.alias ? v.alias : v.name) << "\",\n";
                }
                else {
                    out << "          \"default\": " << default_value << ",\n";
                }
            }

            out << "          \"values\": [";
            bool const is_autoinc = (e.flag == type_enumeration::autoincrement);
            char const* prefix = "\n";
            int d = 0;
            for (type_enumeration::Value const & v : e.values) {
                auto f = (1ull << d >> 1);
                if (!(f & e.exclude_flag)) {
                    out << prefix <<
                        "            {\n"
                        "               \"value\": "
                    ;
                    if (e.is_string_parser) {
                        out << '"' << (v.alias ? v.alias : v.name) << '"';
                    }
                    else if (is_autoinc) {
                        out << d;
                    }
                    else {
                        out << f;
                    }
                    out << ",\n"
                        "               \"label\": \"" << io_label{v.name} << "\",\n"
                        "               \"description\": \"" << io_quoted(v.desc ? v.desc : "") << "\"\n"
                        "            }"
                    ;
                    prefix = ",\n";
                }
                ++d;
            }
            out << "\n          ],\n";
        }

        template<class T>
        void write_enum_value(std::ostream& out, type_enumeration_set const & e, T default_value)
        {
            out <<
                "          \"type\": \"option\",\n"
                "          \"default\": \"" << default_value << "\",\n"
                "          \"values\": ["
            ;
            char const* prefix = "\n";
            for (type_enumeration_set::Value const & v : e.values) {
                    out << prefix <<
                        "            {    "
                        "               \"value\": \"" << (v.alias ? v.alias : v.name) << "\",\n"
                        "               \"label\": " << v.val << ",\n"
                        "               \"description\": \"" << io_quoted(v.desc ? v.desc : "") << "\",\n"
                        "            }"
                    ;
                    prefix = ",\n";
            }
            out << "          ],\n";
        }
    }

    template<class T, class E>
    std::enable_if_t<std::is_enum_v<E>>
    write_type(std::ostream& out, type_enumerations& enums, type_<T>, E const& x)
    {
        static_assert(std::is_same<T, E>::value, "incompatible enum type, used connpolicy::set(...)");
        using ll = long long;
        apply_enumeration_for<T>(enums, [&](auto const & e) {
            impl::write_enum_value(out, e, ll{static_cast<std::underlying_type_t<E>>(x)});
        });
    }
}

struct ConnectionPolicyWriterBase
{
    using attribute_name_type = connpolicy::name;

    using categories_t = std::array<std::string, 2>;

    struct PythonSpec
    {
        std::string filename;
        std::ostringstream out;

        PythonSpec(std::string filename)
        : filename(std::move(filename))
        {}
    };
    PythonSpec python_spec;

    struct JsonSpec
    {
        std::ostringstream out;
    };
    JsonSpec json_spec;

    ConnectionPolicyWriterBase(std::string directory_spec, categories_t categories, std::string sesman_map_filename)
    : python_spec{std::move(sesman_map_filename)}
    , categories(std::move(categories))
    , directory_spec(std::move(directory_spec))
    {}

    template<class Pack>
    void evaluate_member(Names const& names, std::string const & section_name, Pack const& infos, type_enumerations& enums)
    {
        if constexpr (is_convertible_v<Pack, connection_policy_t>) {
            auto type = get_type<connpolicy::type_>(infos);
            auto& default_value = get_default<connpolicy::default_>(type, infos);

            std::string const& member_name = get_name<connpolicy::name>(infos);

            this->json_spec.out << "        {\n          \"name\": \"" << member_name << "\",\n";
            json::write_type(this->json_spec.out, enums, type, default_value);

            std::stringstream comments;

            python_spec_writer::write_description(comments, enums, type, infos);
            python_spec_writer::write_type_info(comments, type);
            python_spec_writer::write_enumeration_value_description(comments, enums, type, infos);

            this->python_spec.out << io_prefix_lines{comments.str().c_str(), "# ", "", 0};
            comments.str("");

            auto& connpolicy = get_elem<connection_policy_t>(infos);

            using attr1_t = spec::internal::attr;
            using attr2_t = connpolicy::internal::attr;
            auto attr1 = value_or<spec_attr_t>(infos, spec_attr_t{attr1_t::no_ini_no_gui}).value;
            auto attr2 = connpolicy.spec;

            if (bool(attr1 & attr1_t::advanced_in_gui)
             || bool(attr2 & attr2_t::advanced_in_connpolicy)) {
                comments << "_advanced\n";
                 this->json_spec.out << "          \"advanced\": true,\n";
            }
            if (bool(attr1 & attr1_t::hex_in_gui)
             || bool(attr2 & attr2_t::hex_in_connpolicy)
             || bool(python_spec_writer::attr_hex_if_enum_flag(type, enums))) {
                comments << "_hex\n";
                this->json_spec.out << "          \"prefered_representation\": \"hex\",\n";
            }

            this->python_spec.out << io_prefix_lines{comments.str().c_str(), "#", "", 0};

            this->python_spec.out << member_name << " = ";
            python_spec_writer::write_type(python_spec.out, enums, type, default_value);
            this->python_spec.out << "\n\n";

            {
                std::ostringstream json_description;
                python_spec_writer::write_description(json_description, enums, type, infos);
                this->json_spec.out << "          \"description\": \"" << json::impl::io_quoted(json_description.str()) << "\"";
            }

            this->json_spec.out << "\n        }";

            auto const& section = value_or<connpolicy::section>(
                infos, connpolicy::section{section_name.c_str()});

            if (this->section_names.emplace(section.name).second) {
                this->ordered_section.emplace_back(section.name);
            }

            auto sesman_name = sesman_network_name(infos, names);

            auto s_py = this->python_spec.out.str();
            auto s_json = this->json_spec.out.str();
            for (auto const& file : connpolicy.files) {
                auto& sec = this->file_map[file][section.name];
                sec.python_contains += s_py;
                if (!sec.json_contains.empty()) {
                    sec.json_contains += ",\n";
                }
                sec.json_contains += s_json;
            }

            this->python_spec.out.str("");
            this->json_spec.out.str("");

            auto& buf = this->json_spec.out;
            auto sesman_mem_key = str_concat(section.name, '/', sesman_name, '/', member_name);
            if (!this->sesman_mems.emplace(sesman_mem_key).second) {
                throw std::runtime_error(str_concat("duplicate ", section.name, ' ', member_name));
            }
            auto sesman_type = get_type<sesman::type_>(infos);
            sesman_default_map::python::write_type(buf, sesman_type, get_default(sesman_type, infos));

            auto& file_content = this->sesman_file[section.name];
            update_sesman_contains(file_content, sesman_name, member_name, buf.str());

            if constexpr (is_convertible_v<Pack, sesman::deprecated_names>) {
                for (auto&& old_name : get_elem<sesman::deprecated_names>(infos).names) {
                    update_sesman_contains(file_content, old_name, member_name, "None", "  # Deprecated, for compatibility only.");
                }
            }
            buf.str("");
        }
    }

    static void update_sesman_contains(
        std::string& s,
        std::string const sesman_name,
        std::string const connpolicy_name,
        std::string const value,
        char const* extra = "")
    {
        str_append(s,
                   "        u'", sesman_name, "': (\n"
                   "            '", connpolicy_name, "', ", value, "\n"
                   "        ),", extra, '\n');
    }

    void do_start_section(Names const& /*names*/, std::string const & /*section_name*/)
    {
    }

    void do_stop_section(Names const& /*names*/, std::string const & /*section_name*/)
    {
    }

    void do_init()
    {}

    int do_finish()
    {
        for (auto const& cat : this->categories) {
            auto file_it = file_map.find(cat);
            if (file_it == file_map.end()) {
                std::cerr << "ConnectionPolicyWriterBase: unknown " << cat << " for connpolicy\n";
                return 1;
            }

            auto const spec_filename = str_concat(this->directory_spec, '/', cat, ".spec");
            auto const json_filename = str_concat(this->directory_spec, '/', cat, ".json");

            std::ofstream out_spec(spec_filename);
            std::ofstream out_json(json_filename);

            out_spec << R"g([general]

# Secondary login Transformation rule
# ${LOGIN} will be replaced by login
# ${DOMAIN} (optional) will be replaced by domain if it exists.
# Empty value means no transformation rule.
transformation_rule = string(default='')

# Account Mapping password retriever
# Transformation to apply to find the correct account.
# ${USER} will be replaced by the user's login.
# ${DOMAIN} will be replaced by the user's domain (in case of LDAP mapping).
# ${USER_DOMAIN} will be replaced by the user's login + "@" + user's domain (or just user's login if there's no domain).
# ${GROUP} will be replaced by the authorization's user group.
# ${DEVICE} will be replaced by the device's name.
# A regular expression is allowed to transform a variable, with the syntax: ${USER:/regex/replacement}, groups can be captured with parentheses and used with \1, \2, ...
# For example to replace leading "A" by "B" in the username: ${USER:/^A/B}
# Empty value means no transformation rule.
vault_transformation_rule = string(default='')


)g";

            out_json << R"g({
  "sections": [
    {
      "name": "general",
      "members": [
        {
          "name": "transformation_rule",
          "type": "string",
          "default": "",
          "description": "Secondary login Transformation rule\n${LOGIN} will be replaced by login\n${DOMAIN} (optional) will be replaced by domain if it exists.\nEmpty value means no transformation rule."
        },
        {
          "name": "vault_transformation_rule",
          "type": "string",
          "default": "",
          "description": "Account Mapping password retriever\nTransformation to apply to find the correct account.\n${USER} will be replaced by the user's login.\n${DOMAIN} will be replaced by the user's domain (in case of LDAP mapping).\n${USER_DOMAIN} will be replaced by the user's login + \"@\" + user's domain (or just user's login if there's no domain).\n${GROUP} will be replaced by the authorization's user group.\n${DEVICE} will be replaced by the device's name.\nA regular expression is allowed to transform a variable, with the syntax: ${USER:/regex/replacement}, groups can be captured with parentheses and used with \\1, \\2, ...\nFor example to replace leading \"A\" by \"B\" in the username: ${USER:/^A/B}\nEmpty value means no transformation rule."
        }
      ]
    })g";
            auto& section_map = file_it->second;
            for (auto& section_name : this->ordered_section) {
                auto section_it = section_map.find(section_name);
                if (section_it != section_map.end()) {
                    out_spec
                        << "[" << section_name << "]\n\n"
                        << section_it->second.python_contains
                    ;
                    out_json
                        << ",\n    {\n"
                        "      \"name\": \"" << section_name << "\",\n"
                        "      \"members\": [\n"
                        << section_it->second.json_contains << "\n"
                        "      ]\n"
                        "    }"
                    ;
                }
            }

            out_json << "\n  ]\n}\n";

            struct P {
                std::ostream& out;
                std::string const& filename;
            };

            for (P p : {P{out_spec, spec_filename}, P{out_json, json_filename}}) {
                if (!p.out.flush()) {
                    std::cerr << "ConnectionPolicyWriterBase: " << p.filename << ": " << strerror(errno) << "\n";
                    return 1;
                }
            }
        }


        std::ofstream out_sesman(this->python_spec.filename);

        out_sesman <<
          "#!/usr/bin/python -O\n"
          "# -*- coding: utf-8 -*-\n\n"
          "# DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN\n\n"
          "cp_spec = {\n"
        ;

        for (auto const& section_name : this->ordered_section) {
            auto section_it = sesman_file.find(section_name);
            out_sesman
                << "    '" << section_name << "': {\n"
                << section_it->second << "    },\n"
            ;
        }

        out_sesman << "}\n";

        if (!out_sesman) {
            std::cerr << "ConnectionPolicyWriterBase: " << this->python_spec.filename << ": " << strerror(errno) << "\n";
            return 1;
        }
        return 0;
    }

private:
    struct Section
    {
        std::string python_contains;
        std::string json_contains;
    };
    using data_by_section_t = std::unordered_map<std::string, Section>;
    std::unordered_map<std::string, data_by_section_t> file_map;
    std::unordered_map<std::string, std::string> sesman_file;
    std::unordered_set<std::string> sesman_mems;
    std::vector<std::string> ordered_section;
    std::unordered_set<std::string> section_names;
    categories_t categories;
    std::string directory_spec;
};

}

}
