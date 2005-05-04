//
// "$Id$"
//
// Widget panel for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

// generated by Fast Light User Interface Designer (fluid) version 1.0200

#ifndef widget_panel_h
#define widget_panel_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
extern void propagate_load(Fl_Group*, void*);
#include <FL/Fl_Input.H>
extern void label_cb(Fl_Input*, void*);
#include <FL/Fl_Choice.H>
extern Fl_Menu_Item labeltypemenu[];
extern void labeltype_cb(Fl_Choice*, void*);
extern void image_cb(Fl_Input*, void*);
#include <FL/Fl_Button.H>
extern void image_browse_cb(Fl_Button*, void*);
extern void inactive_cb(Fl_Input*, void*);
extern void inactive_browse_cb(Fl_Button*, void*);
extern void align_cb(Fl_Button*, void*);
#include <FL/Fl_Box.H>
#include <FL/Fl_Value_Input.H>
extern void x_cb(Fl_Value_Input*, void*);
extern Fl_Value_Input *widget_x_input;
extern void y_cb(Fl_Value_Input*, void*);
extern Fl_Value_Input *widget_y_input;
extern void w_cb(Fl_Value_Input*, void*);
extern Fl_Value_Input *widget_w_input;
extern void h_cb(Fl_Value_Input*, void*);
extern Fl_Value_Input *widget_h_input;
extern void slider_size_cb(Fl_Value_Input*, void*);
extern void min_cb(Fl_Value_Input*, void*);
extern void max_cb(Fl_Value_Input*, void*);
extern void step_cb(Fl_Value_Input*, void*);
extern void value_cb(Fl_Value_Input*, void*);
#include "Shortcut_Button.h"
extern void shortcut_in_cb(Shortcut_Button*, void*);
extern void xclass_cb(Fl_Input*, void*);
#include <FL/Fl_Light_Button.H>
extern void border_cb(Fl_Light_Button*, void*);
extern void modal_cb(Fl_Light_Button*, void*);
extern void non_modal_cb(Fl_Light_Button*, void*);
extern void visible_cb(Fl_Light_Button*, void*);
extern void active_cb(Fl_Light_Button*, void*);
extern void resizable_cb(Fl_Light_Button*, void*);
extern void hotspot_cb(Fl_Light_Button*, void*);
extern void tooltip_cb(Fl_Input*, void*);
extern Fl_Menu_Item fontmenu[];
extern void labelfont_cb(Fl_Choice*, void*);
extern void labelsize_cb(Fl_Value_Input*, void*);
#include <FL/Fl_Check_Button.H>
extern Fl_Check_Button *default_labelcolor;
extern void labelcolor_cb(Fl_Button*, void*);
extern Fl_Button *custom_labelcolor;
extern Fl_Menu_Item boxmenu[];
extern void box_cb(Fl_Choice*, void*);
extern Fl_Check_Button *default_color;
extern void color_cb(Fl_Button*, void*);
extern Fl_Button *custom_color;
extern void down_box_cb(Fl_Choice*, void*);
extern Fl_Check_Button *default_selection_color;
extern void color2_cb(Fl_Button*, void*);
extern Fl_Button *custom_selection_color;
extern void textfont_cb(Fl_Choice*, void*);
extern void textsize_cb(Fl_Value_Input*, void*);
extern Fl_Check_Button *default_text_color;
extern void textcolor_cb(Fl_Button*, void*);
extern Fl_Button *custom_text_color;
extern void subclass_cb(Fl_Input*, void*);
extern void subtype_cb(Fl_Choice*, void*);
extern void name_cb(Fl_Input*, void*);
extern void name_public_cb(Fl_Light_Button*, void*);
extern void v_input_cb(Fl_Input*, void*);
extern Fl_Input *v_input[4];
#include "CodeEditor.h"
extern void callback_cb(CodeEditor*, void*);
extern void user_data_cb(Fl_Input*, void*);
extern Fl_Menu_Item whenmenu[];
extern void when_cb(Fl_Choice*, void*);
extern void user_data_type_cb(Fl_Input*, void*);
extern void when_button_cb(Fl_Light_Button*, void*);
extern void overlay_cb(Fl_Button*, void*);
extern void revert_cb(Fl_Button*, void*);
#include <FL/Fl_Return_Button.H>
extern void ok_cb(Fl_Return_Button*, void*);
extern void cancel_cb(Fl_Button*, void*);
Fl_Double_Window* make_widget_panel();
#endif

//
// End of "$Id$".
//
