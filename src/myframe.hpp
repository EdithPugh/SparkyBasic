#pragma once
// By Edith Pugh on 2026-04-10

#include <wx/event.h>
#include <wx/wx.h>

class MyFrame : public wxFrame {
    wxMenuBar* menu_bar;
    wxMenu* menu_file;
    wxMenu* menu_help;
    
    wxPanel* panel;

    wxBoxSizer* sizer;

    wxTextCtrl* output_box;
    wxBoxSizer* output_sizer;
    wxTextCtrl* entry_box;
    wxBoxSizer* entry_sizer;

    // helper functions to setup the menus
    void setup_file_menu(void);
    void setup_help_menu(void);
public:
    MyFrame(void);
}; // end class MyFrame