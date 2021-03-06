/* Dia -- an diagram creation/manipulation program
 * Copyright (C) 1999 Alexander Larsson
 *
 * beziershape.h - code to help implement bezier shapes
 * Copyright (C) 2000 James Henstridge
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
 
/** \file beziershape.h Allows to construct closed objects consisting of bezier lines */

#ifndef BEZIERSHAPE_H
#define BEZIERSHAPE_H

#include "diatypes.h"
#include "object.h"
#include "boundingbox.h"
#include "bezier-common.h"

#define HANDLE_CORNER (HANDLE_CUSTOM1)

/*!
 * \brief Base class for bezier shaped elements
 *
 * This is a subclass of DiaObject used to help implementing objects
 * that form a polygon-like shape of line-segments.
 *
 * \extends _DiaObject
 */
struct _BezierShape {
  /*! \protected DiaObject must be first because this is a 'subclass' of it. */
  DiaObject object;
  /*! \protected Number of points in points array */
  BezierCommon bezier;
  /*! \protected Extra info (like line-width) to help bounding boc calculation */
  ElementBBExtras extra_spacing;
};

void beziershape_update_data(BezierShape *bezier);
void beziershape_update_boundingbox(BezierShape *bezier);
void beziershape_init(BezierShape *bezier, int num_points);
void beziershape_destroy(BezierShape *bezier);
void beziershape_copy(BezierShape *from, BezierShape *to);
void beziershape_save(BezierShape *bezier, ObjectNode obj_node);
/* NOTE: Does object_init() */
void beziershape_load(BezierShape *bezier, ObjectNode obj_node, DiaContext *ctx);
ObjectChange *beziershape_add_segment(BezierShape *bezier, int segment,
				      Point *point);
ObjectChange *beziershape_remove_segment(BezierShape *bezier, int point);
ObjectChange *beziershape_set_corner_type(BezierShape *bez, Handle *handle,
					  BezCornerType corner_type);
ObjectChange *beziershape_move_handle(BezierShape *bezier, Handle *id,
				      Point *to, ConnectionPoint *cp,
				      HandleMoveReason reason,
				      ModifierKeys modifiers);
ObjectChange *beziershape_move(BezierShape *bezier, Point *to);
real beziershape_distance_from(BezierShape *bezier, Point *point,
			       real line_width);
Handle *beziershape_closest_handle(BezierShape *bezier, Point *point);
Handle *beziershape_closest_major_handle(BezierShape *bezier, Point *point);

#define BEZSHAPE_COMMON_PROPERTIES \
  OBJECT_COMMON_PROPERTIES, \
  { "bez_points", PROP_TYPE_BEZPOINTARRAY, 0, "beziershape points", NULL} \

#define BEZSHAPE_COMMON_PROPERTIES_OFFSETS \
  OBJECT_COMMON_PROPERTIES_OFFSETS, \
  { "bez_points", PROP_TYPE_BEZPOINTARRAY, \
     offsetof(BezierShape,bezier.points), offsetof(BezierShape,bezier.num_points)} \

#endif /* BEZIER_SHAPE_H */
