/***************************************************************************
 * fltk_example.cpp is part of Math Graphic Library
 * Copyright (C) 2007 Alexey Balakin <balakin@appl.sci-nnov.ru>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "mgl2/window.h"
#if defined(WIN32) || defined(_MSC_VER) || defined(__BORLANDC__)
#include <windows.h>
#endif
//-----------------------------------------------------------------------------
int test_wnd(mglGraph *gr);
int sample(mglGraph *gr);
int sample_1(mglGraph *gr);
int sample_2(mglGraph *gr);
int sample_3(mglGraph *gr);
int sample_d(mglGraph *gr);
//-----------------------------------------------------------------------------
//#include <unistd.h>
mglPoint pnt;  // some global variable for changable data
void *mgl_fltk_tmp(void *)	{	mgl_fltk_run();	return 0;	}
//#define PTHREAD_SAMPLE
//-----------------------------------------------------------------------------
int main(int argc,char **argv)
{
#ifdef PTHREAD_SAMPLE
	mglWindow gr("test");
	gr.RunThr();
	for(int i=0;i<10;i++)	// do calculation
	{
#if defined(WIN32) || defined(_MSC_VER) || defined(__BORLANDC__)
		Sleep(1000);
#else
		sleep(1);           // which can be very long
#endif
		pnt = mglPoint(2*mgl_rnd()-1,2*mgl_rnd()-1);
		gr.Clf();			// make new drawing
		gr.Line(mglPoint(),pnt,"Ar2");
		char str[10] = "i=0";	str[3] = '0'+i;
		gr.Puts(mglPoint(),"");
		gr.Update();		// update window
	}
	return 0;	// finish calculations and close the window
#else
	mglWindow *gr;
	char key = 0;
	if(argc>1)	key = argv[1][0]!='-' ? argv[1][0]:argv[1][1];
	else	printf("You may specify argument '1', '2', '3' or 'd' for viewing examples of 1d, 2d, 3d or dual plotting\n");
	switch(key)
	{
		case '1':	gr = new mglWindow(sample_1,"1D plots",0);	break;
		case '2':	gr = new mglWindow(sample_2,"2D plots",0);	break;
		case '3':	gr = new mglWindow(sample_3,"3D plots",0);	break;
		case 'd':	gr = new mglWindow(sample_d,"Dual plots",0);	break;
		case 't':	gr = new mglWindow(test_wnd,"Testing",0);	break;
		default:	gr = new mglWindow(sample,"Drop and waves",0);	break;
	}
	gr->Run();	return 0;
#endif
}
//-----------------------------------------------------------------------------
