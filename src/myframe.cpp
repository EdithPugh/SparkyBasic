// By Edith Pugh on 2026-04-10

#include "myframe.hpp"

#include "defs.hpp"
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/gtk/textctrl.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/wx.h>

enum MenuIDs {
    ID_Save = 1,
    ID_SaveAs,
    ID_SaveCopy,
    ID_Load,
    ID_Help,
    ID_Exit,
    ID_New,
};

MyFrame::MyFrame(void)
    :wxFrame(nullptr, wxID_ANY, k_app_name)
{
    menu_file = new wxMenu();
    menu_help = new wxMenu();

    menu_file->Append(
        ID_New,
        "&New\tCtrl-N",
        "Clear current program to work on new program."
    );
    menu_file->Append(
        ID_Load,
        "&Load\tCtrl-O",
        "Clear current program and load in program file."
    );
    menu_file->AppendSeparator();
    menu_file->Append(
        ID_Save,
        "&Save\tCtrl-S",
        "Save commands in current file."
    );
    menu_file->Append(
        ID_SaveAs,
        "&Save as...\tShift-Ctrl-S",
        "Save commands in new file and make it the current file."
    );
    menu_file->Append(
        ID_SaveCopy,
        "&Save Copy...\tAlt-Ctrl-S",
        "Save commands in new file without making it the current file."
    );
    menu_file->AppendSeparator();
    menu_file->Append(
        ID_Exit,
        "&Exit SparkyBasic\tCtrl-Q",
        "Exit SparkyBasic without saving."
    );

    menu_help->Append(
        ID_Help,
        "&Help\tCtrl-h",
        "Open help dialogue."
    );

    wxMenuBar* menu_bar = new wxMenuBar;
    menu_bar->Append(menu_file, "&File");
    menu_bar->Append(menu_help, "&Help");

    SetMenuBar(menu_bar);

    Bind(wxEVT_MENU, &MyFrame::on_save, this, ID_Save);
    Bind(wxEVT_MENU, &MyFrame::on_save_as, this, ID_SaveAs);
    Bind(wxEVT_MENU, &MyFrame::on_save_copy, this, ID_SaveCopy);
    Bind(wxEVT_MENU, &MyFrame::on_load, this, ID_Load);
    Bind(wxEVT_MENU, &MyFrame::on_help, this, ID_Help);

    output_box = new wxTextCtrl(
        this,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_MULTILINE | wxTE_READONLY | wxTE_CHARWRAP
    );
    output_sizer = new wxBoxSizer(wxHORIZONTAL);
    output_sizer->Add(output_box, 1, wxEXPAND);

    entry_box = new wxTextCtrl(this, wxID_ANY);
    entry_sizer = new wxBoxSizer(wxHORIZONTAL);
    entry_sizer->Add(entry_box, 1, wxEXPAND);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(output_sizer, 1, wxEXPAND);
    sizer->Add(entry_sizer, 0, wxEXPAND);
    SetSizerAndFit(sizer);

    SetSize(k_default_win_size_x, k_default_win_size_y);
} // end MyFrame::MyFrame

void MyFrame::on_save(wxCommandEvent& evt) {
    (void)evt;
    return;
}
void MyFrame::on_save_as(wxCommandEvent& evt) {
    (void)evt;
    return;
}
void MyFrame::on_save_copy(wxCommandEvent& evt) {
    (void)evt;
    return;
}
void MyFrame::on_load(wxCommandEvent& evt) {
    (void)evt ;
    return;
}
void MyFrame::on_help(wxCommandEvent& evt) {
    (void)evt;
    return;
}