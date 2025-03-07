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
    Copyright (C) Wallix 2013
    Author(s): Christophe Grosjean, Meng Tan, Raphael Zhou
*/

#include "mod/internal/widget/group_box.hpp"
#include "core/RDP/orders/RDPOrdersPrimaryOpaqueRect.hpp"
#include "gdi/graphic_api.hpp"
#include "utils/sugar/cast.hpp"
#include "utils/utf.hpp"


WidgetGroupBox::WidgetGroupBox(
    gdi::GraphicApi & drawable, Widget & parent,
    NotifyApi * notifier, const char * text,
    BGRColor fgcolor, BGRColor bgcolor, Font const & font
)
  : WidgetParent(drawable, parent, notifier)
  , bg_color(bgcolor)
  , fg_color(fgcolor)
  , font(font)
{
    this->impl = &composite_array;

    this->set_text(text);
}

WidgetGroupBox::~WidgetGroupBox()
{
    this->clear();
}

void WidgetGroupBox::rdp_input_invalidate(Rect clip)
{
    Rect rect_intersect = clip.intersect(this->get_rect());

    if (!rect_intersect.isempty()) {
        this->drawable.begin_update();

        WidgetParent::draw_inner_free(rect_intersect, this->bg_color);

        // Box.
        const uint16_t border           = 6;
        const uint16_t text_margin      = 6;
        const uint16_t text_indentation = border + text_margin + 4;

        gdi::TextMetrics tm1(this->font, "bp");
        gdi::TextMetrics tm2(this->font, this->buffer);

        auto gcy = this->cy() - tm1.height / 2 - border;
        auto gcx = this->cx() - border * 2 + 1;
        auto px = this->x() + border - 1;

        auto wlabel = text_margin * 2 + tm2.width;
        auto y = this->y() + tm1.height / 2;

        auto const color_ctx = gdi::ColorCtx::depth24();

        // Top Line and Label
        auto rect1 = Rect(px, y, text_indentation - text_margin - border + 2, 1);
        this->drawable.draw(RDPOpaqueRect(rect1, encode_color24()(this->fg_color)), rect_intersect, color_ctx);
        gdi::server_draw_text(this->drawable, this->font
                            , this->x() + text_indentation
                            , this->y()
                            , this->buffer
                            , encode_color24()(this->fg_color)
                            , encode_color24()(this->bg_color)
                            , color_ctx
                            , rect_intersect
                            );
        auto rect2 = Rect(px + wlabel + 4, y, gcx + 1 - wlabel - 4, 1);
        this->drawable.draw(RDPOpaqueRect(rect2, encode_color24()(this->fg_color)), rect_intersect, color_ctx);
        // Bottom line
        auto rect3 = Rect(px, y + gcy, gcx + 1, 1);
        this->drawable.draw(RDPOpaqueRect(rect3, encode_color24()(this->fg_color)), rect_intersect, color_ctx);

        // Left border
        auto rect4 = Rect(px, y + 1, 1, gcy - 1);
        this->drawable.draw(RDPOpaqueRect(rect4, encode_color24()(this->fg_color)), rect_intersect, color_ctx);

        // Right Border
        auto rect5 = Rect(px + gcx, y, 1, gcy);
        this->drawable.draw(RDPOpaqueRect(rect5, encode_color24()(this->fg_color)), rect_intersect, color_ctx);


        WidgetParent::invalidate_children(rect_intersect);

        this->drawable.end_update();
    }
}

BGRColor WidgetGroupBox::get_bg_color() const
{
    return this->bg_color;
}

const char * WidgetGroupBox::get_text() const
{
    return this->buffer;
}

void WidgetGroupBox::set_text(const char * text)
{
    this->buffer[0] = 0;
    if (text) {
        const size_t remain_n = buffer_size - 1;
        const size_t n = strlen(text);
        const size_t max = ((remain_n >= n) ? n :
                            ::UTF8StringAdjustedNbBytes(::byte_ptr_cast(text), remain_n));
        memcpy(this->buffer, text, max);
        this->buffer[max] = 0;
    }
}
