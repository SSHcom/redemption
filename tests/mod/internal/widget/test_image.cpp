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
 *   Copyright (C) Wallix 2010-2012
 *   Author(s): Christophe Grosjean, Dominique Lafages, Jonathan Poelen,
 *              Meng Tan
 */

#include "test_only/test_framework/redemption_unit_tests.hpp"


#include "mod/internal/widget/image.hpp"
#include "mod/internal/widget/screen.hpp"
#include "test_only/check_sig.hpp"
#include "test_only/gdi/test_graphic.hpp"
#include "test_only/core/font.hpp"

RED_AUTO_TEST_CASE(TraceWidgetImage)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position 0,0 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(0, 0);

    // ask to widget to redraw at it's current position
    wimage.rdp_input_invalidate(Rect(0 + wimage.x(),
                                     0 + wimage.y(),
                                     wimage.cx(),
                                     wimage.cy()));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image.png");

    RED_CHECK_SIG(drawable, "\xe2\x5c\x4a\x10\xe0\xbc\x8f\x3c\xb5\x0b\x10\x98\xd1\xdc\x3b\xb8\x33\x28\x76\xbb");
}

RED_AUTO_TEST_CASE(TraceWidgetImage2)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position 10,100 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(10, 100);

    // ask to widget to redraw at it's current position
    wimage.rdp_input_invalidate(Rect(0 + wimage.x(),
                                     0 + wimage.y(),
                                     wimage.cx(),
                                     wimage.cy()));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image2.png");

    RED_CHECK_SIG(drawable, "\xfe\x5c\x1a\x41\xb3\x22\xa4\xc8\xe3\x39\x31\xd3\xd2\xe8\xe6\x55\x56\xce\x9a\xc7");
}

RED_AUTO_TEST_CASE(TraceWidgetImage3)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position -100,500 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(-100, 500);

    // ask to widget to redraw at it's current position
    wimage.rdp_input_invalidate(Rect(0 + wimage.x(),
                                     0 + wimage.y(),
                                     wimage.cx(),
                                     wimage.cy()));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image3.png");

    RED_CHECK_SIG(drawable, "\x15\xf3\xaf\x95\xac\x8e\x9b\xbc\x94\x91\x33\x79\x17\xf9\xee\x43\x74\x9c\x34\xc2");
}

RED_AUTO_TEST_CASE(TraceWidgetImage4)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position 700,500 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(700, 500);

    // ask to widget to redraw at it's current position
    wimage.rdp_input_invalidate(Rect(0 + wimage.x(),
                                     0 + wimage.y(),
                                     wimage.cx(),
                                     wimage.cy()));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image4.png");

    RED_CHECK_SIG(drawable, "\xff\x70\xc7\xd1\x91\x5d\x2a\x6b\x1d\x70\xf8\xcb\x96\x8d\x04\xef\x03\xcf\x73\x0e");
}

RED_AUTO_TEST_CASE(TraceWidgetImage5)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position -100,-100 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(-100, -100);

    // ask to widget to redraw at it's current position
    wimage.rdp_input_invalidate(Rect(0 + wimage.x(),
                                     0 + wimage.y(),
                                     wimage.cx(),
                                     wimage.cy()));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image5.png");

    RED_CHECK_SIG(drawable, "\x1a\x71\xe8\x5b\x2b\x93\x0c\x4b\x68\x9f\xf8\x65\xc8\x53\xdd\xb5\x59\x9f\x29\x28");
}

RED_AUTO_TEST_CASE(TraceWidgetImage6)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position 700,-100 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(700, -100);

    // ask to widget to redraw at it's current position
    wimage.rdp_input_invalidate(Rect(0 + wimage.x(),
                                     0 + wimage.y(),
                                     wimage.cx(),
                                     wimage.cy()));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image6.png");

    RED_CHECK_SIG(drawable, "\x34\x31\x5a\xd6\x44\x12\x6b\xb0\xb6\x61\x54\x70\x57\x63\xf3\x8f\x27\x76\xa3\x2e");
}

RED_AUTO_TEST_CASE(TraceWidgetImageClip)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position 700,-100 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(700, -100);

    // ask to widget to redraw at position 80,10 and of size 50x100. After clip the size is of 20x15
    wimage.rdp_input_invalidate(Rect(80 + wimage.x(),
                                     10 + wimage.y(),
                                     50,
                                     100));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image7.png");

    RED_CHECK_SIG(drawable, "\xa9\x9b\x0f\x65\x5b\xd3\xd0\x70\xee\xd2\xad\xa8\x61\x38\x5e\x9e\x95\x7a\x24\xa2");
}

RED_AUTO_TEST_CASE(TraceWidgetImageClip2)
{
    TestGraphic drawable(800, 600);


    // WidgetImage is a image widget of size 256x125 at position 0,0 in it's parent context
    WidgetScreen parent(drawable, global_font(), nullptr, Theme{});
    parent.set_wh(800, 600);

    NotifyApi * notifier = nullptr;

    WidgetImage wimage(drawable, FIXTURES_PATH"/logo-redemption.png", parent, notifier);
    Dimension dim = wimage.get_optimal_dim();
    wimage.set_wh(dim);
    wimage.set_xy(0, 0);

    // ask to widget to redraw at position 100,25 and of size 100x100.
    wimage.rdp_input_invalidate(Rect(100 + wimage.x(),
                                     25 + wimage.y(),
                                     100,
                                     100));

    //drawable.save_to_png(OUTPUT_FILE_PATH "image8.png");

    RED_CHECK_SIG(drawable, "\x30\xd6\xba\x4a\xd4\x54\x54\xc8\xa6\x55\xe1\xe7\xd1\x95\x83\xca\x36\xd0\x96\x47");
}
