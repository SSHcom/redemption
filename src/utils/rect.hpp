/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Product name: redemption, a FLOSS RDP proxy
   Copyright (C) Wallix 2010
   Author(s): Christophe Grosjean, Javier Caverni, Meng Tan
   Based on xrdp Copyright (C) Jay Sorg 2004-2010

   Rect class : Copyright (C) Christophe Grosjean 2009

*/


#pragma once

#include "utils/sugar/std_stream_proto.hpp"

#include <iosfwd>
#include <algorithm> // min max
#include <cstdlib> // abs
#include <cstdint>
#include <cassert>
#include <cstdio> // snprintf

struct Rect {
    int16_t x = 0;
    int16_t y = 0;
    uint16_t cx = 0;
    uint16_t cy = 0;

    // Inclusive left of rectangle
    [[nodiscard]] int16_t ileft() const {
        return this->x;
    }

    // Exclusive right of rectangle
    [[nodiscard]] int16_t eright() const {
        return static_cast<int16_t>(this->x + this->cx);
    }

    [[nodiscard]] int16_t itop() const {
        return this->y;
    }

    [[nodiscard]] int16_t ebottom() const {
        return static_cast<int16_t>(this->y + this->cy);
    }

    [[nodiscard]] uint16_t width() const {
        return this->cx;
    }

    [[nodiscard]] uint16_t height() const {
        return this->cy;
    }

    Rect() = default;

    Rect(int16_t left, int16_t top, uint16_t width, uint16_t height) noexcept
        : x(left), y(top), cx(width), cy(height)
    {
        // fast detection of overflow, works for valid width/height range 0..4096
        if (((width-1)|(height-1)) & 0x8000){
            this->cx = 0;
            this->cy = 0;
        }
    }

    [[nodiscard]] bool contains_pt(int16_t x, int16_t y) const {
        // return this->contains(Rect(x,y,1,1));
        return x  >= this->x
            && y  >= this->y
            && x   < this->x + this->cx
            && y   < this->y + this->cy;
    }

    [[nodiscard]] bool has_intersection(int16_t x, int16_t y) const
    {
        return this->cx && this->cy
            && (x >= this->x && x < this->eright())
            && (y >= this->y && y < this->ebottom());
    }

    // special cases: contains returns true
    // - if both rects are empty
    // - if inner rect is empty
    [[nodiscard]] bool contains(Rect inner) const {
        return (inner.x >= this->x
              && inner.y >= this->y
              && inner.eright() <= this->eright()
              && inner.ebottom() <= this->ebottom());
    }

    bool operator==(Rect const & other) const {
        return (other.x == this->x
             && other.y == this->y
             && other.cx == this->cx
             && other.cy == this->cy);
    }

    bool operator!=(Rect const & other) const {
        return !(*this == other);
    }

    void empty() {
        this->x  = 0;
        this->y  = 0;
        this->cx = 0;
        this->cy = 0;
    }

    // Rect constructor ensures that any empty rect will be (0, 0, 0, 0)
    // hence testing cx or cy is enough
    [[nodiscard]] bool isempty() const {
        return (this->cx == 0) || (this->cy == 0);
    }

    [[nodiscard]] int getCenteredX() const {
        return this->x + (this->cx / 2);
    }

    [[nodiscard]] int getCenteredY() const {
        return this->y + (this->cy / 2);
    }

    [[nodiscard]] Rect wh() const {
        return Rect(0, 0, this->cx, this->cy);
    }

    // compute a new rect containing old rect and given point
    [[nodiscard]] Rect enlarge_to(int16_t x, int16_t y) const {
        if (this->isempty()){
            return Rect(x, y, 1, 1);
        }

        const int16_t x0 = std::min(this->x, x);
        const int16_t y0 = std::min(this->y, y);
        const int16_t x1 = std::max(static_cast<int16_t>(this->eright() - 1), x);
        const int16_t y1 = std::max(static_cast<int16_t>(this->ebottom() - 1), y);
        return Rect(x0, y0, uint16_t(x1 - x0 + 1), uint16_t(y1 - y0 + 1));
    }

    [[nodiscard]] Rect offset(int16_t dx, int16_t dy) const {
        return Rect(
            static_cast<int16_t>(this->x + dx),
            static_cast<int16_t>(this->y + dy),
            this->cx,
            this->cy
        );
    }

    [[nodiscard]] Rect shrink(uint16_t margin) const {
        assert((this->cx >= margin * 2) && (this->cy >= margin * 2));
        return Rect(
            static_cast<int16_t>(this->x + margin),
            static_cast<int16_t>(this->y + margin),
            static_cast<uint16_t>(this->cx - margin * 2),
            static_cast<uint16_t>(this->cy - margin * 2)
        );
    }

    [[nodiscard]] Rect expand(uint16_t margin) const {
        return Rect(
            static_cast<int16_t>(this->x - margin),
            static_cast<int16_t>(this->y - margin),
            static_cast<uint16_t>(this->cx + margin * 2),
            static_cast<uint16_t>(this->cy + margin * 2)
        );
    }

