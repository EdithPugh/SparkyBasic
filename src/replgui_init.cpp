// By Edith Pugh on 2026-04-10

/**
 * File containing functions used to initialize the Interpreter.
 */

#include "replgui.hpp"

#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/wx.h>

const char * const k_app_name = "SparkyBasic PREALPHA";
const unsigned int k_default_win_size_x = 600;
const unsigned int k_default_win_size_y = 400;

enum MenuIDs {
    ID_Save = 1,
    ID_SaveAs,
    ID_SaveCopy,
    ID_Load,
    ID_Append,
    ID_Help,
    ID_Exit,
    ID_New,
};

auto setup_file_menu() -> wxMenu*;
auto setup_help_menu() -> wxMenu*;

ReplGui::ReplGui()
    : wxFrame(nullptr, wxID_ANY, k_app_name)
    , menu_bar (new wxMenuBar)
    , menu_file(setup_file_menu())
    , menu_help(setup_help_menu())
    , sizer(new wxBoxSizer(wxVERTICAL))
    , output_box(new wxTextCtrl(
        this,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_MULTILINE | wxTE_READONLY | wxTE_CHARWRAP
    ))
    , output_sizer(new wxBoxSizer(wxHORIZONTAL))
    , entry_box(new wxTextCtrl(
        this, 
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_PROCESS_ENTER
    ))
    , entry_sizer(new wxBoxSizer(wxHORIZONTAL))
{
    menu_bar->Append(menu_file, "&File");
    menu_bar->Append(menu_help, "&Help");
    SetMenuBar(menu_bar);

    // Bind menu actions to functions
    auto TODO_REPLACE_ME = [](wxCommandEvent&){};
    Bind(wxEVT_MENU, TODO_REPLACE_ME, ID_Save);
    Bind(wxEVT_MENU, TODO_REPLACE_ME, ID_SaveAs);
    Bind(wxEVT_MENU, TODO_REPLACE_ME, ID_SaveCopy);
    Bind(wxEVT_MENU, TODO_REPLACE_ME, ID_Load);
    Bind(wxEVT_MENU, TODO_REPLACE_ME, ID_Help);

    output_sizer->Add(output_box, 1, wxEXPAND);

    entry_box->Bind(wxEVT_TEXT_ENTER, &ReplGui::on_enter, this);

    entry_sizer->Add(entry_box, 1, wxEXPAND);

    // add both the entry box and output box into the main vertical sizer
    sizer->Add(output_sizer, 1, wxEXPAND);
    sizer->Add(entry_sizer, 0, wxEXPAND);
    SetSizerAndFit(sizer);

    // Set program to a default size
    SetSize(k_default_win_size_x, k_default_win_size_y);
} // end MyFrame::MyFrame

auto setup_file_menu() -> wxMenu* {
    auto* menu_file = new wxMenu(); // NOLINT(cppcoreguidelines-owning-memory)
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
    menu_file->Append(
        ID_Append,
        "&Append\tShift-Ctrl-O",
        "Load file into memory without clearing current program."
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
    return menu_file;
}

auto setup_help_menu() -> wxMenu* {
    auto* menu_help = new wxMenu(); // NOLINT(cppcoreguidelines-owning-memory)

    menu_help->Append(
        ID_Help,
        "&Help\tCtrl-H",
        "Open help dialogue."
    );
    return menu_help;
}