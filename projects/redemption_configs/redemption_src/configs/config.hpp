/*
    This program is free software; you can redistribute it and/or modify it
     under the terms of the GNU General Public License as published by the
     Free Software Foundation; either version 2 of the License, or (at your
     option) any later version.

    This program is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
     Public License for more details.

    You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
     675 Mass Ave, Cambridge, MA 02139, USA.

    Product name: redemption, a FLOSS RDP proxy
    Copyright (C) Wallix 2014
    Author(s): Christophe Grosjean, Jonathan Poelen, Raphael Zhou, Meng Tan

    Configuration file,
    parsing config file rdpproxy.ini
*/

#pragma once

#include "configs/io.hpp"
#include "core/app_path.hpp"
#include "core/authid.hpp"

#include "utils/log.hpp"
#include "utils/cfgloader.hpp"

#include <cstdint>
#include <cassert>


namespace configs
{
    template<class... Ts>
    struct Pack : Ts...
    { static const std::size_t size = sizeof...(Ts); };

    template<class Base, template<class> class Tpl, class Pack>
    struct PointerPackArray;

    template<class Base, template<class> class Tpl, class... Ts>
    struct PointerPackArray<Base, Tpl, Pack<Ts...>>
    : Tpl<Ts>...
    {
        Base * values[sizeof...(Ts)];

        PointerPackArray()
        : values{&static_cast<Tpl<Ts>&>(*this)...}
        {}

        Base & operator[](authid_t i) {
            assert(i < sizeof...(Ts));
            return *this->values[i];
        }

        Base const & operator[](authid_t i) const {
            assert(i < sizeof...(Ts));
            return *this->values[i];
        }
    };

    template<class Config>
    struct CBuf : zstr_buffer_from<typename Config::type> {
    };

    template<class>
    struct BufferPack;

    template<class... Ts>
    struct BufferPack<Pack<Ts...>>
    : CBuf<Ts>...
    {};
} // namespace configs

// config members
//@{
#include "utils/redirection_info.hpp"
#include <string>
#include <chrono>
//@}

#include "config_variant.hpp"

#include "configs/autogen/enums.hpp"
#include "configs/autogen/variables_configuration_fwd.hpp"
#include "configs/autogen/variables_configuration.hpp"

#include "configs/autogen/enums_func_ini.hpp"


class Inifile
{
public:
    using authid_t = ::authid_t;
    using parse_error = configs::parse_error;

    REDEMPTION_DIAGNOSTIC_PUSH
    // Inifile::Field is a extern template
    REDEMPTION_DIAGNOSTIC_CLANG_IGNORE("-Wundefined-func-template")
    explicit Inifile()
    {
        this->initialize();
    }
    REDEMPTION_DIAGNOSTIC_POP

    template<class T>
    typename T::type const & get() const noexcept {
        //static_assert(T::is_sesman_to_proxy, "T isn't readable");
        return static_cast<T const &>(this->variables).value;
    }

    template<class T>
    typename T::type & get_mutable_ref() noexcept {
        static_assert(!T::is_proxy_to_sesman, "reference on write variable isn't safe");
        return static_cast<T&>(this->variables).value;
    }

