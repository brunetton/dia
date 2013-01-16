/* Dia -- an diagram creation/manipulation program
 * Copyright (C) 1998 Alexander Larsson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef COLOR_H
#define COLOR_H

#include "diatypes.h"
#include <gdk/gdk.h>
#include "diavar.h"

void color_init(void);
Color *color_new_rgb(float r, float g, float b);
Color *color_new_rgba(float r, float g, float b, float alpha);
void color_convert(const Color *color, GdkRGBA *gdkcolor);
gboolean color_equals(const Color *color1, const Color *color2);

#ifdef G_OS_WIN32
static Color color_black = { 0.0f, 0.0f, 0.0f, 1.0f };
static Color color_white = { 1.0f, 1.0f, 1.0f, 1.0f };
#else
DIAVAR Color color_black, color_white;
#endif
DIAVAR GdkRGBA color_gdk_black, color_gdk_white;

#endif /* COLOR_H */