    [[nodiscard]] Rect intersect(uint16_t width, uint16_t height) const {
        return this->intersect(Rect(0, 0, width, height));
    }

    [[nodiscard]] Rect intersect(Rect in) const
    {
        int16_t max_x = std::max(in.x, this->x);
        int16_t max_y = std::max(in.y, this->y);
        int16_t min_right = std::min(in.eright(), this->eright());
        int16_t min_bottom = std::min(in.ebottom(), this->ebottom());

        return Rect(max_x, max_y, uint16_t(min_right - max_x), uint16_t(min_bottom - max_y));
    }

    [[nodiscard]] Rect disjunct(Rect r) const
    {
        if (this->isempty()) {
            return r;
        }
        if (r.isempty()) {
            return *this;
        }

        auto x = std::min(r.x, this->x);
        auto y = std::min(r.y, this->y);
        auto cx = std::max(r.eright(), this->eright()) - x;
        auto cy = std::max(r.ebottom(), this->ebottom()) - y;
        return Rect(x, y, uint16_t(cx), uint16_t(cy));
    }

    [[nodiscard]] bool has_intersection(Rect in) const
    {
        return (this->cx && this->cy && !in.isempty()
        && ((in.x >= this->x && in.x < this->eright()) || (this->x >= in.x && this->x < in.eright()))
        && ((in.y >= this->y && in.y < this->ebottom()) || (this->y >= in.y && this->y < in.ebottom()))
        );
    }

    // Ensemblist difference
    template<class Fn>
    void difference(Rect a, Fn fn) const
    {
        const Rect intersect = this->intersect(a);

        if (!intersect.isempty()) {
            if (intersect.y > this->y) {
                fn(Rect(this->x, this->y,
                        this->cx, static_cast<uint16_t>(intersect.y - this->y)));
            }
            if (intersect.x > this->x) {
                fn(Rect(this->x, intersect.y,
                        static_cast<uint16_t>(intersect.x - this->x), intersect.cy));
            }
            if (this->eright() > intersect.eright()) {
                fn(Rect(intersect.eright(), intersect.y,
                        static_cast<uint16_t>(this->eright() - intersect.eright()), intersect.cy));
            }
            if (this->y + this->cy > intersect.ebottom()) {
                fn(Rect(this->x, intersect.ebottom(),
                        this->cx, static_cast<uint16_t>(this->ebottom() - intersect.ebottom())));
            }
        }
        else {
            fn(*this);
        }
    }

    REDEMPTION_FRIEND_OSTREAM(out, Rect const & r) {
        return out << "(" << r.x << ", " << r.y << ", " << r.cx << ", " << r.cy << ")";
    }

    //             |                         |
    //             |                         |
    //             |                         |
    //    UP       |         UP              |      UP
    //    LEFT     |                         |      RIGHT
    //             |                         |
    //-------------+-------------------------+--------------------
    //             |/ / / / / / / / / / / / /|
    //             | / / / / / / / / / / / / |
    //             |/ / / / / / / / / / / / /|
    //    LEFT     | / / / /   IN  / / / / / |     RIGHT
    //             |/ / / / / Rect  / / / / /|
    //             | / / / / / / / / / / / / |
    //             |/ / / / / / / / / / / / /|
    //-------------+-------------------------+-------------------
    //             |                         |
    //    DOWN     |         DOWN            |     DOWN
    //    LEFT     |                         |     RIGHT
    //             |                         |
    //             |                         |

    enum  t_region {
        IN = 0x00,
        UP = 0x01,
        DOWN = 0x02,
        LEFT = 0x04,
        RIGHT = 0x08
    };
    // Region of a point outside rect
    // 0x00 means inside
    [[nodiscard]] t_region region_pt(int16_t x, int16_t y) const {
        int res = IN;
        if (x < this->x) {
            res |= LEFT;
        }
        else if (x >= this->eright()) {
            res |= RIGHT;
        }
        if (y < this->y) {
            res |= UP;
        }
        else if (y >= this->ebottom()) {
            res |= DOWN;
        }
        return static_cast<t_region>(res);
    }
};

inline auto log_value(Rect const & rect)
{
    struct {
        char buffer[128];
        char const * value() { return buffer; }
    } d;
    ::sprintf(d.buffer, "Rect(%d %d %u %u)", rect.x, rect.y, rect.cx, rect.cy);
    return d;
}


struct Dimension {
    uint16_t w = 0;
    uint16_t h = 0;

    Dimension() = default;

    Dimension(uint16_t w, uint16_t h)
        : w(w)
        , h(h)
    {}

    bool operator==(Dimension const & other) const {
        return (other.w == this->w
             && other.h == this->h);
    }

    void empty() {
        this->w = 0;
        this->h = 0;
    }

    [[nodiscard]] bool isempty() const {
        return (!this->w || !this->h);
    }