    template<class T, class... Args>
    void set(Args && ... args) {
        static_assert(!T::is_proxy_to_sesman, "T is writable, used set_acl<T>() instead.");
        this->set_value<T>(std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    void set_acl(Args && ... args) {
        static_assert(T::is_proxy_to_sesman, "T isn't writable, used set<T>() instead.");
        this->set_value<T>(std::forward<Args>(args)...);
    }

    template<class T>
    void ask() {
        static_assert(T::is_sesman_to_proxy, "T isn't askable");
        this->to_send_index.insert(T::index);
        static_cast<Field<T>&>(this->fields).asked_ = true;
    }

    template<class T>
    bool is_asked() const {
        static_assert(T::is_sesman_to_proxy, "T isn't askable");
        return static_cast<Field<T>const&>(this->fields).asked_;
    }

private:
    template<class T, class... Args>
    void set_value(Args && ... args) {
        configs::set_value(
            static_cast<T&>(this->variables).value,
            configs::spec_type<typename T::mapped_type>{},
            std::forward<Args>(args)...
        );
        this->insert_index<T>(std::integral_constant<bool, T::is_proxy_to_sesman>());
        this->unask<T>(std::integral_constant<bool, T::is_sesman_to_proxy>());
    }

    template<class T> void insert_index(std::false_type /*disable*/) {}
    template<class T> void insert_index(std::true_type /*enable*/)
    { this->to_send_index.insert(T::index); }

    template<class T> void unask(std::false_type /*disable*/) {}
    template<class T> void unask(std::true_type /*enable*/)
    { this->fields[T::index].asked_ = false; }

    struct Buffers : configs::BufferPack<configs::VariablesAclPack> {};

    struct FieldBase
    {
        [[nodiscard]] bool is_asked() const { return this->asked_; }
        virtual bool parse(configs::VariablesConfiguration & variables, array_view_const_char value) = 0;
        virtual array_view_const_char
        to_string_view(configs::VariablesConfiguration const & variables, Buffers & buffers) const = 0;
        virtual ~FieldBase() = default;

    private:
        friend class Inifile;
        bool asked_ = false;
    };

    template<class T>
    struct Field : FieldBase
    {
        bool parse(configs::VariablesConfiguration & variables, array_view_const_char value) override final;

        /// \return array_view_const_char::data() guarantee with null terminal
        array_view_const_char
        to_string_view(configs::VariablesConfiguration const & variables, Buffers & buffers) const override final;
    };

public:
    struct ConfigurationHolder : ::ConfigurationHolder
    {
        void set_value(const char * context, const char * key, const char * value) override;

    private:
        friend class Inifile;

        explicit ConfigurationHolder(configs::VariablesConfiguration & variables)
        : variables(variables)
        {}

        configs::VariablesConfiguration & variables;
    };

    ConfigurationHolder & configuration_holder() {
        return this->conf_holder;
    }

    static const uint32_t ENABLE_DEBUG_CONFIG = 1;

private:
    template<bool is_constant>
    struct FieldReferenceBase
    {
        [[nodiscard]] bool is_asked() const {
            return this->field->asked_;
        }

        [[nodiscard]] array_view_const_char to_string_view() const {
            return this->field->to_string_view(this->ini->variables, this->ini->buffers);
        }

        explicit operator bool () const {
            return this->field;
        }

        [[nodiscard]] authid_t authid() const {
            return this->id;
        }

        [[nodiscard]] bool is_loggable() const
        {
            if (configs::is_loggable(unsigned(this->authid())))  {
                return true;
            }
            if (configs::is_unloggable_if_value_with_password(unsigned(this->authid()))) {
                return nullptr == strcasestr(this->to_string_view().data(), "password");
            }
            return false;
        }

        FieldReferenceBase(FieldReferenceBase &&) noexcept = default;

        FieldReferenceBase() = default;

        FieldReferenceBase(FieldReferenceBase const &) = delete;
        FieldReferenceBase & operator=(FieldReferenceBase const &) = delete;

    private:
        using InternalInifile = std::conditional_t<is_constant, Inifile const, Inifile>;
        std::conditional_t<is_constant, FieldBase const, FieldBase> * field = nullptr;
        InternalInifile* ini = nullptr;
        authid_t id = MAX_AUTHID;

        FieldReferenceBase(InternalInifile& ini, authid_t id)
        : field(&ini.fields[id])
        , ini(&ini)
        , id(id)
        {}

        friend class Inifile;
    };

public:
    struct FieldReference : FieldReferenceBase<false>
    {
        void ask() {
            this->field->asked_ = true;
        }

        bool set(char const *) = delete; // use `set(cstr_array_view("blah blah"))` instead

        bool set(array_view_const_char value) {
            auto const err = this->field->parse(this->ini->variables, value);
            if (err) {
                this->field->asked_ = false;
                this->ini->new_from_acl = true;
            }
            return err;
        }

        FieldReference(FieldReference &&) = default;

        FieldReference() = default;

        FieldReference(FieldReference const &) = delete;
        FieldReference & operator=(FieldReference const &) = delete;

    private:
        using FieldReferenceBase<false>::FieldReferenceBase;
        friend class Inifile;
    };

    FieldReference get_acl_field(authid_t authid) {
        if (authid >= MAX_AUTHID) {
            return {};
        }
        return {*this, authid};
    }

    bool check_from_acl() {
        return std::exchange(this->new_from_acl, false);
    }

    std::size_t changed_field_size() const {
        return this->to_send_index.size();
    }

    void clear_send_index() {
        this->to_send_index.clear();
    }

    struct FieldConstReference : FieldReferenceBase<true>
    {
        using FieldReferenceBase<true>::FieldReferenceBase;
        friend class Inifile;
    };

    struct FieldsChanged
    {
        struct iterator
        {
            iterator & operator++() {
                ++this->it;
                return *this;
            }

            bool operator != (iterator const & other) {
                return this->it != other.it;
            }

            FieldConstReference operator*() const {
                return {*this->ini, *this->it};
            }

        private:
            authid_t const * it;
            Inifile const * ini;

            friend struct FieldsChanged;

            iterator(authid_t const * it, Inifile const & ini)
            : it(it)
            , ini(&ini)
            {}
        };

        [[nodiscard]] iterator begin() const { return {this->ini->to_send_index.cbegin(), *this->ini}; }
        [[nodiscard]] iterator end() const { return {this->ini->to_send_index.cend(), *this->ini}; }

    private:
        Inifile const * ini;

        friend class Inifile;

        constexpr FieldsChanged(Inifile const & ini)
        :ini(&ini)
        {}
    };

    FieldsChanged get_fields_changed() const {
        return {*this};
    }

private:
    class ToSendIndexList
    {
        using uint_fast = uint_fast32_t;
        static const std::size_t count = configs::VariablesAclPack::size;
        std::array<uint_fast, (count + sizeof(uint_fast) - 1) / sizeof(uint_fast)> words {};
        std::array<authid_t, count> list;
        std::size_t list_size = 0;

    public:
        ToSendIndexList() = default;

        void insert(authid_t id) noexcept
        {
            uint_fast i = id;
            uint_fast mask = uint_fast{1} << (i % sizeof(uint_fast));
            uint_fast & word = this->words[i / sizeof(uint_fast)];
            if (!(word & mask)) {
                word |= mask;
                this->list[this->list_size++] = id;
            }
        }

        void clear() noexcept
        {
            this->words.fill(0);
            this->list_size = 0;
        }

        [[nodiscard]] std::size_t size() const noexcept
        {
            return this->list_size;
        }

        [[nodiscard]] authid_t const * cbegin() const noexcept
        {
            return this->list.cbegin();
        }

        [[nodiscard]] authid_t const * cend() const noexcept
        {
            return this->cbegin() + this->size();
        }
    };
    ToSendIndexList to_send_index;
    configs::VariablesConfiguration variables;
    configs::PointerPackArray<FieldBase, Field, configs::VariablesAclPack> fields;
    mutable Buffers buffers;
    ConfigurationHolder conf_holder {variables};
    bool new_from_acl = false;

    template<class T>
    void push_to_send_index()
    {
        static_assert(T::is_proxy_to_sesman, "is not writable");
        this->to_send_index.insert(T::index);
    }

    void initialize();
};
