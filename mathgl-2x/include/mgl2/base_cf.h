/***************************************************************************
 * base_cf.h is part of Math Graphic Library
 * Copyright (C) 2007 Alexey Balakin <balakin@appl.sci-nnov.ru>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef _MGL_BASE_CF_H_
#define _MGL_BASE_CF_H_
#include "mgl2/base.h"
//-----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/// Get last warning code
int mgl_get_warn(HMGL gr);
int mgl_get_warn_(uintptr_t *gr);
/// Set warning code ant fill message
void mgl_set_warn(HMGL gr, int code, const char *text);
void mgl_set_warn_(uintptr_t *gr, int *code, const char *text,int);
/// Set buffer for warning messages
const char *mgl_get_mess(HMGL gr);

/// Get bit-value flag of HMGL state (for advanced users only)
int mgl_get_flag(HMGL gr, long flag);
/// Set bit-value flag of HMGL state (for advanced users only)
void mgl_set_flag(HMGL gr, int val, long flag);
/// Change counter of HMGL uses (for advanced users only). Non-zero counter prevent automatic object removing.
long mgl_use_graph(HMGL gr, int inc);
long mgl_use_graph_(uintptr_t *gr, int *inc);
void mgl_set_rdc_acc(HMGL gr, int reduce);	// TODO
void mgl_set_rdc_acc_(uintptr_t *gr, int *reduce);

/// Start group of objects
void mgl_start_group(HMGL gr, const char *);
void mgl_start_group_(uintptr_t *gr, const char *,int);
/// End group of objects
void mgl_end_group(HMGL gr);
void mgl_end_group_(uintptr_t *gr);
/// Highlight objects with given id
void mgl_highlight(HMGL gr, int id);
void mgl_highlight_(uintptr_t *gr, int *id);

/// Set default palette
void mgl_set_palette(HMGL gr, const char *colors);
void mgl_set_palette_(uintptr_t *gr, const char *colors, int);
void mgl_set_pal_color_(uintptr_t *gr, int *n, mreal *r, mreal *g, mreal *b);
void mgl_set_pal_num_(uintptr_t *gr, int *num);
/// Sets RGB values for color with given id
void mgl_set_color(char id, double r, double g, double b);
void mgl_set_color_(char *id, mreal *r, mreal *g, mreal *b, int);
/// Set default color scheme
void mgl_set_def_sch(HMGL gr, const char *sch);
void mgl_set_def_sch_(uintptr_t *gr, const char *sch,int);

/// Set default value of alpha-channel
void mgl_set_alpha_default(HMGL gr, double alpha);
void mgl_set_alpha_default_(uintptr_t *gr, mreal *alpha);
/// Set relative width of rectangles in Bars, Barh, BoxPlot
void mgl_set_bar_width(HMGL gr, double width);
void mgl_set_bar_width_(uintptr_t *gr, mreal *width);
/// Set number of mesh lines (use 0 to draw all of them)
void mgl_set_meshnum(HMGL gr, int num);
void mgl_set_meshnum_(uintptr_t *gr, int *num);
/// Set number of visible faces (use 0 to draw all of them)
void mgl_set_facenum(HMGL gr, int num);
void mgl_set_facenum_(uintptr_t *gr, int *num);
/// Clear unused points and primitives. Useful only in combination with mgl_set_facenum().
void mgl_clear_unused(HMGL gr);
void mgl_clear_unused_(uintptr_t *gr);

/// Set ambient light brightness
void mgl_set_ambbr(HMGL gr, double i);
void mgl_set_ambbr_(uintptr_t *gr, mreal *i);
/// Use diffusive light (only for local light sources)
void mgl_set_light_dif(HMGL gr, int enable);
void mgl_set_light_dif_(uintptr_t *gr, int *enable);

/// Set cutting for points outside of bounding box
void mgl_set_cut(HMGL gr, int cut);
void mgl_set_cut_(uintptr_t *gr, int *cut);
/// Set additional cutting box
void mgl_set_cut_box(HMGL gr, double x1,double y1,double z1,double x2,double y2,double z2);
void mgl_set_cut_box_(uintptr_t *gr, mreal *x1, mreal *y1, mreal *z1, mreal *x2, mreal *y2, mreal *z2);
/// Set the cutting off condition (formula)
void mgl_set_cutoff(HMGL gr, const char *EqC);
void mgl_set_cutoff_(uintptr_t *gr, const char *EqC, int);

/// Set values of axis range
void mgl_set_ranges(HMGL gr, double x1, double x2, double y1, double y2, double z1, double z2);
void mgl_set_ranges_(uintptr_t *gr, mreal *x1, mreal *x2, mreal *y1, mreal *y2, mreal *z1, mreal *z2);
/// Set range in direction dir as [v1, v2]
void mgl_set_range_val(HMGL gr, char dir, double v1,double v2);
void mgl_set_range_val_(uintptr_t *gr, const char *dir, mreal *v1, mreal *v2,int);
/// Set range in direction dir as minimal and maximal values of data a
void mgl_set_range_dat(HMGL gr, char dir, HCDT a, int add);
void mgl_set_range_dat_(uintptr_t *gr, const char *dir, uintptr_t *a, int *add,int);
/// Set axis range scaling -- simplified way to shift/zoom axis range -- need to redraw whole image!
void mgl_zoom_axis(HMGL gr, double x1,double y1,double z1,double c1,double x2,double y2,double z2,double c2);
void mgl_zoom_axis_(uintptr_t *gr, mreal *x1, mreal *y1, mreal *z1, mreal *c1, mreal *x2, mreal *y2, mreal *z2, mreal *c2);

/// Set axis origin
void mgl_set_origin(HMGL gr, double x0, double y0, double z0);
void mgl_set_origin_(uintptr_t *gr, mreal *x0, mreal *y0, mreal *z0);
/// Set the transformation formulas for coordinate
void mgl_set_func(HMGL gr, const char *EqX,const char *EqY,const char *EqZ,const char *EqA);
void mgl_set_func_(uintptr_t *gr, const char *EqX, const char *EqY, const char *EqZ, const char *EqA, int, int, int, int);
/// Set one of predefined transformation rule
void mgl_set_coor(HMGL gr, int how);
void mgl_set_coor_(uintptr_t *gr, int *how);
/// Set to draw Ternary axis (triangle like axis, grid and so on)
void mgl_set_ternary(HMGL gr, int enable);
void mgl_set_ternary_(uintptr_t *gr, int *enable);

/// Set to use or not tick labels rotation
void mgl_set_tick_rotate(HMGL gr, int enable);
void mgl_set_tick_rotate_(uintptr_t *gr, int *enable);
/// Set to use or not tick labels skipping
void mgl_set_tick_skip(HMGL gr, int enable);
void mgl_set_tick_skip_(uintptr_t *gr, int *enable);

/// Set default font for all new HMGL objects
void mgl_def_font(const char *name, const char *path);
void mgl_def_font_(const char *name, const char *path,int,int);
/// Set default size of marks (locally you can use "size" option)
void mgl_set_mark_size(HMGL gr, double size);
void mgl_set_mark_size_(uintptr_t *gr, mreal *size);
/// Set default size of arrows (locally you can use "size" option)
void mgl_set_arrow_size(HMGL gr, double size);
void mgl_set_arrow_size_(uintptr_t *gr, mreal *size);
/// Set default font size
void mgl_set_font_size(HMGL gr, double size);
void mgl_set_font_size_(uintptr_t *gr, mreal *size);
/// Set default font style and color
void mgl_set_font_def(HMGL gr, const char *fnt);
void mgl_set_font_def_(uintptr_t *gr, const char *fnt, int);
/// Set to use or not text rotation
void mgl_set_rotated_text(HMGL gr, int enable);
void mgl_set_rotated_text_(uintptr_t *gr, int *enable);
/// Load font from file
void mgl_load_font(HMGL gr, const char *name, const char *path);
void mgl_load_font_(uintptr_t *gr, char *name, char *path, int l, int n);
/// Copy font from another mglGraph instance
void mgl_copy_font(HMGL gr, HMGL gr_from);
void mgl_copy_font_(uintptr_t *gr, uintptr_t *gr_from);
/// Restore font (load default font for new HMGL objects)
void mgl_restore_font(HMGL gr);
void mgl_restore_font_(uintptr_t *gr);

#ifdef __cplusplus
}
#endif
//-----------------------------------------------------------------------------
#endif
