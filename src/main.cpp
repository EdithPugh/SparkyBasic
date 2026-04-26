// By Edith Pugh on 2026-April-10, Sparky's third birthday.

#include "replgui.hpp"

#include <wx/wx.h>

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
class SparkyBasicApp : public wxApp {
public:
    auto OnInit() -> bool override;

    ReplGui* gui;
};

auto SparkyBasicApp::OnInit() -> bool {
    // wxWidgets sucks so we can't use unique_ptr.
    // gui is automatically freed by wxWidgets.
    gui = new ReplGui(); // NOLINT(cppcoreguidelines-owning-memory)
    gui->Show();
    return true;
} // end InterpreterApp::OnInit

wxIMPLEMENT_APP(SparkyBasicApp);