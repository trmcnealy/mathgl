/* grid.cpp is part of UDAV
 * Copyright (C) 2007 Alexey Balakin <balakin@appl.sci-nnov.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/fl_draw.H>
#include "udav.h"
//-----------------------------------------------------------------------------
Fl_Callback input_cb;
//-----------------------------------------------------------------------------
void input_cb(Fl_Widget*, void* v)	{ ((Fl_Data_Table*)v)->set_value(); }
//-----------------------------------------------------------------------------
Fl_Data_Table::Fl_Data_Table(int x, int y, int w, int h, const char *l) : Fl_Table(x,y,w,h,l)
{
	callback(&event_callback, (void*)this);
	input = new Fl_Input(w/2,h/2,0,0);
	input->hide();
	input->callback(input_cb, (void*)this);
	input->when(FL_WHEN_ENTER_KEY_ALWAYS);
	input->maximum_size(16);
//	(new Fl_Box(9999,9999,0,0))->hide();  // HACK: prevent flickering in Fl_Scroll
	end();
}
//-----------------------------------------------------------------------------
// Handle drawing all cells in table
void Fl_Data_Table::draw_cell(TableContext context, int R, int C, int X, int Y, int W, int H)
{
	static char s[32];
	fl_push_clip(X, Y, W, H);
	switch ( context )
	{
	case CONTEXT_COL_HEADER:
		fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, col_header_color());
		fl_font(FL_HELVETICA | FL_BOLD, 14);
		fl_color(FL_BLACK);		sprintf(s,"%d",C);
		fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
		break;
	case CONTEXT_ROW_HEADER:
		fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, col_header_color());
		fl_font(FL_HELVETICA | FL_BOLD, 14);
		fl_color(FL_BLACK);		sprintf(s,"%d",R);
		fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
		break;
	case CONTEXT_CELL:
	    if (R == row && C == col && input->visible())	break;
		fl_draw_box(FL_THIN_DOWN_BOX, X, Y, W, H, FL_WHITE);
		fl_pop_clip();
		fl_push_clip(X+3, Y+3, W-6, H-6);
		fl_font(FL_HELVETICA, 14);
		fl_color(FL_BLACK);
		if(mgl_isnan(data[C+nx*R]))	strcpy(s,"nan");
		else	sprintf(s,"%g",data[C+nx*R]);
		fl_draw(s, X+3, Y+3, W-6, H-6, FL_ALIGN_RIGHT);
		break;
	case CONTEXT_RC_RESIZE:
		if (!input->visible()) break;
		find_cell(CONTEXT_TABLE, row, col, X, Y, W, H);
		if (X!=input->x() || Y!=input->y() || W!=input->w() || H!=input->h())
			input->resize(X,Y,W,H);
		break;
	default:	break;
	}
	fl_pop_clip();
}
//-----------------------------------------------------------------------------
void Fl_Data_Table::cell_click()
{
    int R = callback_row(), C = callback_col();
    TableContext context = callback_context();

    if(context==CONTEXT_CELL)
	{
		if (input->visible())	//input->do_callback();
		{
			const char *s = input->value();
			data[col + nx*row] = (s[0]==0 || !strcmp(s,"nan")) ? NAN : atof(s);
		}
		row = R;		col = C;
		int XX,YY,WW,HH;
		find_cell(CONTEXT_CELL, R, C, XX, YY, WW, HH);
		input->resize(XX,YY,WW,HH);
		char s[32];
		if(mgl_isnan(data[C+nx*R]))	strcpy(s,"nan");
		else	sprintf(s,"%g",data[C+nx*R]);
		input->value(s);	input->show();
		input->take_focus();
	}
}
//-----------------------------------------------------------------------------
void Fl_Data_Table::set_value()
{
	const char *s = input->value();
	data[col + nx*row] = (s[0]==0 || !strcmp(s,"nan")) ? NAN : atof(s);
}
//-----------------------------------------------------------------------------
