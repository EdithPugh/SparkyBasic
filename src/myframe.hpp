#pragma once
// By Edith Pugh on 2026-04-10

#include <wx/event.h>
#include <wx/wx.h>

class MyFrame : public wxFrame {
    wxMenuBar* menu_bar;
    wxMenu* menu_file;
    wxMenu* menu_help;
    
    //wxPanel* panel;

    //wxTextCtrl* output_box;
    //wxTextCtrl* entry_box;

    void on_save(wxCommandEvent& evt);
    void on_save_as(wxCommandEvent& evt);
    void on_save_copy(wxCommandEvent& evt);
    void on_load(wxCommandEvent& evt);
    void on_help(wxCommandEvent& evt);
    void on_close(wxCloseEvent& evt);
public:
    MyFrame(void);
}; // end class MyFrame