    REDEMPTION_FRIEND_OSTREAM(out, Dimension const & d) {
        return out << "(" << d.w << ", " << d.h << ")";
    }
};

inline auto log_value(Dimension const & dim)
{
    struct {
        char buffer[64];
        char const * value() { return buffer; }
    } d;
    ::sprintf(d.buffer, "Dimension(%u %u)", dim.w, dim.h);
    return d;
}


struct Point {
    int x;
    int y;

    Point(int x, int y)
        : x(x)
        , y(y)
    {}

};

inline auto log_value(Point const & p)
{
    struct {
        char buffer[64];
        char const * value() { return buffer; }
    } d;
    ::sprintf(d.buffer, "Point(%d %d)", p.x, p.y);
    return d;
}


struct Segment {
    Point a;
    Point b;

    Segment(const Point & a, const Point & b)
        : a(a)
        , b(b)
    {}
};

inline auto log_value(Segment const & segment)
{
    struct {
        char buffer[128];
        char const * value() { return buffer; }
    } d;
    ::sprintf(d.buffer, "Segment(Point(%d %d), Point(%d %d))",
        segment.a.x, segment.a.y, segment.b.x, segment.b.y);
    return d;
}


struct LineEquation {
    Segment seg;
    Segment segin;

    int dX;
    int dY;
    int c;

    LineEquation(int aX, int aY, int bX, int bY)
        : seg(Segment(Point(aX, aY), Point(bX, bY)))
        , segin(Segment(Point(0, 0), Point(0, 0)))
        , dX(aX - bX)
        , dY(aY - bY)
        , c(bY*aX - aY*bX)
    {
    }

    [[nodiscard]] int compute_x(int y) const {
        return (this->dX*y - this->c) / this->dY;
    }

    [[nodiscard]] int compute_y(int x) const {
        return (this->dY*x + this->c) / this->dX;
    }

    bool compute_intersection(Rect rect, int region, int & x, int & y) const {
        int interX = 0;
        int interY = 0;
        bool found = false;

        if (region & Rect::LEFT) {
            int tmpy = this->compute_y(rect.x);
            if (tmpy >= rect.y && tmpy < rect.ebottom()) {
                found = true;
                interX = rect.x;
                interY = tmpy;
            }
        }
        else if (region & Rect::RIGHT) {
            int tmpy = this->compute_y(rect.eright() - 1);
            if (tmpy >= rect.y && tmpy < rect.ebottom()) {
                found = true;
                interX = rect.eright() - 1;
                interY = tmpy;
            }
        }

        if (region & Rect::UP) {
            int tmpx = this->compute_x(rect.y);
            if (tmpx >= rect.x && tmpx < rect.eright()) {
                found = true;
                interX = tmpx;
                interY = rect.y;
            }
        }
        else if (region & Rect::DOWN) {
            int tmpx = this->compute_x(rect.ebottom() - 1);
            if (tmpx >= rect.x && tmpx < rect.eright()) {
                found = true;
                interX = tmpx;
                interY = rect.ebottom() - 1;
            }
        }

        if (found) {
            x = interX;
            y = interY;
        }

        return found;
    }

    bool resolve(Rect rect) {
        Rect::t_region aPosition = rect.region_pt(int16_t(this->seg.a.x), int16_t(this->seg.a.y));
        Rect::t_region bPosition = rect.region_pt(int16_t(this->seg.b.x), int16_t(this->seg.b.y));

        if (aPosition & bPosition) {
            return false;
        }
        bool exist = true;
        if (!aPosition) {
            this->segin.a.x = this->seg.a.x;
            this->segin.a.y = this->seg.a.y;
        }
        else {
            exist &= this->compute_intersection(rect, aPosition, this->segin.a.x, this->segin.a.y);
        }

        if (!bPosition) {
            this->segin.b.x = this->seg.b.x;
            this->segin.b.y = this->seg.b.y;
        }
        else {
            exist &= this->compute_intersection(rect, bPosition, this->segin.b.x, this->segin.b.y);
        }
        return exist;
    }
};


// helper class used to compute differences between two rectangles
class DeltaRect {
    public:
    int dleft;
    int dtop;
    int dheight;
    int dwidth;

    DeltaRect(Rect r1, Rect r2)
    : dleft(r1.x - r2.x)
    , dtop(r1.y - r2.y)
    , dheight(r1.cy - r2.cy)
    , dwidth(r1.cx - r2.cx)
    {}

    [[nodiscard]] bool fully_relative() const {
        return (abs(this->dleft) < 128)
            && (abs(this->dtop) < 128)
            && (abs(this->dwidth) < 128)
            && (abs(this->dheight) < 128)
            ;
    }
};

inline auto log_value(DeltaRect const & delta)
{
    struct {
        char buffer[128];
        char const * value() { return buffer; }
    } d;
    ::sprintf(d.buffer, "DeltaRect(%d %d %d %d)",
        delta.dleft, delta.dtop, delta.dheight, delta.dwidth);
    return d;
}
