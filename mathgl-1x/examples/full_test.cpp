/***************************************************************************
 * full_test.cpp is part of Math Graphic Library
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
#include <wchar.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <mgl/mgl_zb.h>
#include <mgl/mgl_eps.h>
#include <mgl/mgl_idtf.h>
//#include <mgl/mgl_w.h>
//-----------------------------------------------------------------------------
#include "mgl/mgl_parse.h"
extern mglTeXsymb mgl_tex_symb[];
int test(mglGraphAB *gr)
{
	gr->Axis(mglPoint(-1,-1,-1),mglPoint(2,2,2));

	mglData f(4,6);
	mglData x(8);
	mglData y(8);
	mglData z(8);

	f.a[0]=0;	f.a[1]=2;	f.a[2]=6;	f.a[3]=4;
	f.a[4]=1;	f.a[5]=3;	f.a[6]=7;	f.a[7]=5;
	f.a[8]=0;	f.a[9]=4;	f.a[10]=5;	f.a[11]=1;
	f.a[12]=2;	f.a[13]=6;	f.a[14]=7;	f.a[15]=3;
	f.a[16]=0;	f.a[17]=1;	f.a[18]=3;	f.a[19]=2;
	f.a[20]=4;	f.a[21]=5;	f.a[22]=7;	f.a[23]=5;

	x.a[0]= 0;	y.a[0]= 0;	z.a[0]= 0;
	x.a[1]= 1;	y.a[1]= 0;	z.a[1]= 0;
	x.a[2]= 0;	y.a[2]= 1;	z.a[2]= 0;
	x.a[3]= 1;	y.a[3]= 1;	z.a[3]= 0;
	x.a[4]= 0;	y.a[4]= 0;	z.a[4]= 1;
	x.a[5]= 1;	y.a[5]= 0;	z.a[5]= 1;
	x.a[6]= 0;	y.a[6]= 1;	z.a[6]= 1;
	x.a[7]= 1;	y.a[7]= 1;	z.a[7]= 1;

	gr->Rotate(60,40);	gr->Box();	gr->Light(true);
	gr->QuadPlot(f,x,y,z,"bgr");

/*
	gr->Clf(mglColor(0.5,1,1));
gr->SetTickLen(-0.1); gr->Axis(); gr->Box(); return 0;
mglTestMode=true;
	mreal a[100];   // let a_i = sin(4*pi*x), x=0...1
	for(int i=0;i<100;i++)a[i]=sin(4*M_PI*i/99);
	mglParse *parser = new mglParse;
	mglData &d =(parser->AddVar("dat"))->d;
	d.Set(a,100); // set data to variable
	parser->Execute(gr, "plot dat; xrange 0 1\nbox\naxis");
	// you may break script at any line do something
	// and continue after that
	parser->Execute(gr, "xlabel 'x'\nylabel 'y'\nbox");
	// also you may use cycles or conditions in script
	parser->Execute(gr, "for $0 -1 1 0.1\nline 0 0 -1 $0 'r'\nnext");
	delete parser;
	return 0;

	mglParse par;
	par.AllowSetSize = true;
	FILE *fp=fopen("test.mgl","rt");
	par.Execute(gr,fp,true);
	fclose(fp);*/
/*	gr->SetDrawReg(2,2,1);
	gr->Rotate(40,60);
	gr->Surf("sin(x*y)");
	gr->SubPlot(2,2,1);	gr->Box();*/

