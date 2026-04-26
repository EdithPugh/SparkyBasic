// By Edith Pugh on 2026-April-10, Sparky's third birthday.

#include "replgui.hpp"

#include <wx/wx.h>

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
class InterpreterApp : public wxApp {
public:
    auto OnInit() -> bool override;

    ReplGui* gui;
};

auto InterpreterApp::OnInit() -> bool {
    // wxWidgets sucks so we can't use unique_ptr.
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    gui = new ReplGui();
    gui->Show();
    return true;
} // end InterpreterApp::OnInit

wxIMPLEMENT_APP(InterpreterApp);