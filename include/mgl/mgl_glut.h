/* mgl_glut.h is part of Math Graphic Library
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
//-----------------------------------------------------------------------------
#ifndef _MGL_GLUT_H_
#define _MGL_GLUT_H_
#include "mgl/mgl_gl.h"
//-----------------------------------------------------------------------------
/// Class allows the window creation under OpenGL with the help of GLUT library
class mglGraphGLUT : public mglGraphGL
{
friend void _mgl_display();
friend void _mgl_key_up(unsigned char ch,int ,int );
friend void _mgl_timer(int);
public:
	bool AutoClf;	///< Clear canvas between drawing
	int Delay;		///< Delay for animation in ms

	mglGraphGLUT();
	~mglGraphGLUT();
	//void WriteEPS(const char *fname,const char *descr=0);	// ������� � EPS
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ��������� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/// Create a window for plotting. Now implemeted only for GLUT.
	void Window(int argc, char **argv, int (*draw)(mglGraph *gr, void *p),
						const char *title,void *par=NULL,
			   			void (*reload)(bool next)=NULL);
private:
	int nfig;		///< Number of figures in the list. If 0 then no list and mglGraph::DrawFunc will called for each drawing.
	int curr_fig;	///< Current figure in the list.
	int tt;			///< Temporal variable
	void (*LoadFunc)(bool);
	void *FuncPar;	///< Parameters for drawing function mglGraph::DrawFunc.
	/// Drawing function for window procedure.
	int (*DrawFunc)(mglGraph *gr, void *par);	//< It return the number
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
