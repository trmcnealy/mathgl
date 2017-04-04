/* main.cpp is part of UDAV
 * Copyright (C) 2007-2014 Alexey Balakin <mathgl.abalakin@gmail.ru>
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
#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <getopt.h>
#include "mgllab.h"
#include <Fl/Fl_Spinner.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Select_Browser.H>
#include <Fl/Fl_Printer.H>
//-----------------------------------------------------------------------------
#ifndef MGL_DOC_DIR
#ifdef WIN32
#define MGL_DOC_DIR ""
#else
#define MGL_DOC_DIR "/usr/local/share/doc/mathgl/"
#endif
#endif
//-----------------------------------------------------------------------------
//int num_windows = 0, auto_exec=1, plastic_scheme=1, internal_font=0;
int num_windows = 0;
int auto_exec;
int exec_save;
int highlight;
int mouse_zoom;
std::string docdir;
std::string helpname;
std::string fontname;
int lang;
int scheme;
std::string lastfiles[5];
Fl_Preferences pref(Fl_Preferences::USER,"abalakin","mgllab");
//-----------------------------------------------------------------------------
void set_scheme_lang(int s, int l)
{
	static const char *sch[4]={"base","gtk+","plastic","gleam"};
	static const char *loc[3]={"C.UTF8",	"ru_RU.utf8",	"ru_RU.cp1251"};
	if(s<0 || s>3)	s=1;
	if(l<0 || l>2)	l=1;
	setlocale(LC_CTYPE, loc[l]);
	Fl::scheme(sch[s]);
	scheme = s;	lang = l;
	static const char *hlp[3]={"mgl_en.html#","mgl_ru.html#", "mgl_ru.html#"};
#ifdef WIN32
	char sep = '\\';
#else
	char sep = '/';
#endif
	helpname = docdir+sep+hlp[l];
}
//-----------------------------------------------------------------------------
void save_pref()
{
	pref.set("locale",lang);
	pref.set("scheme",scheme);
	pref.set("help_dir",docdir.c_str());
	pref.set("auto_exec",auto_exec);
	pref.set("exec_save",exec_save);
	pref.set("highlight",highlight);
	pref.set("mouse_zoom",mouse_zoom);
	pref.set("font_kind",font_kind);
	pref.set("font_size",font_size);
	pref.set("font_name",fontname.c_str());
	pref.set("fname1",lastfiles[0].c_str());
	pref.set("fname2",lastfiles[1].c_str());
	pref.set("fname3",lastfiles[2].c_str());
	pref.set("fname4",lastfiles[3].c_str());
	pref.set("fname5",lastfiles[4].c_str());
}
//-----------------------------------------------------------------------------
void load_pref(ScriptWindow *w)
{
	static char *s=0;
	pref.get("locale",lang,1);
	pref.get("scheme",scheme,2);
	pref.get("help_dir",s,MGL_DOC_DIR);
	if(s)	{	docdir=s;	free(s);	}
	pref.get("auto_exec",auto_exec,1);
	pref.get("exec_save",exec_save,1);
	pref.get("highlight",highlight,1);
	pref.get("mouse_zoom",mouse_zoom,0);
	pref.get("font_kind",font_kind,1);
	pref.get("font_size",font_size,14);
	set_style(font_kind, font_size);
	pref.get("font_name",s,"");
	if(s)	{	fontname=s;	free(s);	}
	if(w && w->graph)
		mgl_load_font(w->graph->get_graph(),fontname.c_str(),NULL);
	pref.get("fname1",s,"");	if(s)	{	lastfiles[0]=s;	free(s);	}
	pref.get("fname2",s,"");	if(s)	{	lastfiles[1]=s;	free(s);	}
	pref.get("fname3",s,"");	if(s)	{	lastfiles[2]=s;	free(s);	}
	pref.get("fname4",s,"");	if(s)	{	lastfiles[3]=s;	free(s);	}
	pref.get("fname5",s,"");	if(s)	{	lastfiles[4]=s;	free(s);	}
	set_scheme_lang(scheme,lang);	// NOTE: must be after setting docdir
	example_cb(NULL, w);	w->graph->parent()->show();
}
//-----------------------------------------------------------------------------
void set_title(Fl_Window* w)
{
	static std::string title;
	if (filename.empty()) title=mgl_gettext("Untitled");
	else
	{
		size_t sep = filename.find_last_of('/');
#ifdef WIN32
		if(sep==std::string::npos)
			sep = filename.find_last_of('\\');
#endif
		if(sep!=std::string::npos)	title = filename.substr(sep+1);
		else	title = filename;
	}
	if(changed)	title += " *";
	title = title + " - mgllab";
	w->label(title.c_str());
}
//-----------------------------------------------------------------------------
void close_dlg_cb(Fl_Widget *, void *v)	{	((Fl_Window *)v)->hide();	}
//-----------------------------------------------------------------------------
void fname_cb(Fl_Widget*, void *v)
{
	ScriptWindow* e = (ScriptWindow*)v;
	char *file = fl_file_chooser(mgl_gettext("Insert File Name?"), mgl_gettext("All Files (*)"), 0);
	if(file)
	{
		char *str = new char[strlen(file)+4];
		snprintf(str,strlen(file)+4," '%s'",file);
		e->editor->insert(str);
		delete []str;
	}
}
//-----------------------------------------------------------------------------
void new_cb(Fl_Widget*, void*)
{
	if (!check_save()) return;
	filename[0] = '\0';
	textbuf->select(0, textbuf->length());
	textbuf->remove_selection();
	changed = 0;
	textbuf->call_modify_callbacks();
}
//-----------------------------------------------------------------------------
void open_cb(Fl_Widget*, void *v)
{
	if (!check_save()) return;
	char *lastname=0;
	char *newfile = fl_file_chooser(mgl_gettext("Open File?"),
		mgl_gettext("MGL files (*.mgl)\tDAT files (*.{dat,csv})\tAll files (*)"), filename.c_str());
	if(lastname)	free(lastname);
	if(newfile != NULL)
	{
		ScriptWindow* e = (ScriptWindow*)v;
		load_file(newfile, -1,e);
		if(auto_exec)	e->graph->update();
	}
}
//-----------------------------------------------------------------------------
void close_cb(Fl_Widget*, void* v)
{
	Fl_Window* w = (Fl_Window*)v;
	if (num_windows == 1 && !check_save())	return;

	w->hide();
	textbuf->remove_modify_callback(changed_cb, w);
	delete w;
	num_windows--;
	if (!num_windows) exit(0);
}
//-----------------------------------------------------------------------------
void quit_cb(Fl_Widget*, void*)
{
	if (changed && !check_save())	return;
	exit(0);
}
//-----------------------------------------------------------------------------
void save_cb(Fl_Widget*w, void*v)
{
	if(filename.empty())	{	saveas_cb(w,v);	return;	}	// No filename - get one!
	else save_file(filename.c_str(),(ScriptWindow*)v);
}
//-----------------------------------------------------------------------------
void saveas_cb(Fl_Widget*, void *v)
{
	char *newfile, *fname=0;
	FILE *fp=0;
	while(1)
	{
		newfile = fl_file_chooser(mgl_gettext("Save File As?"), "*.mgl", filename.c_str());
		if(!newfile || !newfile[0])	break;
		if(!strchr(newfile,'.'))
		{
			if(fname)	delete []fname;
			fname = new char[strlen(newfile)+5];
			strcpy(fname,newfile);	strcat(fname,".mgl");
			newfile = fname;
		}
		fp = fopen(newfile,"r");
		if(fp)
		{
			fclose(fp);
			if(fl_choice(mgl_gettext("File is exesist. Overwrite it?"),0,mgl_gettext("No"),mgl_gettext(" Yes "))==2)
				break;
		}
		else	break;
	}
	if (newfile != NULL)	save_file(newfile, (ScriptWindow*)v);
	if(fname)	delete []fname;
}
//-----------------------------------------------------------------------------
ScriptWindow *new_view();
void view_cb(Fl_Widget*, void*)
{	Fl_Window* w = new_view();	w->show();	}
//-----------------------------------------------------------------------------
void hint_cb(Fl_Widget*, void*)	{}
void lastfile1_cb(Fl_Widget*, void *v)	{	load_file(lastfiles[0].c_str(),-1,(ScriptWindow*)v);	}
void lastfile2_cb(Fl_Widget*, void *v)	{	load_file(lastfiles[1].c_str(),-1,(ScriptWindow*)v);	}
void lastfile3_cb(Fl_Widget*, void *v)	{	load_file(lastfiles[2].c_str(),-1,(ScriptWindow*)v);	}
void lastfile4_cb(Fl_Widget*, void *v)	{	load_file(lastfiles[3].c_str(),-1,(ScriptWindow*)v);	}
void lastfile5_cb(Fl_Widget*, void *v)	{	load_file(lastfiles[4].c_str(),-1,(ScriptWindow*)v);	}
//-----------------------------------------------------------------------------
void print_plot_cb(Fl_Widget*,void *v)
{
	ScriptWindow *w = (ScriptWindow*)v;
	Fl_Printer *p = new Fl_Printer;
	p->start_job(1);	p->start_page();
	int wp,hp, ww=w->graph->FMGL->w(), hh=w->graph->FMGL->h();
	p->printable_rect(&wp,&hp);
	double s=1, sw=double(wp)/ww, sh=double(hp)/hh;
	if(sw<s)	s=sw;
	if(sh<s)	s=sh;
//	if(sw<sh)	p->rotate(90);	// TODO add rotation ???
	p->scale(s,s);
	p->print_widget(w->graph->FMGL);
	p->end_page();		p->end_job();
	delete p;
}
//-----------------------------------------------------------------------------
Fl_Menu_Item menuitems[] = {
	{"File", 0, 0, 0, FL_SUBMENU},
		{"New script", 0, new_cb},
		{"Open file ...", FL_CTRL+'o', open_cb},
		{"Save file", FL_CTRL+'s', save_cb},
		{"Save as ...", 0, saveas_cb, 0, FL_MENU_DIVIDER},
		{"Print plot", 0, print_plot_cb, 0, FL_MENU_DIVIDER},
		{"Recent files", 0, 0, 0, FL_SUBMENU|FL_MENU_DIVIDER},
			{"1.", 0, lastfile1_cb},
			{"2.", 0, lastfile2_cb},
			{"3.", 0, lastfile3_cb},
			{"4.", 0, lastfile4_cb},
			{"5.", 0, lastfile5_cb},
			{0},
		{"Exit", 0, quit_cb},
		{0},
	{"Edit", 0, 0, 0, FL_SUBMENU},
		{"Undo", FL_CTRL+'z', undo_cb},
		{"Cut text", FL_CTRL+'x', cut_cb},
		{"Copy text", FL_CTRL+'c', copy_cb},
		{"Paste text", FL_CTRL+'v', paste_cb},
		{"Select all", FL_CTRL+'a', select_all_cb, 0, FL_MENU_DIVIDER},
		{"Find|Replace", FL_CTRL+'f', find_dlg_cb},
		{"Find next", FL_F+3, find_next_cb, 0, FL_MENU_DIVIDER},
		{"Insert", 0, 0, 0, FL_SUBMENU},
			{"File path", FL_META+'p', ins_path_cb},
			{"Folder path", 0, ins_fname_cb},
			{"Command", FL_META+'c', newcmd_dlg_cb},
			{"Inplot", FL_META+'i', inplot_dlg_cb},
			{"Fitted formula", FL_META+'f', ins_fits_cb},
			{"Plot style", 0, style_dlg_cb},
			{"Option(s)", FL_META+'o', option_dlg_cb},
			{0},
	// TODO{"Selection", 0,  0, 0, FL_SUBMENU|FL_MENU_DIVIDER},
		// TODO{"Hide", 0,  0},
		// TODO{"Delete", 0,  0},
		// TODO{"Move up", 0,  0},
		// TODO{"Move down", 0,  0},
		// TODO{"Show hidden", FL_F+8,  0, 0, FL_MENU_TOGGLE},
		{0},
	{"Graphics", 0, 0, 0, FL_SUBMENU},
		{0},
	{"Setup", 0, 0, 0, FL_SUBMENU},
		{"Properties", 0, prop_dlg_cb},
		{"Set arguments", 0, args_dlg_cb},
		{"Set animation", 0, animate_dlg_cb},
		{"Plot setup", FL_META+'g', setup_dlg_cb, 0, FL_MENU_DIVIDER},
		{"Calculator", FL_F+4, calc_dlg_cb},
		{"Messages", FL_F+2, message_cb},
		{0},
	{"Help", 0, 0, 0, FL_SUBMENU},
		{"Help", FL_F+1, help_cb},
		{"Hints", 0, hint_dlg_cb},
		{"About", 0, about_cb},
		{0},
	{0}
};
//-----------------------------------------------------------------------------
void mem_upd_cb(Fl_Widget *, void *v)
{	((ScriptWindow*)v)->mem_init();	}
//-----------------------------------------------------------------------------
extern Fl_RGB_Image image_udav;
ScriptWindow *new_view()
{
	Fl_Group *gg;
	ScriptWindow *w = new ScriptWindow(930, 510, mgl_gettext("Untitled - mgllab"));
	w->begin();
	w->menu = new Fl_Menu_Bar(0, 0, 930, 30);
	w->menu->copy(menuitems, w);
	w->label(mgl_gettext("Untitled - mgllab"));

	Fl_Tile *t = new Fl_Tile(0,30,930,455);
	add_editor(w);

	w->rtab = new Fl_Tabs(300,30,630,455,0);
	w->gplot = new Fl_Group(300,30,630,430,mgl_gettext("Canvas"));
	w->graph = new Fl_MGLView(300,30,630,430,mgl_gettext("Canvas"));
	w->gplot->resizable(w->graph);	w->gplot->end();
	w->ghelp = new Fl_Group(300,30,630,430,mgl_gettext("Help"));
	add_help(w);	w->ghelp->end();	w->ghelp->hide();
	gg = new Fl_Group(300,30,630,430,mgl_gettext("Memory"));	gg->hide();
	add_mem(w);		gg->end();
	w->rtab->end();


	w->status = new Fl_Output(0,485,930,25);	w->status->value(mgl_gettext("Ready"));
	w->draw = new Fl_MGL(w->graph);	w->draw->e = w;
	mgl_makemenu_fltk(w->menu, w->graph);
	w->menu->add("Graphics/Primitive", FL_CTRL+'m', prim_dlg_cb, w);

	t->end();	w->end();	w->resizable(t);
	w->rtab->callback(mem_upd_cb, w);
	w->callback(close_cb, w);	w->icon(&image_udav);
	num_windows++;	return w;
}
//-----------------------------------------------------------------------------
void argument_set(int n, const char *s);
int main(int argc, char **argv)
{
//	Fl::lock();
	mgl_ask_func = mgl_ask_fltk;

	textbuf = new Fl_Text_Buffer;
	style_init();
	ScriptWindow *w = new_view();
	Fl::visual(FL_DOUBLE|FL_RGB);
	load_pref(w);
	int ir = w->menu->find_index("File/Recent files");
	w->menu->replace(ir+1, lastfiles[0].c_str());
	w->menu->replace(ir+2, lastfiles[1].c_str());
	w->menu->replace(ir+3, lastfiles[2].c_str());
	w->menu->replace(ir+4, lastfiles[3].c_str());
	w->menu->replace(ir+5, lastfiles[4].c_str());
	int sh;	pref.get("show_hint",sh,1);
	if(sh)	hint_dlg_cb(0,0);

	char *buf = 0;
	while(1)
	{
		char ch = getopt(argc, argv, "1:2:3:4:5:6:7:8:9:ho:L:");
		if(ch>='1' && ch<='9')	argument_set(ch-'0', optarg);
		else if(ch=='L')	setlocale(LC_CTYPE, optarg);
		else if(ch=='h')
		{
			printf("mglconv convert mgl script to bitmap png file.\nCurrent version is 2.%g\n",MGL_VER2);
			printf("Usage:\tmgllab [parameter(s)] scriptfile\n");
			printf(	"\t-1 str       set str as argument $1 for script\n"
					"\t...          ...\n"
					"\t-9 str       set str as argument $9 for script\n"
					"\t-L loc       set locale to loc\n"
//					"\t-            get script from standard input\n"
					"\t-h           print this message\n" );
			return 0;
		}
		// NOTE: I will not parse stdin here
		else if(ch==-1 && optind<argc)	buf = argv[optind];
		else if(ch==-1 && optind>=argc)	break;
	}

	w->show(1, argv);
	if(buf && *buf && *buf!='-')
	{
		load_file(buf, -1,w);
		if(auto_exec)	w->graph->update();
	}
	return Fl::run();
}
//-----------------------------------------------------------------------------
void cb_filech(Fl_Widget*, void *v);
class PropDlg : public GeneralDlg
{
	friend void cb_filech(Fl_Widget*, void *v);
	Fl_Choice *fkind;
	Fl_Spinner *fsize;
	Fl_File_Input *help_path;
	Fl_File_Input *font_path;
	Fl_Check_Button *auto_exec_w;
	Fl_Check_Button *exec_save_w;
	Fl_Check_Button *complete_w;
	Fl_Check_Button *highlight_w;
	Fl_Check_Button *mouse_zoom_w;
	Fl_Choice *lang_w;
	Fl_Choice *scheme_w;
public:
	HMGL gr;
	PropDlg()
	{
		Fl_Button *o;
		w = new Fl_Double_Window(340, 365, mgl_gettext("Properties"));
		w->align(Fl_Align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE));
		fkind = new Fl_Choice(75, 10, 90, 25, mgl_gettext("Font kind"));
		fkind->add("Helvetica");	fkind->add("Courier");	fkind->add("Times");
		fsize = new Fl_Spinner(245, 10, 90, 25, mgl_gettext("Font size"));
		help_path = new Fl_File_Input(5, 55, 305, 35, mgl_gettext("Path for help files"));
		help_path->align(FL_ALIGN_TOP_LEFT);
		o = new Fl_Button(310, 65, 25, 25, mgl_gettext("..."));	o->callback(cb_filech, 0);
		font_path = new Fl_File_Input(5, 110, 305, 35, mgl_gettext("Path for MathGL font (without extension)"));
		font_path->align(FL_ALIGN_TOP_LEFT);
		o = new Fl_Button(310, 120, 25, 25, mgl_gettext("..."));	o->callback(cb_filech, (void *)1);
		auto_exec_w = new Fl_Check_Button(5, 145, 330, 25, mgl_gettext("Execute script after loading"));
		exec_save_w = new Fl_Check_Button(5, 170, 330, 25, mgl_gettext("Save file before redrawing"));
		complete_w = new Fl_Check_Button(5, 195, 330, 25, mgl_gettext("Enable keywords completion"));
		complete_w->deactivate();	// TODO	add completion
		highlight_w = new Fl_Check_Button(5, 220, 330, 25, mgl_gettext("Highlight current object(s)"));
		mouse_zoom_w = new Fl_Check_Button(5, 245, 330, 25, mgl_gettext("Enable mouse wheel for zooming"));
		lang_w = new Fl_Choice(160, 275, 175, 25, mgl_gettext("Language for mgllab"));
		lang_w->add("C.UTF8");	lang_w->add("ru_RU.utf8");	lang_w->add("ru_RU.cp1251");
		scheme_w = new Fl_Choice(160, 305, 175, 25, mgl_gettext("Widget scheme"));
		scheme_w->add("base");	scheme_w->add("gtk+");	scheme_w->add("plastic");	scheme_w->add("gleam");
		o = new Fl_Button(85, 340, 75, 25, mgl_gettext("Cancel"));	o->callback(cb_dlg_cancel,this);
		o = new Fl_Return_Button(180, 340, 75, 25, mgl_gettext("OK"));	o->callback(cb_dlg_ok,this);
		w->set_modal();	w->end();
	}
	void init()
	{
		fkind->value(styletable[0].font/4);
		fsize->value(styletable[0].size);
		font_path->value(fontname.c_str());
		help_path->value(docdir.c_str());
		auto_exec_w->value(auto_exec);
		exec_save_w->value(exec_save);
		//		complete_w->value(complete_word);
		highlight_w->value(highlight);
		mouse_zoom_w->value(mouse_zoom);
		lang_w->value(lang);
		scheme_w->value(scheme);
	}
	void cb_ok()
	{
		set_style(fkind->value(),fsize->value());
		auto_exec = auto_exec_w->value();
		exec_save = exec_save_w->value();
		highlight = highlight_w->value();
		mouse_zoom = mouse_zoom_w->value();
		docdir = help_path->value();
		fontname = font_path->value();
		if(e->graph->get_graph())
			mgl_load_font(e->graph->get_graph(),fontname.c_str(),NULL);
		set_scheme_lang(scheme_w->value(),lang_w->value());	// NOTE: must be after setting docdir
		example_cb(NULL, e);	e->graph->parent()->show();
		save_pref();	hide();
	}
} prop_dlg;
//-----------------------------------------------------------------------------
void cb_filech(Fl_Widget*, void *v)
{
	if(v)
	{
		char *s = fl_file_chooser(mgl_gettext("Font file name"), "MGL font files (*.vfm*)", prop_dlg.font_path->value(), 0);
		if(s)
		{	char *e = strstr(s,".vfm");	if(e)	*e=0;
			prop_dlg.font_path->value(s);	}
	}
	else
	{
		char *s = fl_dir_chooser(mgl_gettext("Folder for help files"), prop_dlg.help_path->value(), 0);
		if(s)	prop_dlg.help_path->value(s);
	}
}
void prop_dlg_cb(Fl_Widget *, void *v)
{	prop_dlg.e = (ScriptWindow *)v;	prop_dlg.show();	}
//-----------------------------------------------------------------------------
void cb_calc_key(Fl_Widget *, void *v);
void cb_calc_ins(Fl_Widget *, void *);
void cb_calc_prev(Fl_Widget *, void *);
void cb_calc_edit(Fl_Widget *, void *);
void cb_calc_kind(Fl_Widget *, void *);
void cb_calc_func(Fl_Widget *, void *);
class CalcDlg : public GeneralDlg
{
public:
	Fl_Input *edit;
	Fl_Output *output;
	Fl_Browser *prev;
	Fl_Choice *kind;
	Fl_Choice *func;
	CalcDlg()
	{
		Fl_Button *o;	Fl_Group* g, *gg;
		w = new Fl_Double_Window(275, 275, mgl_gettext("Calculator"));
		g = new Fl_Group(5, 5, 265, 25);
		edit = new Fl_Input(5, 5, 240, 25);	//edit->callback(cb_calc_edit);
		o = new Fl_Return_Button(245, 5, 25, 25, "@>");
		o->callback(cb_calc_edit);	g->end();	g->resizable(edit);
		g = new Fl_Group(5, 35, 265, 25);
		output = new Fl_Output(55, 35, 120, 25, mgl_gettext("Result"));
		o = new Fl_Button(180, 35, 90, 25, mgl_gettext("@-> to script"));
		o->callback(cb_calc_ins);	g->end();	g->resizable(output);
		prev = new Fl_Select_Browser(5, 80, 265, 70, mgl_gettext("Previous expressions"));
		prev->align(FL_ALIGN_TOP_LEFT);	prev->callback(cb_calc_prev);
		static int widths[] = { 200, 65, 0 };  // widths for each column
		prev->column_widths(widths);	prev->column_char('\t');
		gg = new Fl_Group(5, 155, 265, 115);
			o = new Fl_Button(5, 155, 25, 25, mgl_gettext("7"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(35, 155, 25, 25, mgl_gettext("8"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(65, 155, 25, 25, mgl_gettext("9"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(95, 155, 25, 25, mgl_gettext("+"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(125, 155, 25, 25, mgl_gettext("pi"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(5, 185, 25, 25, mgl_gettext("4"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(35, 185, 25, 25, mgl_gettext("5"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(65, 185, 25, 25, mgl_gettext("6"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(95, 185, 25, 25, mgl_gettext("-"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(125, 185, 25, 25, mgl_gettext("^"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(5, 215, 25, 25, mgl_gettext("1"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(35, 215, 25, 25, mgl_gettext("2"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(65, 215, 25, 25, mgl_gettext("3"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(95, 215, 25, 25, mgl_gettext("*"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(125, 215, 25, 25, mgl_gettext("("));	o->callback(cb_calc_key,o);
			o = new Fl_Button(5, 245, 25, 25, mgl_gettext("0"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(35, 245, 25, 25, mgl_gettext("."));	o->callback(cb_calc_key,o);
			o = new Fl_Button(65, 245, 25, 25, mgl_gettext("E"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(95, 245, 25, 25, mgl_gettext("/"));	o->callback(cb_calc_key,o);
			o = new Fl_Button(125, 245, 25, 25, mgl_gettext(")"));	o->callback(cb_calc_key,o);

			g = new Fl_Group(155, 175, 115, 95, mgl_gettext("Function"));
			kind = new Fl_Choice(160, 179, 105, 25);	kind->callback(cb_calc_kind);
			kind->add("Basic");	kind->add("Exp and log");	kind->add("Trigonometric");
			kind->add("Hyperbolic");	kind->add("Bessel");	kind->add("Elliptic");
			kind->add("Jacobi");	 kind->add("Airy and Gamma");
			kind->add("Exp-integrals"); kind->add("Special");	kind->value(0);

			func = new Fl_Choice(160, 209, 105, 25);
			o = new Fl_Button(160, 239, 105, 25, mgl_gettext("Put function"));	o->callback(cb_calc_func);
			g->end();	g->box(FL_DOWN_BOX);
		gg->end();	gg->resizable(g);

		w->end();	w->resizable(prev);
	}
	void eval()
	{
		const char *eq = edit->value();
		mglData d = Parse->Calc(eq);
		char res[64];	snprintf(res,63,"%g",d.a[0]);
		output->value(res);	result = res;
		char *buf = new char[strlen(res)+strlen(eq)+3];
		sprintf(buf,"%s\t%s",eq,res);
		prev->insert(0,buf);	delete []buf;
	}
	void set_kind()
	{
		int val = kind->value();	func->clear();
		switch(val)
		{
		case 0:	// basic
			func->add("abs()");		func->add("sign()");	func->add("step()");	func->add("sqrt()");
			func->add("mod(,)");	func->add("arg(,)");	break;
		case 1:	// exp and logarithms
			func->add("exp()");		func->add("pow(,)");	func->add("ln()");		func->add("lg()");
			func->add("log(,)");	break;
		case 2:	// trigonometric
			func->add("sin()");		func->add("cos()");		func->add("tan()");		func->add("sinc()");
			func->add("asin()");	func->add("acos()");	func->add("atan()");	break;
		case 3:	// hyperbolic
			func->add("sinh()");	func->add("cosh()");	func->add("tanh()");	func->add("asinh()");
			func->add("acosh()");	func->add("atanh()");	break;
		case 4:	// bessel
			func->add("bessel_j(,)");	func->add("bessel_y(,)");	func->add("bessel_i(,)");	func->add("bessel_k(,)");	break;
		case 5:	// elliptic
			func->add("elliptic_e(,)");	func->add("elliptic_f(,)");	func->add("elliptic_ec()");	func->add("elliptic_kc()");	break;
		case 6:	// jacobi
			func->add("sn(,)");		func->add("cn(,)");		func->add("dn(,)");		func->add("sc(,)");
			func->add("dc(,)");		func->add("nc(,)");		func->add("cs(,)");		func->add("ds(,)");
			func->add("ns(,)");		func->add("sd(,)");		func->add("cd(,)");		func->add("nd(,)");	break;
		case 7:	// airy and gamma
			func->add("airy_ai()");	func->add("airy_bi()");	func->add("airy_dai()");func->add("airy_dbi()");
			func->add("gamma()");	func->add("psi()");		func->add("beta(,)");	break;
		case 8:	// exp integrals
			func->add("ci()");		func->add("si()");		func->add("ei()");		func->add("e1()");
			func->add("e2()");		func->add("ei3()");	break;
		case 9:	// special
			func->add("erf()");		func->add("z()");		func->add("legendre(,)");	func->add("dilog()");
			func->add("eta()");		func->add("zeta()");	func->add("w0()");		func->add("w1()");	break;
		}
//		func->value(0);
	}
} calc_dlg;
//-----------------------------------------------------------------------------
void cb_calc_key(Fl_Widget *, void *v)
{	Fl_Button *o=(Fl_Button *)v;	calc_dlg.edit->insert(o->label());	}
void cb_calc_ins(Fl_Widget *, void *)
{	if(calc_dlg.e)	calc_dlg.e->editor->insert(calc_dlg.output->value());	}
void cb_calc_prev(Fl_Widget *, void *)
{
	const char *s = calc_dlg.prev->text(calc_dlg.prev->value());
	if(s && *s)
	{
		std::string ss(s);	size_t l=ss.length();
		for(size_t i=0;i<l;i++)	if(ss[i]=='\t')	ss[i]=0;
		calc_dlg.edit->value(ss.c_str());
	}
}
void cb_calc_edit(Fl_Widget *, void *)	{	calc_dlg.eval();	}
void cb_calc_kind(Fl_Widget *, void *)	{	calc_dlg.set_kind();	}
void cb_calc_func(Fl_Widget *, void *)
{	const char *s = calc_dlg.func->text();
	if(s && *s)	calc_dlg.edit->insert(s);	}
//-----------------------------------------------------------------------------
void calc_dlg_cb(Fl_Widget *, void *v)
{	calc_dlg.e = (ScriptWindow *)v;	calc_dlg.show();	}
//-----------------------------------------------------------------------------
