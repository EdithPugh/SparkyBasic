#pragma once
// By Edith Pugh on 2026-04-10

#include <wx/event.h>
#include <wx/wx.h>

/**
 * A class implementing the main GUI of the program
 */
class ReplGui : public wxFrame {
    wxMenuBar* menu_bar;
    wxMenu* menu_file;
    wxMenu* menu_help;

    wxBoxSizer* sizer;

    wxTextCtrl* output_box;
    wxBoxSizer* output_sizer;
    wxTextCtrl* entry_box;
    wxBoxSizer* entry_sizer;

    /**
     * A function bound to the input box enter key, all code related to
     * executing commands is ultimately run from here.
     */
    void on_enter(wxCommandEvent& evt);
public:
    ReplGui(void);
}; // end class MyFrame