//	gr->Box();
//	gr->ShowImage("",true);
	return 0;
}
//=============================================================================
struct mglSample	/// Structure for list of samples
{
	const char *name;
	void (*func)(mglGraph*);
};
//-----------------------------------------------------------------------------
int mgl_cmd_smp(const void *a, const void *b)
{
	const mglSample *aa = (const mglSample *)a;
	const mglSample *bb = (const mglSample *)b;
	return strcmp(aa->name, bb->name);
}
//-----------------------------------------------------------------------------
extern mglSample samp[];
int type = 0;
int dotest  = 0;
int width  = 600;
int height = 400;
int mini = 0;
int big  = 0;
int srnd = 0;
mglData s;
//-----------------------------------------------------------------------------
static struct option longopts[] =
{
	{ "test",			no_argument,	&dotest,	1 },
	{ "srnd",			no_argument,	&srnd,		1 },
	{ "width",			required_argument,	NULL,	'w' },
	{ "height",			required_argument,	NULL,	'h' },
	{ "list",			no_argument,	NULL,		'l' },
	{ "kind",			required_argument,	NULL,	'k' },
	{ "thread",			required_argument,	NULL,	't' },
	{ "mini",			no_argument,	&mini,		1 },
	{ "big",			no_argument,	&big,		1 },
	{ "png",			no_argument,	&type,		0 },
	{ "eps",			no_argument,	&type,		1 },
	{ "svg",			no_argument,	&type,		2 },
	{ "solid",			no_argument,	&type,		3 },
	{ "jpeg",			no_argument,	&type,		4 },
	{ "idtf",			no_argument,	&type,		5 },
	{ "gif",			no_argument,	&type,		6 },
	{ "none",			no_argument,	&type,		7 },
	{ "bps",			no_argument,	&type,		8 },
	{ "u3d",			no_argument,	&type,		9 },
	{ "pdf",			no_argument,	&type,		10 },
	{ "help",			no_argument,	NULL,		'?' },
	{ NULL,				0,				NULL,		0 }
};
//-----------------------------------------------------------------------------
void usage()
{
	puts (	\
		"-png			- output png\n"					\
		"-width=num		- png picture width\n"			\
		"-height=num	- png picture height\n"			\
		"-mini			- png picture is 200x133\n"		\
		"-big			- png picture is 1200x800\n"	\
		"-idtf			- output idtf\n"				\
		"-u3d			- output u3d\n"				\
		"-pdf			- output pdf\n"				\
		"-eps			- output EPS\n"					\
		"-jpeg			- output JPEG\n"				\
		"-solid			- output solid PNG\n"			\
		"-svg			- output SVG\n"					\
		"-none			- none output\n"				\
		"-srnd			- use the same random numbers in any run\n"	\
		"-kind=name		- produce only this picture"	\
		"-thread=num	- number of threads used"		\
		"-test			- perform test\n"
		);
//	exit(0);
};
//-----------------------------------------------------------------------------
void save(mglGraph *gr,const char *name,const char *suf="")
{
//	return;
	char buf[128];
	printf("%s ",name);	fflush(stdout);
	switch(type)
	{
		case 1:	// EPS
			sprintf(buf,"%s%s.eps",name,suf);
			gr->WriteEPS(buf);
			break;
		case 2:	// SVG
			sprintf(buf,"%s%s.svg",name,suf);
			gr->WriteSVG(buf);	break;
		case 3:	// PNG
			sprintf(buf,"%s%s.png",name,suf);
			gr->WritePNG(buf,0,true);	break;
		case 4:	// JPEG
			sprintf(buf,"%s%s.jpg",name,suf);
			gr->WriteJPEG(buf);	break;
		case 5:	// IDTF
			sprintf(buf,"%s%s.idtf",name,suf);
			gr->WriteIDTF(buf);	break;
		case 6:	// GIF
			sprintf(buf,"%s%s.gif",name,suf);
			gr->WriteGIF(buf);	break;
		case 7:	// none
			break;
		case 8:	// EPS to PNG
			sprintf(buf,"%s%s.png",name,suf);
			gr->WritePNG(buf,0,false);
			break;
		case 9:	// U3D
			sprintf(buf,"%s%s.u3d",name,suf);
			gr->WriteU3D(buf);	break;
		case 10:	// PDF
			sprintf(buf,"%s%s.pdf",name,suf);
			gr->WritePDF(buf);	break;
		default:// PNG (no alpha)
			sprintf(buf,"%s%s.png",name,suf);
			gr->WritePNG(buf,0,false);	break;
	}
}
//-----------------------------------------------------------------------------
//		Sample functions
//-----------------------------------------------------------------------------
void smgl_tval(mglGraph *gr)	// ticks features
{
	gr->Axis(mglPoint(-M_PI, 0), mglPoint(M_PI, 2));
	gr->SetTicksVal('x', 6, -M_PI, "-\\pi", -M_PI/2, "-\\pi/2", 0., "0",
				 0.886, "x^*", M_PI/2, "\\pi/2", M_PI, "\\pi");
	gr->Axis();	gr->Grid();
	gr->Plot("2*cos(x^2)^2", "r2", NAN, 300);
}
//-----------------------------------------------------------------------------
void smgl_fonts(mglGraph *gr)	// ticks features
{
	float h=1.1, d=0.25;
	gr->LoadFont("STIX");		gr->Puts(mglPoint(0,h), "default font (STIX)");
	gr->LoadFont("adventor");	gr->Puts(mglPoint(0,h-d), "adventor font");
	gr->LoadFont("bonum");		gr->Puts(mglPoint(0,h-2*d), "bonum font");
	gr->LoadFont("chorus");		gr->Puts(mglPoint(0,h-3*d), "chorus font");
	gr->LoadFont("cursor");		gr->Puts(mglPoint(0,h-4*d), "cursor font");
	gr->LoadFont("heros");		gr->Puts(mglPoint(0,h-5*d), "heros font");
	gr->LoadFont("heroscn");	gr->Puts(mglPoint(0,h-6*d), "heroscn font");
	gr->LoadFont("pagella");	gr->Puts(mglPoint(0,h-7*d), "pagella font");
	gr->LoadFont("schola");		gr->Puts(mglPoint(0,h-8*d), "schola font");
	gr->LoadFont("termes");		gr->Puts(mglPoint(0,h-9*d), "termes font");
	gr->LoadFont("STIX");
}
//-----------------------------------------------------------------------------
void smgl_stick(mglGraph *gr)	// column plot
{
	if(type==5 || type==9 || type==10)	
		gr->Puts(mglPoint(0,0),"Does not work in 3D\\n for reasons I do not care to investigate till 2.0");

	gr->SetRanges(-1, 1, -1, 1, 0, 1);	gr->Light(true);
	gr->StickPlot(3, 0, 40, 30);		gr->Axis("xyz_");
	gr->Surf("exp(-10*y^2-6*x^2)");
	gr->Text(mglPoint(0.2, 0, 1.2), "z=0", "", -2);
	gr->StickPlot(3, 1, 40, 30);		gr->Axis("xyz_");
	gr->Surf("exp(-10*y^2/2-6*x^2)/sqrt(2)");
	gr->Text(mglPoint(0.2, 0, 1.2), "z=1", "", -2);
	gr->StickPlot(3, 2, 40, 30);		gr->Axis("xyz_");
	gr->Surf("exp(-10*y^2/5-6*x^2)/sqrt(5)");
	gr->Text(mglPoint(0.2, 0, 1.2), "z=2", "", -2);
	gr->Label('x',"\\tau", 0);	gr->Label('y', "\\rho");
}
//-----------------------------------------------------------------------------
void smgl_column(mglGraph *gr)	// column plot
{
	char str[32];
	for(int i=0;i<4;i++)
	{
		gr->ColumnPlot(4,i);
		gr->Box();
		sprintf(str,"Plot %d of 4",i);
		gr->Text(mglPoint(-0.5,0.5),str);
		sprintf(str,"sin(pi*x+pi*%d/2)",i);
		gr->Plot(str);
	}
}
//-----------------------------------------------------------------------------
void smgl_map(mglGraph *gr)	// example of mapping
{
	mglData a(50, 40), b(50, 40);
	gr->Puts(mglPoint(0, 0), "\\to", "C", -1.4);
	gr->Axis(mglPoint(-1,-1,-2),mglPoint(1,1,2));

	gr->SubPlot(2, 1, 0);
	a.Fill("x", gr->Min, gr->Max);	b.Fill("y", gr->Min, gr->Max);
	gr->Puts(mglPoint(0, 1.1), "\\{x, y\\}", "C", -2);		gr->Box();
	gr->Map(a, b, "brgk", 0, false);

	gr->SubPlot(2, 1, 1);
	a.Fill("(x^3+y^3)/2", gr->Min, gr->Max);
	b.Fill("(x-y)/2", gr->Min, gr->Max);
	gr->Puts(mglPoint(0, 1.1), "\\{\\frac{x^3+y^3}{2}, \\frac{x-y}{2}\\}", "C", -2);
	gr->Box();
	gr->Map(a, b, "brgk", 0, false);
}
//-----------------------------------------------------------------------------
void smgl_color_schemes(mglGraph *gr)	// Color table
{
	mglData a(256,2);	a.Fill(-1,1);
	gr->SubPlot(2,10,0,0.2);	gr->Dens(a,"kw");
	gr->Puts(mglPoint(-1.4, -0.3), "kw", "C", -8);
	gr->SubPlot(2,10,1,0.2);	gr->Dens(a,"wk");
	gr->Puts(mglPoint(-1.4, -0.3), "wk", "C", -8);
	gr->SubPlot(2,10,2,0.2);	gr->Dens(a,"kHCcw");
	gr->Puts(mglPoint(-1.4, -0.3), "kHCcw", "C", -8);
	gr->SubPlot(2,10,3,0.2);	gr->Dens(a,"kBbcw");
	gr->Puts(mglPoint(-1.4, -0.3), "kBbcw", "C", -8);
	gr->SubPlot(2,10,4,0.2);	gr->Dens(a,"kRryw");
	gr->Puts(mglPoint(-1.4, -0.3), "kRryw", "C", -8);
	gr->SubPlot(2,10,5,0.2);	gr->Dens(a,"kGgew");
	gr->Puts(mglPoint(-1.4, -0.3), "kGgew", "C", -8);
	gr->SubPlot(2,10,6,0.2);	gr->Dens(a,"BbwrR");
	gr->Puts(mglPoint(-1.4, -0.3), "BbwrR", "C", -8);
	gr->SubPlot(2,10,7,0.2);	gr->Dens(a,"BbwgG");
	gr->Puts(mglPoint(-1.4, -0.3), "BbwgG", "C", -8);
	gr->SubPlot(2,10,8,0.2);	gr->Dens(a,"GgwmM");
	gr->Puts(mglPoint(-1.4, -0.3), "GgwmM", "C", -8);
	gr->SubPlot(2,10,9,0.2);	gr->Dens(a,"UuwqR");
	gr->Puts(mglPoint(-1.4, -0.3), "UuwqR", "C", -8);
	gr->SubPlot(2,10,10,0.2);	gr->Dens(a,"QqwcC");
	gr->Puts(mglPoint(-1.4, -0.3), "QqwcC", "C", -8);
	gr->SubPlot(2,10,11,0.2);	gr->Dens(a,"CcwyY");
	gr->Puts(mglPoint(-1.4, -0.3), "CcwyY", "C", -8);
	gr->SubPlot(2,10,12,0.2);	gr->Dens(a,"bcwyr");
	gr->Puts(mglPoint(-1.4, -0.3), "bcwyr", "C", -8);
	gr->SubPlot(2,10,13,0.2);	gr->Dens(a,"bwr");
	gr->Puts(mglPoint(-1.4, -0.3), "bwr", "C", -8);
	gr->SubPlot(2,10,14,0.2);	gr->Dens(a,"BbcyrR");
	gr->Puts(mglPoint(-1.4, -0.3), "BbcyrR", "C", -8);
	gr->SubPlot(2,10,15,0.2);	gr->Dens(a,"UbcyqR");
	gr->Puts(mglPoint(-1.4, -0.3), "UbcyqR", "C", -8);
	gr->SubPlot(2,10,16,0.2);	gr->Dens(a,"BbcwyrR");
	gr->Puts(mglPoint(-1.4, -0.3), "BbcwyrR", "C", -8);
	gr->SubPlot(2,10,17,0.2);	gr->Dens(a,"bcyr");
	gr->Puts(mglPoint(-1.4, -0.3), "bcyr", "C", -8);
	gr->SubPlot(2,10,18,0.2);	gr->Dens(a,"BbcyrR|");
	gr->Puts(mglPoint(-1.4, -0.3), "BbcyrR|", "C", -8);
	gr->SubPlot(2,10,19,0.2);	gr->Dens(a,"bgr");
	gr->Puts(mglPoint(-1.4, -0.3), "bgr", "C", -8);
}
//-----------------------------------------------------------------------------
void smgl_colors(mglGraph *gr)	// Color table
{
	//#LENUQ
	gr->FaceZ(-1,	-1, 0, 0.4, 0.3, "L#");	gr->Puts(mglPoint(-0.8,-0.9), "L", "C:w", -1.4);
	gr->FaceZ(-0.6,	-1, 0, 0.4, 0.3, "E#");	gr->Puts(mglPoint(-0.4,-0.9), "E", "C:w", -1.4);
	gr->FaceZ(-0.2,	-1, 0, 0.4, 0.3, "N#");	gr->Puts(mglPoint(0,  -0.9), "N", "C:w", -1.4);
	gr->FaceZ(0.2,	-1, 0, 0.4, 0.3, "U#");	gr->Puts(mglPoint(0.4,-0.9), "U", "C:w", -1.4);
	gr->FaceZ(0.6,	-1, 0, 0.4, 0.3, "Q#");	gr->Puts(mglPoint(0.8,-0.9), "Q", "C:w", -1.4);
	//#lenuq
	gr->FaceZ(-1,	-0.7, 0, 0.4, 0.3, "l#");	gr->Puts(mglPoint(-0.8,-0.6), "l", "C:k", -1.4);
	gr->FaceZ(-0.6,	-0.7, 0, 0.4, 0.3, "e#");	gr->Puts(mglPoint(-0.4,-0.6), "e", "C:k", -1.4);
	gr->FaceZ(-0.2,	-0.7, 0, 0.4, 0.3, "n#");	gr->Puts(mglPoint(0,  -0.6), "n", "C:k", -1.4);
	gr->FaceZ(0.2,	-0.7, 0, 0.4, 0.3, "u#");	gr->Puts(mglPoint(0.4,-0.6), "u", "C:k", -1.4);
	gr->FaceZ(0.6,	-0.7, 0, 0.4, 0.3, "q#");	gr->Puts(mglPoint(0.8,-0.6), "q", "C:k", -1.4);
	//#CMYkP
	gr->FaceZ(-1,	-0.4, 0, 0.4, 0.3, "C#");	gr->Puts(mglPoint(-0.8,-0.3), "C", "C:w", -1.4);
	gr->FaceZ(-0.6,	-0.4, 0, 0.4, 0.3, "M#");	gr->Puts(mglPoint(-0.4,-0.3), "M", "C:w", -1.4);
	gr->FaceZ(-0.2,	-0.4, 0, 0.4, 0.3, "Y#");	gr->Puts(mglPoint(0,  -0.3), "Y", "C:w", -1.4);
	gr->FaceZ(0.2,	-0.4, 0, 0.4, 0.3, "k#");	gr->Puts(mglPoint(0.4,-0.3), "k", "C:w", -1.4);
	gr->FaceZ(0.6,	-0.4, 0, 0.4, 0.3, "P#");	gr->Puts(mglPoint(0.8,-0.3), "P", "C:w", -1.4);
	//#cmywp
	gr->FaceZ(-1,	-0.1, 0, 0.4, 0.3, "c#");	gr->Puts(mglPoint(-0.8, 0), "c", "C:k", -1.4);
	gr->FaceZ(-0.6,	-0.1, 0, 0.4, 0.3, "m#");	gr->Puts(mglPoint(-0.4, 0), "m", "C:k", -1.4);
	gr->FaceZ(-0.2,	-0.1, 0, 0.4, 0.3, "y#");	gr->Puts(mglPoint(0,   0), "y", "C:k", -1.4);
	gr->FaceZ(0.2,	-0.1, 0, 0.4, 0.3, "w#");	gr->Puts(mglPoint(0.4, 0), "w", "C:k", -1.4);
	gr->FaceZ(0.6,	-0.1, 0, 0.4, 0.3, "p#");	gr->Puts(mglPoint(0.8, 0), "p", "C:k", -1.4);
	//#BGRHW
	gr->FaceZ(-1,	0.2, 0, 0.4, 0.3, "B#");	gr->Puts(mglPoint(-0.8, 0.3), "B", "C:w", -1.4);
	gr->FaceZ(-0.6,	0.2, 0, 0.4, 0.3, "G#");	gr->Puts(mglPoint(-0.4, 0.3), "G", "C:w", -1.4);
	gr->FaceZ(-0.2,	0.2, 0, 0.4, 0.3, "R#");	gr->Puts(mglPoint(0,   0.3), "R", "C:w", -1.4);
	gr->FaceZ(0.2,	0.2, 0, 0.4, 0.3, "H#");	gr->Puts(mglPoint(0.4, 0.3), "H", "C:w", -1.4);
	gr->FaceZ(0.6,	0.2, 0, 0.4, 0.3, "W#");	gr->Puts(mglPoint(0.8, 0.3), "W", "C:w", -1.4);
	//#bgrhw
	gr->FaceZ(-1,	0.5, 0, 0.4, 0.3, "b#");	gr->Puts(mglPoint(-0.8, 0.6), "b", "C:k", -1.4);
	gr->FaceZ(-0.6,	0.5, 0, 0.4, 0.3, "g#");	gr->Puts(mglPoint(-0.4, 0.6), "g", "C:k", -1.4);
	gr->FaceZ(-0.2,	0.5, 0, 0.4, 0.3, "r#");	gr->Puts(mglPoint(0,   0.6), "r", "C:k", -1.4);
	gr->FaceZ(0.2,	0.5, 0, 0.4, 0.3, "h#");	gr->Puts(mglPoint(0.4, 0.6), "h", "C:k", -1.4);
	gr->FaceZ(0.6,	0.5, 0, 0.4, 0.3, "w#");	gr->Puts(mglPoint(0.8, 0.6), "w", "C:k", -1.4);
	//#brighted
	gr->FaceZ(-1,	0.8, 0, 0.4, 0.3, "r1#");	gr->Puts(mglPoint(-0.8, 0.9), "r1", "C:w", -1.4);
	gr->FaceZ(-0.6,	0.8, 0, 0.4, 0.3, "r3#");	gr->Puts(mglPoint(-0.4, 0.9), "r3", "C:w", -1.4);
	gr->FaceZ(-0.2,	0.8, 0, 0.4, 0.3, "r5#");	gr->Puts(mglPoint(0,   0.9), "r5", "C:k", -1.4);
	gr->FaceZ(0.2,	0.8, 0, 0.4, 0.3, "r7#");	gr->Puts(mglPoint(0.4, 0.9), "r7", "C:k", -1.4);
	gr->FaceZ(0.6,	0.8, 0, 0.4, 0.3, "r9#");	gr->Puts(mglPoint(0.8, 0.9), "r9", "C:k", -1.4);
}
//-----------------------------------------------------------------------------
void smgl_qo2d(mglGraph *gr)
{
	gr->Compression(true);  // try to save space
	mglData r, xx, yy, a, im(128), re(128);
	const char *ham = "p^2+q^2-x-1+i*0.5*(y+x)*(y>-x)";
	r = mglRay(ham, mglPoint(-0.7, -1), mglPoint(0, 0.5), 0.02, 2);
	gr->Plot(r.SubData(0), r.SubData(1), "k");
	gr->Axis();	gr->Label('x', "\\i x");	gr->Label('y', "\\i z");
	// now start beam tracing
	re.Fill("exp(-48*x^2)", gr->Min, gr->Max);
	a = mglQO2d(ham, re, im, r, 1, 30, &xx, &yy);
	gr->CAxis(0, 1);
	gr->Dens(xx, yy, a, "wyrRk");
	gr->Plot("-x", "k|");
	gr->Puts(mglPoint(0, 0.85), "absorption: (x+y)/2 for x+y>0");
	gr->Puts(mglPoint(0.7, -0.05), "central ray");
	gr->Title("Beam and ray tracing", "C", -1.5);
	gr->Compression(false);  //put setting back
}
//-----------------------------------------------------------------------------
void smgl_pde(mglGraph *gr)	// PDE and Ray sample
{
	gr->Compression(true);  // try to save space
	mglData a,re(128),im(128);
	gr->Axis();
	gr->Label('x', "\\i x");
	gr->Label('y', "\\i z");

	re.Fill("exp(-48*(x+0.7)^2)", gr->Min, gr->Max);
	a = mglPDE("p^2+q^2-x-1+i*0.5*(z+x)*(z>-x)", re, im,
				gr->Min, gr->Max, 0.01, 30);
	a.Transpose("yxz");
	gr->CAxis(0, 1);
	gr->Dens(a,"wyrRk");
	gr->Plot("-x", "k|", (type==5 || type==9 || type==10)?0.01:NAN);
	gr->Puts(mglPoint(0, 0.85), "absorption: (x+z)/2 for x+z>0");
	gr->Title("Equation: ik_0\\partial_zu + \\Delta u + x\\cdot u + i \\frac{x+z}{2}\\cdot u = 0", "C", -float(width)/height);
	gr->Compression(false);  //put setting back
}
//-----------------------------------------------------------------------------
void smgl_stfa(mglGraph *gr)	// STFA sample
{
	mglData a(2000), b(2000);
	a.Fill("cos(50*pi*x)*(x<-.5)+cos(100*pi*x)*(x<0)*(x>-.5)+\
				cos(200*pi*x)*(x<.5)*(x>0)+cos(400*pi*x)*(x>.5)",
				gr->Min, gr->Max);
	gr->SubPlot(1, 2, 0);
	gr->Plot(a);
	gr->Axis();
	gr->Label('x', "\\i t");

	gr->SubPlot(1, 2, 1);
	gr->STFA(a, b, 64, "BbcyrR");
	gr->Axis();
	gr->Label('x', "\\i t");
	gr->Label('y', "\\omega", 0);
}
//-----------------------------------------------------------------------------
void smgl_envelop(mglGraph *gr)	// Envelop reconstruction
{
	mglData a(1000);
	a.Fill("exp(-8*x^2)*sin(10*pi*x)", gr->Min, gr->Max);
	gr->Plot(a, "b");
	a.Envelop('x');
	gr->Plot(a, "r");
	gr->Axis();
}
//-----------------------------------------------------------------------------
void smgl_sew(mglGraph *gr)	// Phase reconstruction
{
	gr->VertexColor(false);
	mglData a(100, 100);
	a.Modify("mod((y^2-(1-x)^2)/2,0.1)");
	gr->Rotate(40, 60);
	gr->Light(true);
	gr->Alpha(true);
	gr->Surf(a, "b");
	a.Sew("xy", 0.1);
	gr->Surf(a, "r");
	gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_samplee(mglGraph *gr)	// TeX sample
{
	gr->Puts(mglPoint(0), "\\sqrt{\\frac{\\alpha^{\\gamma^2}+\\overset 1{\\big\\infty}}{\\sqrt3{2+b}}}", 0, -4);
}
//-----------------------------------------------------------------------------
void smgl_sampled(mglGraph *gr)	// arrow styles
{
	mreal a=0.1,b=0.4,c=0.5;
	gr->Line(mglPoint(a,1),mglPoint(b,1),"k-A");		gr->Puts(mglPoint(c,1),"Style 'A' or 'A\\_'","rL");
	gr->Line(mglPoint(a,0.8),mglPoint(b,0.8),"k-V");	gr->Puts(mglPoint(c,0.8),"Style 'V' or 'V\\_'","rL");
	gr->Line(mglPoint(a,0.6),mglPoint(b,0.6),"k-K");	gr->Puts(mglPoint(c,0.6),"Style 'K' or 'K\\_'","rL");
	gr->Line(mglPoint(a,0.4),mglPoint(b,0.4),"k-I");	gr->Puts(mglPoint(c,0.4),"Style 'I' or 'I\\_'","rL");
	gr->Line(mglPoint(a,0.2),mglPoint(b,0.2),"k-D");	gr->Puts(mglPoint(c,0.2),"Style 'D' or 'D\\_'","rL");
	gr->Line(mglPoint(a,0),mglPoint(b,0),"k-S");		gr->Puts(mglPoint(c,0),"Style 'S' or 'S\\_'","rL");
	gr->Line(mglPoint(a,-0.2),mglPoint(b,-0.2),"k-O");	gr->Puts(mglPoint(c,-0.2),"Style 'O' or 'O\\_'","rL");
	gr->Line(mglPoint(a,-0.4),mglPoint(b,-0.4),"k-T");	gr->Puts(mglPoint(c,-0.4),"Style 'T' or 'T\\_'","rL");
	gr->Line(mglPoint(a,-0.6),mglPoint(b,-0.6),"k-_");	gr->Puts(mglPoint(c,-0.6),"Style '\\_' or none","rL");
	gr->Line(mglPoint(a,-0.8),mglPoint(b,-0.8),"k-AS");	gr->Puts(mglPoint(c,-0.8),"Style 'AS'","rL");
	gr->Line(mglPoint(a,-1),mglPoint(b,-1),"k-_A");		gr->Puts(mglPoint(c,-1),"Style '\\_A'","rL");

	a=-1;	b=-0.7;	c=-0.6;
	gr->Line(mglPoint(a,1),mglPoint(b,1),"kAA");		gr->Puts(mglPoint(c,1),"Style 'AA'","rL");
	gr->Line(mglPoint(a,0.8),mglPoint(b,0.8),"kVV");	gr->Puts(mglPoint(c,0.8),"Style 'VV'","rL");
	gr->Line(mglPoint(a,0.6),mglPoint(b,0.6),"kKK");	gr->Puts(mglPoint(c,0.6),"Style 'KK'","rL");
	gr->Line(mglPoint(a,0.4),mglPoint(b,0.4),"kII");	gr->Puts(mglPoint(c,0.4),"Style 'II'","rL");
	gr->Line(mglPoint(a,0.2),mglPoint(b,0.2),"kDD");	gr->Puts(mglPoint(c,0.2),"Style 'DD'","rL");
	gr->Line(mglPoint(a,0),mglPoint(b,0),"kSS");		gr->Puts(mglPoint(c,0),"Style 'SS'","rL");
	gr->Line(mglPoint(a,-0.2),mglPoint(b,-0.2),"kOO");	gr->Puts(mglPoint(c,-0.2),"Style 'OO'","rL");
	gr->Line(mglPoint(a,-0.4),mglPoint(b,-0.4),"kTT");	gr->Puts(mglPoint(c,-0.4),"Style 'TT'","rL");
	gr->Line(mglPoint(a,-0.6),mglPoint(b,-0.6),"k-__");	gr->Puts(mglPoint(c,-0.6),"Style '\\_\\_'","rL");
	gr->Line(mglPoint(a,-0.8),mglPoint(b,-0.8),"k-VA");	gr->Puts(mglPoint(c,-0.8),"Style 'VA'","rL");
	gr->Line(mglPoint(a,-1),mglPoint(b,-1),"k-AV");		gr->Puts(mglPoint(c,-1),"Style 'AV'","rL");
}
//-----------------------------------------------------------------------------
void smgl_samplec(mglGraph *gr)	// error boxes
{
	mglData  x(10), y(10), ex(10), ey(10), y0(50);
	x.Modify("2*x-1 + 0.2*rnd-0.1");
	y.Modify("(2*x-1)^2 + 0.2*rnd-0.1");
	y0.Modify("(2*x-1)^2");
	ex.Modify("0.2");
	ey.Modify("0.1");

	gr->Clf();
	gr->SubPlot(2,2,0);
	gr->Error(y,ey,"ko");
	gr->Plot(y0,"r");
	gr->Axis();
	gr->Text(mglPoint(0,1.2,0),"Random \\i{y}");
	gr->SubPlot(2,2,1);
	gr->Error(x,y,ex,"ko");
	gr->Plot(y0,"r");
	gr->Axis();
	gr->Text(mglPoint(0,1.2,0),"Random \\i{x, y}");
	gr->SubPlot(2,2,2);
	gr->Error(x,y,ey,ey,"ko");
	gr->Plot(y0,"r");
	gr->Axis();
	gr->Text(mglPoint(0,1.2,0),"Random \\i{x, y} and 2d boxes");
	gr->SubPlot(2,2,3);
	gr->Text(mglPoint(0,1.2,0),"Random point in 3d space");
	gr->Rotate(40,60);
	for(int i=0;i<10;i++)
		gr->Error(mglPoint(mgl_rnd()-0.5,mgl_rnd()-0.5,mgl_rnd()-0.5), mglPoint(0.1,0.1,0.1),"bo");
	gr->Axis();
	gr->Rotate(0,0); // for unrotate in IDTF
}
//-----------------------------------------------------------------------------
void smgl_sampleb(mglGraph *gr)	// Gaussian beam
{
	gr->Alpha(true);	gr->Light(true);	gr->Light(0,mglPoint(0,0,1));
	mglData a(30,30,30), b(30,30,30);
	a.Modify("exp(-16*((z-0.5)^2+(y-0.5)^2)/(1+4*x^2))");
	b.Modify("16*((z-0.5)^2+(y-0.5)^2)*(x)/(1+4*x^2)");
	gr->CAxis(0,1);

	gr->SubPlot(2,2,0);	gr->Rotate(40,60);
	gr->VertexColor(false);
	// since we have one-color trasparent surfaces - disable (per-vertex) coloring
	gr->Surf3(a,"wgk");	gr->Box();
	gr->SubPlot(2,2,1);	gr->Rotate(40,60);
	gr->DensA(a);		gr->Box();	gr->Axis();
	gr->SubPlot(2,2,2);	gr->Rotate(40,60);
	gr->Cloud(a);		gr->Box();
	gr->SubPlot(2,2,3);	gr->Rotate(40,60);
	gr->VertexColor(false);
	// for variable transparency the only way is to disable smooth (per-vertex) coloring
	gr->Surf3A(b,a,"q");		gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_samplea(mglGraph *gr)	// flag #
{
	gr->Alpha(true);	gr->Light(true);	gr->Light(0,mglPoint(0,0,1));
	mglData a(30,20);
	a.Modify("0.6*sin(2*pi*x)*sin(3*pi*y) + 0.4*cos(3*pi*(x*y))");

	gr->SubPlot(2,2,0);	gr->Rotate(40,60);
	gr->Surf(a,"BbcyrR#");		gr->Box();
	gr->SubPlot(2,2,1);	gr->Rotate(40,60);
	gr->Dens(a,"BbcyrR#");		gr->Box();
	gr->SubPlot(2,2,2);	gr->Rotate(40,60);
	gr->Cont(a,"BbcyrR#");		gr->Box();
	gr->SubPlot(2,2,3);	gr->Rotate(40,60);
	gr->Axial(a,"BbcyrR#");		gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_sample9(mglGraph *gr)	// 2d plot
{
	gr->Light(true);	gr->Light(0,mglPoint(0,0,1));

	mglData a0(50,40);
	a0.Modify("0.6*sin(2*pi*x)*sin(3*pi*y) + 0.4*cos(3*pi*(x*y))");
	gr->SubPlot(2,2,0);	gr->Rotate(60,40);
	gr->Surf(a0);		gr->Box();

	mglData x(50,40),y(50,40),z(50,40);
	x.Modify("0.8*sin(2*pi*x)*sin(pi*y)");
	y.Modify("0.8*cos(2*pi*x)*sin(pi*y)");
	z.Modify("0.8*cos(pi*y)");
	gr->SubPlot(2,2,1);	gr->Rotate(60,40);
	gr->Surf(x,y,z,"BbwrR");		gr->Box();

	mglData a1(50,40,3);
	a1.Modify("0.6*sin(2*pi*x)*sin(3*pi*y) + 0.4*cos(3*pi*(x*y))");
	a1.Modify("0.6*cos(2*pi*x)*cos(3*pi*y) + 0.4*sin(3*pi*(x*y))",1);
	a1.Modify("0.6*cos(2*pi*x)*cos(3*pi*y) + 0.4*cos(3*pi*(x*y))",2);
	gr->SubPlot(2,2,2);	gr->Rotate(60,40);
	gr->Alpha(true);
	gr->Surf(a1);		gr->Box();

	gr->SubPlot(2,2,3);	gr->Rotate(60,40);
	gr->Dens(a1);		gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_sample8(mglGraph *gr)	// 1d plot
{
	mglData y0(50);		y0.Modify("sin(pi*(2*x-1))");
	gr->SubPlot(2,2,0);
	gr->Plot(y0);		gr->Box();

	gr->SubPlot(2,2,1);
	mglData y1(50,2);
	y1.Modify("sin(pi*2*x-pi)");	y1.Modify("cos(pi*2*x-pi)/2",1);
	gr->Plot(y1);		gr->Box();

	mglData x(50);		x.Modify("cos(pi*2*x-pi)");
	gr->Plot(x,y0,"Y+");

	gr->Plot(y1.SubData(-1,0),y1.SubData(-1,1),"q|");

	gr->SubPlot(2,2,2);	gr->Rotate(60,40);
	mglData z(50);		z.Modify("2*x-1");
	gr->Plot(x,y0,z);		gr->Box();

	mglData y2(10,3);	y2.Modify("cos(pi*(2*x-1-y))");
	y2.Modify("2*x-1",2);
	gr->Plot(y2.SubData(-1,0),y2.SubData(-1,1),y2.SubData(-1,2),"bo ");

	gr->SubPlot(2,2,3);	gr->Rotate(60,40);
	gr->Bars(x,y0,z,"ri");		gr->Box();
	
	gr->Rotate(0,0); // for unrotate in IDTF
}
//-----------------------------------------------------------------------------
void smgl_sample7(mglGraph *gr)	// smoothing
{
	mglData y0(30),y1,y2,y3;
	y0.Modify("0.4*sin(2*pi*x) + 0.3*cos(3*pi*x) - 0.4*sin(4*pi*x)+0.2*rnd");

	y1=y0;	y1.Smooth(SMOOTH_LINE_3);
	y2=y0;	y2.Smooth(SMOOTH_LINE_5);
	y3=y0;	y3.Smooth(SMOOTH_QUAD_5);

	gr->Plot(y0,"k");	gr->AddLegend("NONE","k");
	gr->Plot(y1,"r");	gr->AddLegend("LINE\\_3","r");
	gr->Plot(y2,"g");	gr->AddLegend("LINE\\_5","g");
	gr->Plot(y3,"b");	gr->AddLegend("QUAD\\_5","b");
	gr->Legend();		gr->Box();
	gr->ClearLegend();	// clear legend strings
}
//-----------------------------------------------------------------------------
void smgl_sample6(mglGraph *gr)	// differentiate
{
	mglData a(30,40);	a.Modify("x*y");
	gr->Axis(mglPoint(0,0,0),mglPoint(1,1,1));
	gr->SubPlot(2,2,0);	gr->Rotate(60,40);
	gr->Surf(a);		gr->Box();
	gr->Text(mglPoint(0.7,1,1.2),"a(x,y)");
	gr->SubPlot(2,2,1);	gr->Rotate(60,40);
	a.Diff("x");		gr->Surf(a);	gr->Box();
	gr->Text(mglPoint(0.7,1,1.2),"da/dx");
	gr->SubPlot(2,2,2);	gr->Rotate(60,40);
	a.Integral("xy");	gr->Surf(a);	gr->Box();
	gr->Text(mglPoint(0.7,1,1.2),"\\int da/dx dxdy");
	gr->SubPlot(2,2,3);	gr->Rotate(60,40);
	a.Diff2("y");	gr->Surf(a);	gr->Box();
	gr->Text(mglPoint(0.7,1,1.2),"\\int {d^2}a/dxdy dx");
}
//-----------------------------------------------------------------------------
void smgl_sample5(mglGraph *gr)	// pen styles
{
	if(type==5 || type==9 || type==10)	gr->Puts(mglPoint(0,1.2),"line styles not supported","rL");
	mreal d,x1,x2,x0,y=0.95;
	d=0.3, x0=0.2, x1=0.5, x2=0.6;
	gr->Line(mglPoint(x0,1-0*d),mglPoint(x1,1-0*d),"k-");	gr->Puts(mglPoint(x2,y-0*d),"Solid '-'","rL");
	gr->Line(mglPoint(x0,1-1*d),mglPoint(x1,1-1*d),"k|");	gr->Puts(mglPoint(x2,y-1*d),"Long Dash '|'","rL");
	gr->Line(mglPoint(x0,1-2*d),mglPoint(x1,1-2*d),"k;");	gr->Puts(mglPoint(x2,y-2*d),"Dash ';'","rL");
	gr->Line(mglPoint(x0,1-3*d),mglPoint(x1,1-3*d),"k=");	gr->Puts(mglPoint(x2,y-3*d),"Small dash '='","rL");
	gr->Line(mglPoint(x0,1-4*d),mglPoint(x1,1-4*d),"kj");	gr->Puts(mglPoint(x2,y-4*d),"Dash-dot 'j'","rL");
	gr->Line(mglPoint(x0,1-5*d),mglPoint(x1,1-5*d),"ki");	gr->Puts(mglPoint(x2,y-5*d),"Small dash-dot 'i'","rL");
	gr->Line(mglPoint(x0,1-6*d),mglPoint(x1,1-6*d),"k:");	gr->Puts(mglPoint(x2,y-6*d),"Dots ':'","rL");
	gr->Line(mglPoint(x0,1-7*d),mglPoint(x1,1-7*d),"k ");	gr->Puts(mglPoint(x2,y-7*d),"None ' '","rL");

	d=0.25; x1=-1; x0=-0.8;	y = -0.05;
	gr->Mark(mglPoint(x1,5*d),'.');		gr->Puts(mglPoint(x0,y+5*d),"'.'","rL");
	gr->Mark(mglPoint(x1,4*d),'+');		gr->Puts(mglPoint(x0,y+4*d),"'+'","rL");
	gr->Mark(mglPoint(x1,3*d),'x');		gr->Puts(mglPoint(x0,y+3*d),"'x'","rL");
	gr->Mark(mglPoint(x1,2*d),'*');		gr->Puts(mglPoint(x0,y+2*d),"'*'","rL");
	gr->Mark(mglPoint(x1,d),'s');		gr->Puts(mglPoint(x0,y+d),"'s'","rL");
	gr->Mark(mglPoint(x1,0),'d');		gr->Puts(mglPoint(x0,y),"'d'","rL");
	gr->Mark(mglPoint(x1,-d,0),'o');	gr->Puts(mglPoint(x0,y-d),"'o'","rL");
	gr->Mark(mglPoint(x1,-2*d,0),'^');	gr->Puts(mglPoint(x0,y-2*d),"'\\^'","rL");
	gr->Mark(mglPoint(x1,-3*d,0),'v');	gr->Puts(mglPoint(x0,y-3*d),"'v'","rL");
	gr->Mark(mglPoint(x1,-4*d,0),'<');	gr->Puts(mglPoint(x0,y-4*d),"'<'","rL");
	gr->Mark(mglPoint(x1,-5*d,0),'>');	gr->Puts(mglPoint(x0,y-5*d),"'>'","rL");

	d=0.25; x1=-0.5; x0=-0.3;	y = -0.05;
	gr->Mark(mglPoint(x1,5*d),'C');		gr->Puts(mglPoint(x0,y+5*d),"'\\#.'","rL");
	gr->Mark(mglPoint(x1,4*d),'P');		gr->Puts(mglPoint(x0,y+4*d),"'\\#+'","rL");
	gr->Mark(mglPoint(x1,3*d),'X');		gr->Puts(mglPoint(x0,y+3*d),"'\\#x'","rL");
	gr->Mark(mglPoint(x1,2*d),'Y');		gr->Puts(mglPoint(x0,y+2*d),"'\\#*'","rL");
	gr->Mark(mglPoint(x1,d),'S');		gr->Puts(mglPoint(x0,y+d),"'\\#s'","rL");
	gr->Mark(mglPoint(x1,0),'D');		gr->Puts(mglPoint(x0,y),"'\\#d'","rL");
	gr->Mark(mglPoint(x1,-d,0),'O');	gr->Puts(mglPoint(x0,y-d),"'\\#o'","rL");
	gr->Mark(mglPoint(x1,-2*d,0),'T');	gr->Puts(mglPoint(x0,y-2*d),"'\\#\\^'","rL");
	gr->Mark(mglPoint(x1,-3*d,0),'V');	gr->Puts(mglPoint(x0,y-3*d),"'\\#v'","rL");
	gr->Mark(mglPoint(x1,-4*d,0),'L');	gr->Puts(mglPoint(x0,y-4*d),"'\\#<'","rL");
	gr->Mark(mglPoint(x1,-5*d,0),'R');	gr->Puts(mglPoint(x0,y-5*d),"'\\#>'","rL");
}
//-----------------------------------------------------------------------------
void smgl_sample4(mglGraph *gr)	// font features
{
//	setlocale(LC_CTYPE, "ru_RU.cp1251");
//	gr->Putsw(mglPoint(0,1),L"Text can be in english ?? ?? ??????????????");
	gr->Putsw(mglPoint(0,1),L"Text can be in ASCII and in Unicode");
	gr->Puts(mglPoint(0,0.6),"It can be \\wire{wire}, \\big{big} or #r{colored}");
	gr->Puts(mglPoint(0,0.2),"One can change style in string: "
			"\\b{bold}, \\i{italic, \\b{both}}");
	gr->Puts(mglPoint(0,-0.2),"Easy to \\a{overline} or "
			"\\u{underline}");
	gr->Puts(mglPoint(0,-0.6),"Easy to change indexes ^{up} _{down} @{center}");
	gr->Puts(mglPoint(0,-1),"It parse TeX: \\int \\alpha \\cdot "
			"\\sqrt3{sin(\\pi x)^2 + \\gamma_{i_k}} dx");
}
//-----------------------------------------------------------------------------
void smgl_sample3(mglGraph *gr)	// curvilinear coordinates
{
	mglData x(50),y(50),z(50);
	y.Fill(0.5,0.5);
	x.Fill(-1,1);        // create data arrays

	gr->Axis(mglPoint(-1,-1,-1),mglPoint(1,1,1),mglPoint(-1,1,-1));
	gr->SetTicks('z', 0.5);  // set tick step to 0.5

	gr->SubPlot(2,2,0);
	gr->Rotate(60,40);
	gr->Plot(x,y,z,"r2");
	gr->Axis(); gr->Grid();
	gr->Text(mglPoint(0,1.3,1),"Cartesian");

	gr->SubPlot(2,2,1);
	gr->SetFunc("y*sin(pi*x)","y*cos(pi*x)",0);
	gr->Rotate(60,40);
	gr->Plot(x,y,z,"r2");
	gr->Axis(); gr->Grid();
	gr->Text(mglPoint(0,1.3,1),"Cylindrical");

	gr->SubPlot(2,2,2);
	gr->Rotate(60,40);
	gr->SetFunc("2*y*x","y*y - x*x",0);
	gr->Plot(x,y,z,"r2");
	gr->Axis(); gr->Grid();
	gr->Text(mglPoint(0,1.3,1),"Parabolic");

	gr->SubPlot(2,2,3);
	gr->Rotate(60,40);
	gr->SetFunc("y*sin(pi*x)","y*cos(pi*x)","x+z");
	gr->Plot(x,y,z,"r2");
	gr->Axis(); gr->Grid();
	gr->Text(mglPoint(0,1.3,1),"Spiral");
	gr->Axis(0,0,0);	// set to default Cartesian
}
//-----------------------------------------------------------------------------
void smgl_sample2(mglGraph *gr)	// axis and grid
{
	gr->SubPlot(2,2,0);
	gr->SetTicks('x', 0.4, 3);  // sets tick step to 0.4
	gr->SetTicks('y', 0.4, 3);  // and draws 3 subticks
	gr->Box();                  // should be after the ticks change
	gr->Axis("xy");
	gr->Grid();
	gr->Puts(mglPoint(0,1.3,1),"Axis and grid");

	gr->SetTicks('x');  gr->SetTicks('y'); // restore back
	gr->Axis(mglPoint(-1,-1,-1),mglPoint(1,1,1),mglPoint(0,0,0));

	gr->SubPlot(2,2,1);
	gr->Rotate(60,40);
	gr->Axis();
	gr->Label('x',"x");
	gr->Label('y',"y");
	gr->Label('z',"z");
	gr->Puts(mglPoint(0,0,1.5),"Axis and labels");

	gr->SubPlot(2,2,2);
	gr->Rotate(60,40);
	gr->SetTicks('x', 0.2); gr->SetTicks('y', 0.2);
	gr->SetTicks('z', 0.2); // too low step of ticks
	gr->Axis(mglPoint(-1,-1,-1),mglPoint(1,1,1),mglPoint(-1,-1,-1));
	gr->Axis();
	gr->Grid();
	gr->Puts(mglPoint(0,0,1.5),"Shift origin and add grid");
	gr->Puts(mglPoint(0,0,1.2),"(note, too many ticks)");

	gr->SubPlot(2,2,3);
	gr->Rotate(60,40);
	gr->SetTicks('x', -6);  // decrease the number of ticks
	gr->SetTicks('y', -6);
	gr->Axis("yz");
	gr->Label('y',"Y axis",0);
	gr->Label('z',"Z axis",0);
	gr->Puts(mglPoint(0,0,1.5),"Remove X axis, and");
	gr->Puts(mglPoint(0,0,1.2),"decrease number of ticks");
	
	gr->Rotate(0,0); // for unrotate in IDTF
}
//-----------------------------------------------------------------------------
void smgl_sample1(mglGraph *gr)	// transformation
{
	gr->SubPlot(2,2,0);  // just new axis without rotation and aspects
	gr->Box();
	gr->Text(mglPoint(-1,1.1,1),"Just box","rL");
	gr->InPlot(0.2,0.5,0.7,1,false);
	gr->Box();
	gr->Text(mglPoint(0,1.2,1),"InPlot example");
	gr->SubPlot(2,2,1);  // new axis with aspect and rotation
	gr->Rotate(60,40);
	gr->Aspect(1,1,1);
	gr->Box();
	gr->Text(mglPoint(1,1,1.5),"Rotate only","rR");
	gr->SubPlot(2,2,2);  // aspect in other direction
	gr->Rotate(60,40);
	gr->Aspect(1,1,2);
	gr->Box();
	gr->Text(mglPoint(0,0,2),"Aspect and Rotate");
	gr->SubPlot(2,2,3);  // rotation before aspect. INCORRECT !!!
	gr->Rotate(60,40);
	gr->Aspect(1,2,2);
	gr->Box();
	gr->Text(mglPoint(0,0,1.5),"Aspect in other direction");
	gr->Rotate(0,0); // for unrotate in IDTF
}
//-----------------------------------------------------------------------------
void mgls_prepare1d(mglData *y, mglData *y1=0, mglData *y2=0, mglData *x1=0, mglData *x2=0)
{
	register long i,n=50;
	if(y)	y->Create(n,3);
	if(x1)	x1->Create(n);		if(x2)	x2->Create(n);
	if(y1)	y1->Create(n);		if(y2)	y2->Create(n);
	mreal xx;
	for(i=0;i<n;i++)
	{
		xx = i/(n-1.);
		if(y)
		{
			y->a[i] = 0.7*sin(2*M_PI*xx) + 0.5*cos(3*M_PI*xx) + 0.2*sin(M_PI*xx);
			y->a[i+n] = sin(2*M_PI*xx);
			y->a[i+2*n] = cos(2*M_PI*xx);
		}
		if(y1)	y1->a[i] = 0.5+0.3*cos(2*M_PI*xx);
		if(y2)	y2->a[i] = 0.3*sin(2*M_PI*xx);
		if(x1)	x1->a[i] = xx*2-1;
		if(x2)	x2->a[i] = 0.05+0.03*cos(2*M_PI*xx);
	}
}
//-----------------------------------------------------------------------------
void smgl_plot(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	gr->Box();	gr->Plot(y);
}
//-----------------------------------------------------------------------------
void smgl_area(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	gr->Org=mglPoint();	gr->Box();	gr->Area(y);
}
//-----------------------------------------------------------------------------
void smgl_area_2(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	gr->Org=mglPoint();	gr->Box();	gr->Area(y,"cbgGyr");
}
//-----------------------------------------------------------------------------
void smgl_stem(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	gr->Org=mglPoint();	gr->Box();	gr->Stem(y,"o");
}
//-----------------------------------------------------------------------------
void smgl_step(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	gr->Box();	gr->Step(y);
}
//-----------------------------------------------------------------------------
void smgl_bars_2(mglGraph *gr)
{
	mglData ys(10,3);	ys.Modify("0.8*sin(pi*(2*x+y/2))+0.2*rnd");
	gr->Org=mglPoint();	gr->Box();	gr->Bars(ys,"cbgGyr");
}
//-----------------------------------------------------------------------------
void smgl_bars_a(mglGraph *gr)
{
	mglData ys(10,3);	ys.Modify("0.3*sin(pi*(2*x+y/2))+0.1*rnd");
	gr->Org=mglPoint();	gr->Box();	gr->Bars(ys,"a");
}
//-----------------------------------------------------------------------------
void smgl_bars_f(mglGraph *gr)
{
	mglData ys(10,2);	ys.Modify("0.24*sin(pi*(2*x+y/2))+0.06*rnd");
	gr->Org=mglPoint();	gr->Box();	gr->Bars(ys,"f");
}
//-----------------------------------------------------------------------------
void smgl_bars(mglGraph *gr)
{
	mglData ys(10,3);	ys.Modify("0.8*sin(pi*(2*x+y/2))+0.2*rnd");
	gr->Org=mglPoint();	gr->Box();	gr->Bars(ys);
}
//-----------------------------------------------------------------------------
void smgl_barh(mglGraph *gr)
{
	mglData ys(10,3);	ys.Modify("0.8*sin(pi*(2*x+y/2))+0.2*rnd");
	gr->Org=mglPoint();	gr->Box();	gr->Barh(ys);
}
//-----------------------------------------------------------------------------
void smgl_tens(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	gr->Box();	gr->Tens(y.SubData(-1,0), y.SubData(-1,1));
}
//-----------------------------------------------------------------------------
void smgl_text(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	gr->Box();	gr->Plot(y.SubData(-1,0));
	gr->Text(y,"This is very very long string drawn along a curve",":k");
	gr->Text(y,"Another string drawn above a curve","T:r");
}
//-----------------------------------------------------------------------------
void smgl_region(mglGraph *gr)
{
	mglData y1,y2;	mgls_prepare1d(0, &y1, &y2);
	gr->Box();	gr->Region(y2,y1,"r");
	gr->Plot(y1,"k2");	gr->Plot(y2,"k2");
}
//-----------------------------------------------------------------------------
void smgl_region_2(mglGraph *gr)
{
	mglData y1,y2;	mgls_prepare1d(0, &y1, &y2);
	gr->Box();	gr->Region(y2,y1,"yr");
	gr->Plot(y1,"k2");	gr->Plot(y2,"k2");
}
//-----------------------------------------------------------------------------
void smgl_mark(mglGraph *gr)
{
	mglData y,y1;	mgls_prepare1d(&y,&y1);
	gr->Box();	gr->Mark(y,y1,"bs");
}
//-----------------------------------------------------------------------------
void smgl_traj(mglGraph *gr)
{
	mglData x,y,y1,y2;	mgls_prepare1d(&y,&y1,&y2,&x);
	gr->Box();	gr->Plot(x,y);	gr->Traj(x,y,y1,y2);
}
//-----------------------------------------------------------------------------
void smgl_textmark(mglGraph *gr)
{
	mglData y,y1;	mgls_prepare1d(&y,&y1);
	gr->Box();	gr->TextMark(y,y1,"\\gamma");
}
//-----------------------------------------------------------------------------
void smgl_torus(mglGraph *gr)
{
	mglData y1,y2;	mgls_prepare1d(0,&y1,&y2);
	gr->Light(true);	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->Box();	gr->Torus(y1,y2,"pz");
}
//-----------------------------------------------------------------------------
void smgl_tube(mglGraph *gr)
{
	mglData y,y1;	mgls_prepare1d(&y,&y1);
	gr->Light(true);	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->Box();	gr->Tube(y,0.05);
}
//-----------------------------------------------------------------------------
void smgl_tube_3d(mglGraph *gr)
{
	mglData y,y1,y2,x1,x2;	mgls_prepare1d(&y,&y1,&y2,&x1,&x2);
	gr->Light(true);	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->Box();	gr->Tube(y,0.05);	gr->Tube(y1,x1,y2,x2);
}
//-----------------------------------------------------------------------------
void smgl_radar(mglGraph *gr)
{
	mglData yr(10,3);	yr.Modify("0.4*sin(pi*(2*x+y/2))+0.1*rnd");
	gr->Box();	gr->Radar(yr,"#");
}
//-----------------------------------------------------------------------------
void smgl_error(mglGraph *gr)
{
	mglData y;	mgls_prepare1d(&y);
	mglData x0(10), y0(10), ex0(10), ey0(10);
	mreal x;
	for(int i=0;i<10;i++)
	{
		x = i/9.;
		x0.a[i] = 2*x-1 + 0.1*mgl_rnd()-0.05;
		y0.a[i] = 0.7*sin(2*M_PI*x)+0.5*cos(3*M_PI*x)+0.2*sin(M_PI*x)+0.2*mgl_rnd()-0.1;
		ey0.a[i]=0.2;	ex0.a[i]=0.1;
	}
	gr->Box();	gr->Plot(y.SubData(-1,0));
	gr->Error(x0,y0,ex0,ey0,"ko");
}
//-----------------------------------------------------------------------------
void smgl_chart(mglGraph *gr)
{
	mglData ch(7,2);	for(int i=0;i<7*2;i++)	ch.a[i]=mgl_rnd()+0.1;
	gr->Light(true);	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->Box();	gr->Chart(ch,"#");
}
//-----------------------------------------------------------------------------
void smgl_ring_chart(mglGraph *gr)
{
	mglData ch(7,2);	for(int i=0;i<7*2;i++)	ch.a[i]=mgl_rnd()+0.1;
	gr->Light(true);	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->SetFunc("(y+2)/3*cos(pi*x)","(y+2)/3*sin(pi*x)","");
	gr->Box();	gr->Chart(ch,"bgr cmy#");
}
//-----------------------------------------------------------------------------
void smgl_pie_chart(mglGraph *gr)
{
	mglData ch(7,2);	for(int i=0;i<7*2;i++)	ch.a[i]=mgl_rnd()+0.1;
	gr->Light(true);	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->SetFunc("(y+1)/2*cos(pi*x)","(y+1)/2*sin(pi*x)","");
	gr->Box();	gr->Chart(ch,"bgr cmy#");
}
//-----------------------------------------------------------------------------
void mgls_prepare2d(mglData *a, mglData *b=0, mglData *v=0)
{
	register long i,j,n=50,m=40,i0;
	if(a)	a->Create(n,m);		if(b)	b->Create(n,m);
	if(v)	{	v->Create(9);	v->Fill(-1,1);	}
	mreal x,y;
	for(i=0;i<n;i++)	for(j=0;j<m;j++)
	{
		x = i/(n-1.);	y = j/(m-1.);	i0 = i+n*j;
		if(a)	a->a[i0] = 0.6*sin(2*M_PI*x)*sin(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
		if(b)	b->a[i0] = 0.6*cos(2*M_PI*x)*cos(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
	}
}
//-----------------------------------------------------------------------------
void smgl_grad(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Box();	gr->Grad(a);
	gr->Alpha(true);	gr->Dens(a);
}
//-----------------------------------------------------------------------------
void smgl_contt(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Box();	gr->Cont(a,"t");
}
//-----------------------------------------------------------------------------
void smgl_tiles(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2d(&a,&b);
	gr->Box();	gr->TileS(a,b);
}
//-----------------------------------------------------------------------------
void smgl_contd(mglGraph *gr)
{
	mglData a,v;	mgls_prepare2d(&a,0,&v);
	gr->Box();	gr->ContD(v,a);	gr->Colorbar(v);
}
//-----------------------------------------------------------------------------
void smgl_dens(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Box();	gr->Dens(a);	gr->Colorbar();
}
//-----------------------------------------------------------------------------
void smgl_surf_sl(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->Surf(a,"|");
}
//-----------------------------------------------------------------------------
void smgl_surf(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->Surf(a);
}
//-----------------------------------------------------------------------------
void smgl_stereo(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);
	gr->SubPlot(2,1,0);	gr->Rotate(40,60+3);
	gr->Box();	gr->Surf(a);
	gr->SubPlot(2,1,1);	gr->Rotate(40,60-3);
	gr->Box();	gr->Surf(a);
	gr->Rotate(0,0); // for unrotate in IDTF
}
//-----------------------------------------------------------------------------
void smgl_tile(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->Tile(a);
}
//-----------------------------------------------------------------------------
void smgl_belt(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->Belt(a);
}
//-----------------------------------------------------------------------------
void smgl_mesh(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->Mesh(a);
}
//-----------------------------------------------------------------------------
void smgl_fall(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->Fall(a);
}
//-----------------------------------------------------------------------------
void smgl_contf(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->ContF(a);
}
//-----------------------------------------------------------------------------
void smgl_cont(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);
	gr->Box();	gr->Cont(a);
}
//-----------------------------------------------------------------------------
void smgl_surfc(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2d(&a,&b);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->SurfC(a,b);
}
//-----------------------------------------------------------------------------
void smgl_boxs(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Org = mglPoint();	gr->Light(true);	gr->Rotate(40,60);
	gr->Box();	gr->Boxs(a);
}
//-----------------------------------------------------------------------------
void smgl_surf_fog(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);	gr->Fog(1);	gr->Box();
	(type==5 || type==9 || type==10)?gr->Text(mglPoint(),"Fog not supported") : gr->Surf(a);
	gr->Fog(0);
}
//-----------------------------------------------------------------------------
void smgl_surf_alpha(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);	gr->Alpha(true);
	gr->Box();	gr->Surf(a);
}
//-----------------------------------------------------------------------------
void smgl_axial(mglGraph *gr)
{
	mglData a;	mgls_prepare2d(&a);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Alpha(true);	gr->VertexColor(false);
	gr->Box();	gr->Axial(a);
}
//-----------------------------------------------------------------------------
void smgl_surfa(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2d(&a,&b);
	gr->Light(true);	gr->Rotate(40,60);
	gr->Alpha(true);	gr->VertexColor(false);
	gr->Box();	gr->SurfA(a,b);
}
//-----------------------------------------------------------------------------
void mgls_prepare3d(mglData *a, mglData *b=0)
{
	register long i,j,k,n=60,m=50,l=40,i0;
	if(a)	a->Create(n,m,l);		if(b)	b->Create(n,m,l);
	mreal x,y,z;
	for(i=0;i<n;i++)	for(j=0;j<m;j++)	for(k=0;k<l;k++)
	{
		x=2*i/(n-1.)-1;	y=2*j/(m-1.)-1;	z=2*k/(l-1.)-1;	i0 = i+n*(j+m*k);
		if(a)	a->a[i0] = -2*(x*x + y*y + z*z*z*z - z*z - 0.1);
		if(b)	b->a[i0] = 1-2*tanh((x+y)*(x+y));
	}
}
//-----------------------------------------------------------------------------
void smgl_surf3_rgbd(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->VertexColor(true);
	gr->Box();	gr->Surf3(c,"bgrd");
}
//-----------------------------------------------------------------------------
void smgl_conta(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->Box();	gr->ContA(c);
}
//-----------------------------------------------------------------------------
void smgl_dens_xyz(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->Box();	gr->DensX(c.Sum("x"),0,-1);
	gr->DensY(c.Sum("y"),0,1);	gr->DensZ(c.Sum("z"),0,-1);
}
//-----------------------------------------------------------------------------
void smgl_cont_xyz(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->VertexColor(false);
	gr->Box();	gr->ContX(c.Sum("x"),"",-1);
	gr->ContY(c.Sum("y"),"",1);
	gr->ContZ(c.Sum("z"),"",-1);
}
//-----------------------------------------------------------------------------
void smgl_contfa(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->Light(true);	gr->VertexColor(false);
	gr->Box();	gr->ContFA(c);
}
//-----------------------------------------------------------------------------
void smgl_surf3(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->Light(true);	gr->Alpha(true);
	gr->VertexColor(false);
	gr->Box();	gr->Surf3(c);
}
//-----------------------------------------------------------------------------
void smgl_surf3a(mglGraph *gr)
{
	mglData c,d;	mgls_prepare3d(&c,&d);
	gr->Rotate(40,60);	gr->Light(true);	gr->Alpha(true);
	gr->VertexColor(false);
	gr->Box();	gr->Surf3A(c,d);
}
//-----------------------------------------------------------------------------
void smgl_surf3c(mglGraph *gr)
{
	mglData c,d;	mgls_prepare3d(&c,&d);
	gr->Rotate(40,60);	gr->Light(true);	gr->Alpha(true);
	gr->VertexColor(false);
	gr->Box();	gr->Surf3C(c,d);
}
//-----------------------------------------------------------------------------
void smgl_densa(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->Alpha(true);	gr->VertexColor(false);
	gr->Org=mglPoint();	gr->Axis();
	gr->Box();			gr->DensA(c);
}
//-----------------------------------------------------------------------------
void smgl_cloud(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->Alpha(true);	gr->VertexColor(false);
	gr->Box();	gr->Cloud(c,"wyrRk");
}
//-----------------------------------------------------------------------------
void smgl_cloudp(mglGraph *gr)
{
	mglData c;	mgls_prepare3d(&c);
	gr->Rotate(40,60);	gr->Alpha(true);	gr->VertexColor(false);
	gr->Box();
	if(type==5 || type==9 || type==10)	gr->Text(mglPoint(0,0,0),"Point clouds not supported");
	else		gr->CloudP(c,"wyrRk");
}
//-----------------------------------------------------------------------------
void mgls_prepare2v(mglData *a, mglData *b)
{
	register long i,j,n=20,m=30,i0;
	if(a)	a->Create(n,m);		if(b)	b->Create(n,m);
	mreal x,y;
	for(i=0;i<n;i++)	for(j=0;j<m;j++)
	{
		x=i/(n-1.);	y=j/(m-1.);	i0 = i+n*j;
		if(a)	a->a[i0] = 0.6*sin(2*M_PI*x)*sin(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
		if(b)	b->a[i0] = 0.6*cos(2*M_PI*x)*cos(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
	}
}
//-----------------------------------------------------------------------------
void smgl_vect(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Box();	gr->Vect(a,b);
}
//-----------------------------------------------------------------------------
void smgl_vectl(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Box();	gr->VectL(a,b);
}
//-----------------------------------------------------------------------------
void smgl_vectc(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Box();	gr->VectC(a,b);
}
//-----------------------------------------------------------------------------
void smgl_flow(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Box();	gr->Flow(a,b);
}
//-----------------------------------------------------------------------------
void smgl_pipe2(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Box();	gr->Pipe(a,b);
}
//-----------------------------------------------------------------------------
void smgl_pipe(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Light(true);	gr->Compression(true);  // try to save space
	gr->Box();	gr->Pipe(a,b);
	gr->Compression(false);  //put setting back
}
//-----------------------------------------------------------------------------
void smgl_dew(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Light(true);	gr->Compression(true);  // try to save space
	gr->DoubleSided(false); // try to improve performance
	gr->Box();	gr->MeshNum=20;	gr->Dew(a,b);
	gr->DoubleSided(true);
	gr->Compression(false);  //put setting back
}
//-----------------------------------------------------------------------------
void smgl_dew2(mglGraph *gr)
{
	mglData a,b;	mgls_prepare2v(&a,&b);
	gr->Rotate(40,60);	gr->Light(true);	gr->Compression(true);  // try to save space
	gr->DoubleSided(false); // try to improve performance
	gr->Box();	gr->MeshNum=10;	gr->Dew(a,b);
	gr->DoubleSided(true);
	gr->Compression(false);  //put setting back
}
//-----------------------------------------------------------------------------
void mgls_prepare3v(mglData *ex, mglData *ey, mglData *ez)
{
	register long i,j,k,n=10,i0;
	if(!ex || !ey || !ez)	return;
	ex->Create(n,n,n);	ey->Create(n,n,n);	ez->Create(n,n,n);
	mreal x,y,z, r1,r2;
	for(i=0;i<n;i++)	for(j=0;j<n;j++)	for(k=0;k<n;k++)
	{
		x=2*i/(n-1.)-1;	y=2*j/(n-1.)-1;	z=2*k/(n-1.)-1;	i0 = i+n*(j+k*n);
		r1 = pow(x*x+y*y+(z-0.3)*(z-0.3),1.5);
		r2 = pow(x*x+y*y+(z+0.3)*(z+0.3),1.5);
		ex->a[i0]=0.2*x/r1 - 0.2*x/r2;
		ey->a[i0]=0.2*y/r1 - 0.2*y/r2;
		ez->a[i0]=0.2*(z-0.3)/r1 - 0.2*(z+0.3)/r2;
	}
}
//-----------------------------------------------------------------------------
void smgl_flow3(mglGraph *gr)
{
	mglData ex,ey,ez;	mgls_prepare3v(&ex,&ey,&ez);
	gr->Rotate(40,60);
	gr->Box();	gr->Box();	gr->Flow(ex,ey,ez,"bwr");
}
//-----------------------------------------------------------------------------
void smgl_vect3(mglGraph *gr)
{
	mglData ex,ey,ez;	mgls_prepare3v(&ex,&ey,&ez);
	gr->Rotate(40,60);
	gr->Box();	gr->Box();	gr->Vect(ex,ey,ez,"bwr");
}
//-----------------------------------------------------------------------------
void smgl_vectl3(mglGraph *gr)
{
	mglData ex,ey,ez;	mgls_prepare3v(&ex,&ey,&ez);
	gr->Rotate(40,60);
	gr->Box();	gr->Box();	gr->VectL(ex,ey,ez,"bwr");
}
//-----------------------------------------------------------------------------
void smgl_vectc3(mglGraph *gr)
{
	mglData ex,ey,ez;	mgls_prepare3v(&ex,&ey,&ez);
	gr->Rotate(40,60);
	gr->Box();	gr->Box();	gr->VectC(ex,ey,ez,"bwr");
}
//-----------------------------------------------------------------------------
void smgl_pipe3(mglGraph *gr)
{
	mglData ex,ey,ez;	mgls_prepare3v(&ex,&ey,&ez);
	gr->Rotate(40,60);	gr->Light(true);
	gr->Compression(true);	// try to save space
	gr->Clf();	gr->Box();	gr->Pipe(ex,ey,ez);
	gr->Compression(false);	// put setting back
}
//-----------------------------------------------------------------------------
void smgl_crust(mglGraph *gr)
{
	mglData pnts("hotdogs.pts");	pnts.Norm(-1,1,true);
	gr->Rotate(40,60);	gr->Light(true);	gr->Alpha(true);
	gr->Clf();	gr->Box();	gr->Crust(pnts);
}
//-----------------------------------------------------------------------------
void smgl_dots(mglGraph *gr)
{
	mglData pnts("hotdogs.pts");	pnts.Norm(-1,1,true);
	gr->Rotate(40,60);	gr->Light(true);	gr->Alpha(true);
	gr->Clf();	gr->Box();	gr->Dots(pnts);
}
//-----------------------------------------------------------------------------
void smgl_legend(mglGraph *gr)
{
	mglData f(50,3);
	mreal x;
	for(int i=0;i<50;i++)
	{
		x=i/49.;
		f.a[i]=sin(2*M_PI*x*x);
		f.a[i+50]=sin(2*M_PI*x);
		f.a[i+100]=sin(2*M_PI*sqrt(x));
	}
	gr->Axis(mglPoint(0), mglPoint(1));
	gr->Box();	gr->Plot(f);	gr->Axis("xy");
	if(type==5 || type==9 || type==10)	gr->LegendBox = false;
	gr->AddLegend("sin(\\pi {x^2})","b");	gr->AddLegend("sin(\\pi x)","g*");
	gr->AddLegend("sin(\\pi \\sqrt{x})","r+");	gr->Legend();
}
//-----------------------------------------------------------------------------
void smgl_type0(mglGraph *gr)	// TranspType = 0
{
	if(type==5 || type==9 || type==10)	return;
	gr->Alpha(true);	gr->Light(true);	gr->Light(0,mglPoint(0,0,1));
	mglData a;	mgls_prepare2d(&a);
	gr->TranspType = 0;	gr->Clf();
	gr->SubPlot(2,2,0);	gr->Rotate(40,60);	gr->Surf(a);	gr->Box();
	gr->SubPlot(2,2,1);	gr->Rotate(40,60);	gr->Dens(a);	gr->Box();
	gr->SubPlot(2,2,2);	gr->Rotate(40,60);	gr->Cont(a);	gr->Box();
	gr->SubPlot(2,2,3);	gr->Rotate(40,60);	gr->Axial(a);	gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_type1(mglGraph *gr)	// TranspType = 1
{
	if(type==5 || type==9 || type==10)	return;
	gr->Alpha(true);	gr->Light(true);	gr->Light(0,mglPoint(0,0,1));
	mglData a;	mgls_prepare2d(&a);
	gr->TranspType = 1;	gr->Clf();
	gr->SubPlot(2,2,0);	gr->Rotate(40,60);	gr->Surf(a);	gr->Box();
	gr->SubPlot(2,2,1);	gr->Rotate(40,60);	gr->Dens(a);	gr->Box();
	gr->SubPlot(2,2,2);	gr->Rotate(40,60);	gr->Cont(a);	gr->Box();
	gr->SubPlot(2,2,3);	gr->Rotate(40,60);	gr->Axial(a);	gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_type2(mglGraph *gr)	// TranspType = 2
{
	if(type==5 || type==9 || type==10)	return;
	gr->Alpha(true);	gr->Light(true);	gr->Light(0,mglPoint(0,0,1));
	mglData a;	mgls_prepare2d(&a);
	gr->TranspType = 2;	gr->Clf();
	gr->SubPlot(2,2,0);	gr->Rotate(40,60);	gr->Surf(a);	gr->Box();
	gr->SubPlot(2,2,1);	gr->Rotate(40,60);	gr->Dens(a);	gr->Box();
	gr->SubPlot(2,2,2);	gr->Rotate(40,60);	gr->Cont(a);	gr->Box();
	gr->SubPlot(2,2,3);	gr->Rotate(40,60);	gr->Axial(a);	gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_molecule(mglGraph *gr)	// example of moleculas
{
	gr->VertexColor(false);	gr->Compression(false); // per-vertex colors and compression are detrimental to transparency
	gr->DoubleSided(false); // we do not get into atoms, while rendering internal surface has negative impact on trasparency
	gr->Alpha(true);	gr->Light(true);

	gr->SubPlot(2,2,0);
	gr->StartGroup("Methane");
	gr->StartGroup("MetaneLabel");
	gr->Puts(mglPoint(0,1.2),"Methane, CH_4",0,-2);
	gr->EndGroup();
	gr->Rotate(60,120);
	gr->Sphere(mglPoint(0,0,0),0.25,"k");
	gr->Drop(mglPoint(0,0,0),mglPoint(0,0,1),0.35,"h",1,2);
	gr->Sphere(mglPoint(0,0,0.7),0.25,"g");
	gr->Drop(mglPoint(0,0,0),mglPoint(-0.94,0,-0.33),0.35,"h",1,2);
	gr->Sphere(mglPoint(-0.66,0,-0.23),0.25,"g");
	gr->Drop(mglPoint(0,0,0),mglPoint(0.47,0.82,-0.33),0.35,"h",1,2);
	gr->Sphere(mglPoint(0.33,0.57,-0.23),0.25,"g");
	gr->Drop(mglPoint(0,0,0),mglPoint(0.47,-0.82,-0.33),0.35,"h",1,2);
	gr->Sphere(mglPoint(0.33,-0.57,-0.23),0.25,"g");
	gr->EndGroup();

	gr->SubPlot(2,2,1);
	gr->StartGroup("Water");
	gr->StartGroup("WaterLabel");
	gr->Puts(mglPoint(0,1.2),"Water, H_{2}O",0,-2);
	gr->EndGroup();
	gr->Rotate(60,100);
	gr->StartGroup("Water_O");
	gr->Sphere(mglPoint(0,0,0),0.25,"r");
	gr->EndGroup();
	gr->StartGroup("Water_Bond_1");
	gr->Drop(mglPoint(0,0,0),mglPoint(0.3,0.5,0),0.3,"m",1,2);
	gr->EndGroup();
	gr->StartGroup("Water_H_1");
	gr->Sphere(mglPoint(0.3,0.5,0),0.25,"g");
	gr->EndGroup();
	gr->StartGroup("Water_Bond_2");
	gr->Drop(mglPoint(0,0,0),mglPoint(0.3,-0.5,0),0.3,"m",1,2);
	gr->EndGroup();
	gr->StartGroup("Water_H_2");
	gr->Sphere(mglPoint(0.3,-0.5,0),0.25,"g");
	gr->EndGroup();
	gr->EndGroup();

	gr->SubPlot(2,2,2);
	gr->StartGroup("Oxygen");
	gr->StartGroup("OxygenLabel");
	gr->Puts(mglPoint(0,1.2),"Oxygen, O_2",0,-2);
	gr->EndGroup();
	gr->Rotate(60,120);
	gr->Drop(mglPoint(0,0.5,0),mglPoint(0,-0.3,0),0.3,"m",1,2);
	gr->Sphere(mglPoint(0,0.5,0),0.25,"r");
	gr->Drop(mglPoint(0,-0.5,0),mglPoint(0,0.3,0),0.3,"m",1,2);
	gr->Sphere(mglPoint(0,-0.5,0),0.25,"r");
	gr->EndGroup();

	gr->SubPlot(2,2,3);
	gr->StartGroup("Ammonia");
	gr->StartGroup("AmmoniaLabel");
	gr->Puts(mglPoint(0,1.2),"Ammonia, NH_3",0,-2);
	gr->EndGroup();
	gr->Rotate(60,120);
	gr->Sphere(mglPoint(0,0,0),0.25,"b");
	gr->Drop(mglPoint(0,0,0),mglPoint(0.33,0.57,0),0.32,"n",1,2);
	gr->Sphere(mglPoint(0.33,0.57,0),0.25,"g");
	gr->Drop(mglPoint(0,0,0),mglPoint(0.33,-0.57,0),0.32,"n",1,2);
	gr->Sphere(mglPoint(0.33,-0.57,0),0.25,"g");
	gr->Drop(mglPoint(0,0,0),mglPoint(-0.65,0,0),0.32,"n",1,2);
	gr->Sphere(mglPoint(-0.65,0,0),0.25,"g");
	gr->EndGroup();
	gr->DoubleSided( true ); // put back
}
//-----------------------------------------------------------------------------
void smgl_ternary(mglGraph *gr)	// flag #
{
	mglData x(50),y(50),rx(10),ry(10), a(20,30);
	a.Modify("4*x*y");
	x.Modify("0.25*(1+cos(2*pi*x))");
	y.Modify("0.25*(1+sin(2*pi*x))");
	rx.Modify("rnd"); ry.Modify("(1-v)*rnd",rx);

	gr->Text(mglPoint(-0.8,1.3), "Ternary plot (x+y+t=1)");
	gr->Ternary(1);
	gr->Plot(x,y,"r2");
	gr->Plot(rx,ry,"q^ ");
	gr->Cont(a,"BbcyrR");
	gr->Line(mglPoint(0.5,0), mglPoint(0,0.75), "g2");
	gr->Axis(); gr->Grid("xyz","B;");
	gr->Label('x',"x comp.");
	gr->Label('y',"y comp.");
	gr->Label('t',"t comp.");
	gr->Ternary(0);
}
//-----------------------------------------------------------------------------
void smgl_quaternary(mglGraph *gr)	// flag #
{
	mglData x(50),y(50),z(50),rx(10),ry(10), a(20,30);
	a.Modify("x*y*(1-x-y)^2*30");
	x.Modify("0.25*(1-x)*(1+cos(2*pi*x))");
	y.Modify("0.25*(1-x)*(1+sin(2*pi*x))");
	z.Modify("x");

	gr->Text(mglPoint(0,1.3), "Quaternary plot (x+y+z+t=1)");
	gr->Rotate(60,70);		gr->Light(true);
	gr->Ternary(2);			gr->SetCut(true);
	gr->Plot(x,y,z,"r2");	gr->Surf(a,"BbcyrR#");
	gr->Axis(); gr->Grid();	gr->Box();
	gr->SetRotatedText(false);
	gr->Label('t',"A",1);	gr->Label('x',"B",1);
	gr->Label('y',"C",1);	gr->Label('z',"D",1);
	gr->Ternary(0);
}
//-----------------------------------------------------------------------------
void smgl_drops(mglGraph *gr)	// flag #
{
	gr->VertexColor(false);	// not strictly required, but looks better imho
	gr->Light(true);	gr->Alpha(false);
	gr->Text(mglPoint(-1,1.2),"sh=0");
	gr->Drop(mglPoint(-1,0),mglPoint(0,1),0.5,"r",0);
	gr->Text(mglPoint(-0.33,1.2),"sh=0.33");
	gr->Drop(mglPoint(-0.33,0),mglPoint(0,1),0.5,"r",0.33);
	gr->Text(mglPoint(0.33,1.2),"sh=0.67");
	gr->Drop(mglPoint(0.33,0),mglPoint(0,1),0.5,"r",0.67);
	gr->Text(mglPoint(1,1.2),"sh=1");
	gr->Drop(mglPoint(1,0),mglPoint(0,1),0.5,"r",1);
	gr->Ball(mglPoint(-1,0,1),'k');
	gr->Ball(mglPoint(-0.33,0,1),'k');
	gr->Ball(mglPoint(0.33,0,1),'k');
	gr->Ball(mglPoint(1,0,1),'k');
	gr->Line(mglPoint(-1,0,1),mglPoint(1,0,1),"b");
}
//-----------------------------------------------------------------------------
void smgl_fish(mglGraph *gr)	// flag #
{
	gr->VertexColor(false); // the model is big even without information on point colors
	gr->Compression(true);  // fishes are important, not their scales
	gr->DoubleSided(false); // we do not get into drops, while rendering internal surfaces may have negative impact on performace
	gr->Light(true);	gr->Alpha(false);
	mglData a(10,10), b(10,10), x(10,10), y(10,10);
	a.Modify("0.3*x+rnd"); x.Modify("x+0.1*rnd");
	b.Modify("0.3*y+rnd"); y.Modify("y+0.1*rnd");

	gr->Clf();
	gr->Axis(mglPoint(0,0),mglPoint(1.1,1.1));
	gr->Light(true);
	gr->Dew(x,y,a,b,"BbcyrR");
	gr->Compression(false);	gr->DoubleSided(true);
}
//-----------------------------------------------------------------------------
void smgl_mirror(mglGraph *gr)	// flag #
{
	gr->VertexColor(true); gr->TextureColor(false); // Let us use pre-lighting for this example
	mglData a(30,40),x(30),y1(40),y2(40);
	a.Modify("pi*(1-2*x)*exp(-4*y^2-4*(2*x-1)^2)");
	x.Fill(-1,1); y1.Fill(0,1); y2.Fill(0,-1);

	gr->Alpha(false);	gr->Rotate(40,60);
	gr->Light(true);	gr->Box();
	gr->Surf(x,y1,a,"r"); gr->Surf(x,y2,a,"b");
	gr->VertexColor(false); gr->TextureColor(true); // set settings back
}
//-----------------------------------------------------------------------------
void smgl_semilog(mglGraph *gr)	// semi-log axis
{
	mglData x(2000), y(2000);
	x.Modify("0.01/(x+10^(-5))"); y.Modify("sin(1/v)",x);

	gr->Axis(mglPoint(0.01,-1),mglPoint(1000,1));
	gr->SetFunc("lg(x)",0,0); gr->SetTicks('x', 0);	gr->Box();
	gr->Plot(x,y,"b2");
	gr->Axis(); gr->Grid("xy","g");
	gr->Label('x',"x",0); gr->Label('y', "y = sin 1/x",0);
}
//-----------------------------------------------------------------------------
void smgl_loglog(mglGraph *gr)	// log-log axis
{
	mglData x(2000), y(2000);
	x.Modify("pow(10,6*x-3)"); y.Modify("sqrt(1+v^2)",x);

	gr->Axis(mglPoint(0.001,0.1),mglPoint(1000,1000));
	gr->SetFunc("lg(x)","lg(y)",0);
	gr->SetTicks('x', 0);
	gr->SetTicks('y', 0);
	gr->Box();	gr->Axis(); gr->Grid("xy","g;");
	gr->Plot(x,y,"b2");
	gr->Label('x',"x",0); gr->Label('y', "y=\\sqrt{1+x^2}",0);
}
//-----------------------------------------------------------------------------
void smgl_fit(mglGraph *gr)	// nonlinear fitting
{
	mglData rnd(100), in(100), res;
	rnd.Fill("0.4*rnd+0.1+sin(2*pi*x)", gr->Min, gr->Max);
	in.Fill("0.3+sin(2*pi*x)", gr->Min, gr->Max);

	gr->Axis(mglPoint(-1,-2), mglPoint(1,2));
	gr->Plot(rnd, ". ");
	gr->Box();

	mreal ini[3] = {1,1,3};
	gr->Fit(res, rnd, "a+b*sin(c*x)", "abc", ini);
	gr->Plot(res, "r");
	gr->Plot(in, "b");
	gr->Text(mglPoint(-1, -1.3), "fitted:", "L:r", -1);
	gr->PutsFit(mglPoint(0, -1.8), "y = ", "C:r", -1);
	gr->Text(mglPoint(0, 2.2), "initial: y = 0.3+sin(2\\pi x)", "C:b", -1);
	gr->Axis(mglPoint(-1,-1,-1),mglPoint(1,1,1),mglPoint(0,0,0));
}
//-----------------------------------------------------------------------------
#include <mgl/mgl_parse.h>
void smgl_parser(mglGraph *gr)	// example of MGL parsing
{
	mreal a[100];   // let a_i = sin(4*pi*x), x=0...1
	for(int i=0;i<100;i++)a[i]=sin(4*M_PI*i/99);
	mglParse *parser = new mglParse;
	mglData &d =(parser->AddVar("dat"))->d;
	d.Set(a,100); // set data to variable
	parser->Execute(gr, "plot dat; xrange 0 1\nbox\naxis");
	// you may break script at any line do something
	// and continue after that
	parser->Execute(gr, "xlabel 'x'\nylabel 'y'\nbox");
	// also you may use cycles or conditions in script
	parser->Execute(gr, "for $0 -1 1 0.1\nline 0 0 -1 $0 'r'\nnext");
	delete parser;
}
//-----------------------------------------------------------------------------
void smgl_2_axis(mglGraph *gr)	// 2 axis
{
	mglData y1,y2;	mgls_prepare1d(0,&y2,&y1);
	gr->Axis(mglPoint(-1,-1,-1),mglPoint(1,1,1),mglPoint(-1,-1,-1));
	gr->Axis();	gr->Label('y',"axis 1",0);	gr->Plot(y1,"b");
	// set up second axis
	gr->Axis(mglPoint(0,0,0),mglPoint(1,1,1),mglPoint(1,1,1));
	gr->Axis();	gr->Label('y',"axis 2",0);	gr->Stem(y2,"r");
}
//-----------------------------------------------------------------------------
void smgl_flow_dens(mglGraph *gr)	// flow threads and density plot
{
	mglData a,b,d;	mgls_prepare2v(&a,&b);	d = a;
	for(int i=0;i<a.nx*a.ny;i++)	d.a[i] = hypot(a.a[i],b.a[i]);
	gr->Flow(a,b,"br",5,true,(type==5 || type==9 || type==10)?-0.99:NAN);
	gr->Dens(d,"BbcyrR");	gr->Box();
}
//-----------------------------------------------------------------------------
void smgl_surf_cont(mglGraph *gr)	// contour lines over surface
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);
	gr->Box();	gr->Surf(a,"kw");
	gr->CAxis(-1,0);	gr->Cont(a,"w");
	gr->CAxis( 0,1);	gr->Cont(a,"k");
}
//-----------------------------------------------------------------------------
void smgl_mesh_cont(mglGraph *gr)	// contours under mesh
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);
	gr->Box();	gr->Mesh(a);	gr->Cont(a, 0, 7, -1);
}
//-----------------------------------------------------------------------------
void smgl_surf_cont_y(mglGraph *gr)	// contours on the surface
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);	gr->Light(true);
	gr->Box();	gr->Surf(a);	gr->Cont(a,"y");
}
//-----------------------------------------------------------------------------
void smgl_surf_cont_fog(mglGraph *gr)	// contours on the surface in fog
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);	gr->Light(true);	gr->Fog(1,0.1);
	gr->Box();	gr->Surf(a);	gr->Cont(a,"y");
}
//-----------------------------------------------------------------------------
void smgl_surf_caxis(mglGraph *gr)	// caxis and the surface
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);	gr->Light(true);
	gr->CAxis(0,1);	gr->Box();	gr->Surf(a);
}
//-----------------------------------------------------------------------------
void smgl_surf_cut(mglGraph *gr)	// cutting
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);	gr->Light(true);
	gr->Axis(mglPoint(-1,-1,0),mglPoint(1,1,1));	gr->Cut=false;
	gr->Box();	gr->Surf(a);
}
//-----------------------------------------------------------------------------
void smgl_several_light(mglGraph *gr)	// several light sources
{
	mglData a;	mgls_prepare2d(&a);
	gr->Rotate(40,60);	gr->Light(true);
	gr->Light(1,mglPoint(0,1,0),'c');	gr->Light(2,mglPoint(1,0,0),'y');
	gr->Light(3,mglPoint(0,-1,0),'m');
	gr->Box();	gr->Surf(a,"h");
	gr->Light(1,false);	gr->Light(2,false);	gr->Light(3,false);
}
//-----------------------------------------------------------------------------
void mgls_preparecc(mglData *c)
{
	register long i,j,k,n=61,m=51,l=40,i0;
	if(!c)	return;		c->Create(n,m,l);
	mreal x,y,z;
	for(i=0;i<n;i++)	for(j=0;j<m;j++)	for(k=0;k<l;k++)
	{
		x=2*i/(n-1.)-1;	y=2*j/(m-1.)-1;	z=2*k/(l-1.)-1;	i0 = i+n*(j+m*k);
		c->a[i0] = -2*(x*x + y*y + z*z*z*z - z*z - 0.1);
	}
}
//-----------------------------------------------------------------------------
void smgl_cutminmax2(mglGraph *gr)	// CutMin CutMax example
{
	mglData c;	mgls_preparecc(&c);
	mglData v(10);	v.Fill(-0.5,1);
	gr->Rotate(40,60);	gr->Light(true);
	gr->VertexColor(false);	gr->Compression(false);
	gr->CutMin = mglPoint(0,-1,-1);	gr->CutMax = mglPoint(1,0,1.1);
	gr->Box();	gr->Surf3(-0.5,c);
	gr->ContF3(v,c,'x',-1);	gr->ContF3(v,c,'y',-1);
	gr->ContF3(v,c,'z',0);	gr->ContF3(v,c,'z',39);
}
//-----------------------------------------------------------------------------
void smgl_cutminmax(mglGraph *gr)	// CutMin CutMax example
{
	mglData c;	mgls_preparecc(&c);
	gr->Rotate(40,60);	gr->Light(true);	gr->Alpha(true);
	gr->VertexColor(false);	gr->Compression(false);
	gr->CutMin = mglPoint(0,-1,-1);	gr->CutMax = mglPoint(1,0,1.1);
	gr->Box();	gr->Surf3(c);
}
//-----------------------------------------------------------------------------
void smgl_surf3_cutoff(mglGraph *gr)	// CutMin CutMax example
{
	mglData c;	mgls_preparecc(&c);
	gr->Rotate(40,60);	gr->Light(true);	gr->Alpha(true);
	gr->VertexColor(false);	gr->Compression(false);
	gr->CutOff("(z>(x+0.5*y-1)^2-1) & (z>(x-0.5*y-1)^2-1)");
	gr->Box();	gr->Surf3(c);
}
//-----------------------------------------------------------------------------
void smgl_boxplot(mglGraph *gr)	// flow threads and density plot
{
	mglData a(10,7);	a.Modify("(2*rnd-1)^3/2");
	gr->Box();	gr->BoxPlot(a);	gr->Plot(a," ko");
}
//-----------------------------------------------------------------------------
int main(int argc,char **argv)
{
	const char *suf = "";
	char name[256]="";
	int ch;
	mglGraphIDTF u3d;
	mglGraphZB zb;
	mglGraphPS ps;
	mglGraphAB *gr = NULL;
	mglSample *s=samp;
	while(( ch = getopt_long_only(argc, argv, "", longopts, NULL)) != -1)
		switch(ch)
		{
			case 0:		break;
			case 'w':	width =atoi(optarg);	break;
			case 'h':	height=atoi(optarg);	break;
			case 'k':	strcpy(name, optarg);	break;
			case 't':	mglNumThr=atoi(optarg);	break;
			case 'l':
				while(s->name[0])	{	printf("%s ",s->name);	s++;	}
				printf("\n");	return 0;
			case '?':
			default:	usage();	return 0;
		}

	if(type==5 || type==9 || type==10)
	{
		u3d.unrotate_flag = true;
		gr = &u3d;
	}
	else 
	{
		if(type==1 || type==2 || type==8)	gr = &ps;
	else				gr = &zb;
	}

	if(mini)		{	gr->SetSize(200,133);	suf = "_sm";	}
	else if(big)
	{	gr->SetSize(1200,800);	suf = "_lg";	gr->BaseLineWidth = 2;	}
	else	gr->SetSize(width,height);

	if(dotest)
	{
		mglTestMode=true;	test(gr);
		gr->WriteEPS("test.eps");	gr->WritePNG("test.png","",false);
		return 0;
	}

	if(srnd)	mgl_srnd(1);
	gr->VertexColor(false);	gr->TextureColor(true);	gr->Compression(false);
	if(name[0]==0)	while(s->name[0])	// all samples
	{
		gr->DefaultPlotParam();	gr->Clf();
		s->func(gr);	save(gr, s->name, suf);
		fflush(stdout);	s++;
	}
	else	// manual sample
	{
		mglSample tst;	tst.name=name;
		int i=0;
		for(i=0;samp[i].name[0];i++);	// determine the number of samples
		s = (mglSample *) bsearch(&tst, samp, i, sizeof(mglSample), mgl_cmd_smp);
		if(s)
		{
			gr->DefaultPlotParam();	gr->Clf();
			s->func(gr);	save(gr, s->name, suf);
		}
		else	printf("no sample %s\n",name);
	}
	printf("\n");	return 0;
}
//-----------------------------------------------------------------------------
mglSample samp[] = {
	{"2_axis", smgl_2_axis},
	{"area", smgl_area},
	{"area_2", smgl_area_2},
	{"axial", smgl_axial},
	{"barh", smgl_barh},
	{"bars", smgl_bars},
	{"bars_2", smgl_bars_2},
	{"bars_a", smgl_bars_a},
	{"bars_f", smgl_bars_f},
	{"belt", smgl_belt},
	{"boxplot", smgl_boxplot},
	{"boxs", smgl_boxs},
	{"chart", smgl_chart},
	{"cloud", smgl_cloud},
	{"cloudp", smgl_cloudp},
	{"color_schemes", smgl_color_schemes},
	{"colors", smgl_colors},
	{"column",	smgl_column},
	{"cont", smgl_cont},
	{"cont_xyz", smgl_cont_xyz},
	{"conta", smgl_conta},
	{"contd", smgl_contd},
	{"contf", smgl_contf},
	{"contfa", smgl_contfa},
	{"contt", smgl_contt},
	{"crust", smgl_crust},
	{"cutminmax", smgl_cutminmax},
	{"cutminmax2", smgl_cutminmax2},
	{"dens", smgl_dens},
	{"dens_xyz", smgl_dens_xyz},
	{"densa", smgl_densa},
	{"dew", smgl_dew},
	{"dew2", smgl_dew2},
	{"dots", smgl_dots},
	{"drops", smgl_drops},
	{"envelop", smgl_envelop},
	{"error", smgl_error},
	{"fall", smgl_fall},
	{"fish", smgl_fish},
	{"fit", smgl_fit},
	{"flow", smgl_flow},
	{"flow3", smgl_flow3},
	{"flow_dens", smgl_flow_dens},
	{"fonts", smgl_fonts},
	{"grad", smgl_grad},
	{"legend", smgl_legend},
	{"loglog", smgl_loglog},
	{"map",		smgl_map},
	{"mark", smgl_mark},
	{"mesh", smgl_mesh},
	{"mesh_cont", smgl_mesh_cont},
	{"mirror", smgl_mirror},
	{"molecule", smgl_molecule},
	{"parser", smgl_parser},
	{"pde", smgl_pde},
	{"pie_chart", smgl_pie_chart},
	{"pipe", smgl_pipe},
	{"pipe2", smgl_pipe2},
	{"pipe3", smgl_pipe3},
	{"plot", smgl_plot},
	{"qo2d", smgl_qo2d},
	{"quaternary", smgl_quaternary},
	{"radar", smgl_radar},
	{"region", smgl_region},
	{"region_2", smgl_region_2},
	{"ring_chart", smgl_ring_chart},
	{"sample1", smgl_sample1},
	{"sample2", smgl_sample2},
	{"sample3", smgl_sample3},
	{"sample4", smgl_sample4},
	{"sample5", smgl_sample5},
	{"sample6", smgl_sample6},
	{"sample7", smgl_sample7},
	{"sample8", smgl_sample8},
	{"sample9", smgl_sample9},
	{"samplea", smgl_samplea},
	{"sampleb", smgl_sampleb},
	{"samplec", smgl_samplec},
	{"sampled", smgl_sampled},
	{"samplee", smgl_samplee},
	{"semilog", smgl_semilog},
	{"several_light", smgl_several_light},
	{"sew", smgl_sew},
	{"stem", smgl_stem},
	{"step", smgl_step},
	{"stereo", smgl_stereo},
	{"stfa", smgl_stfa},
	{"stick", smgl_stick},
	{"surf", smgl_surf},
	{"surf3", smgl_surf3},
	{"surf3_cutoff", smgl_surf3_cutoff},
	{"surf3_rgbd", smgl_surf3_rgbd},
	{"surf3a", smgl_surf3a},
	{"surf3c", smgl_surf3c},
	{"surf_alpha", smgl_surf_alpha},
	{"surf_caxis", smgl_surf_caxis},
	{"surf_cont", smgl_surf_cont},
	{"surf_cont_fog", smgl_surf_cont_fog},
	{"surf_cont_y", smgl_surf_cont_y},
	{"surf_cut", smgl_surf_cut},
	{"surf_fog", smgl_surf_fog},
	{"surf_sl", smgl_surf_sl},
	{"surfa", smgl_surfa},
	{"surfc", smgl_surfc},
	{"tens", smgl_tens},
	{"ternary", smgl_ternary},
	{"text", smgl_text},
	{"textmark", smgl_textmark},
	{"tile", smgl_tile},
	{"tiles", smgl_tiles},
	{"torus", smgl_torus},
	{"traj", smgl_traj},
	{"tube", smgl_tube},
	{"tube_3d", smgl_tube_3d},
	{"tval",	smgl_tval},
	{"type0", smgl_type0},
	{"type1", smgl_type1},
	{"type2", smgl_type2},
	{"vect", smgl_vect},
	{"vect3", smgl_vect3},
	{"vectc", smgl_vectc},
	{"vectc3", smgl_vectc3},
	{"vectl", smgl_vectl},
	{"vectl3", smgl_vectl3},
	{"", NULL}};
