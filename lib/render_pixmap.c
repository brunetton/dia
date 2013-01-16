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

/* This renderer is similar to RenderGdk, except that it renders onto
 * its own little GdkPixmap, doesn't deal with the DDisplay at all, and
 * uses a 1-1 mapping between points and pixels.  It is used for rendering
 * arrows and lines onto selectors.  This way, any change in the arrow 
 * definitions are automatically reflected in the selectors.
 */

/*
 * 2002-10-06 : Leaved the original comment but removed almost
 * anything else. The 'RendererPixmap' now uses the DiaGdkRenderer which 
 * is the ported to GObject 'RendererGdk'. No more huge code duplication 
 * but only some renderer parametrization tweaking.                 --hb
 */
#include <config.h>

#include <math.h>
#include <stdlib.h>
#include <gdk/gdk.h>

#include "render_pixmap.h"
#include "message.h"
#include "diagdkrenderer.h"

static Rectangle rect;
static real zoom = 1.0;

DiaRenderer *
new_pixmap_renderer(GdkWindow *window, int width, int height)
{
  DiaGdkRenderer *renderer;
  GtkStyleContext *style;
  GdkRGBA color;

  rect.left = 0;
  rect.top = 0;
  rect.right = width;
  rect.bottom = height;

  renderer = g_object_new (DIA_TYPE_GDK_RENDERER, NULL);
  renderer->transform = dia_transform_new (&rect, &zoom);
  renderer->pixmap =
     gdk_window_create_similar_surface(window, CAIRO_CONTENT_COLOR,
                                       width, height);
  renderer->cr = cairo_create(renderer->pixmap);

  cairo_save(renderer->cr);
  cairo_set_source_rgb(renderer->cr, 1, 1, 1);
  cairo_rectangle(renderer->cr, 0, 0, width, height);
  cairo_fill(renderer->cr);
  cairo_restore(renderer->cr);
  cairo_surface_flush(renderer->pixmap);

  return DIA_RENDERER(renderer);
}

void
renderer_pixmap_set_pixmap (DiaRenderer *ren, 
                            cairo_surface_t *pixmap,
                            int xoffset, int yoffset, 
                            int width, int height)
{
  DiaGdkRenderer *renderer = DIA_GDK_RENDERER (ren);

  if (renderer->cr != NULL)
    cairo_destroy(renderer->cr);

  if (renderer->pixmap != NULL)
    cairo_surface_destroy(renderer->pixmap);

  renderer->pixmap = cairo_surface_reference(pixmap);
  renderer->cr = cairo_create(renderer->pixmap);

  rect.left = -xoffset;
  rect.top = -yoffset;
  rect.right = width;
  rect.bottom = height;
}

cairo_surface_t *
renderer_pixmap_get_pixmap (DiaRenderer *ren) 
{
  DiaGdkRenderer *renderer = DIA_GDK_RENDERER (ren);

  return renderer->pixmap;
}
