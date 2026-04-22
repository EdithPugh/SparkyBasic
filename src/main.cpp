// By Edith Pugh on 2026-April-10, Sparky's third birthday.

#include "replgui.hpp"

#include <wx/wx.h>

class InterpreterApp : public wxApp {
public:
    bool OnInit() override;

    ReplGui* gui;
};

bool InterpreterApp::OnInit() {
    // wxWidgets sucks so we can't use unique_ptr.
    gui = new ReplGui();
    gui->Show();
    return true;
} // end InterpreterApp::OnInit

wxIMPLEMENT_APP(InterpreterApp);