// By Edith Pugh on 2026-April-10, Sparky's third birthday.

#include "interpreter.hpp"

#include <wx/wx.h>

class InterpreterApp : public wxApp {
public:
    bool OnInit() override;

    Interpreter* interpreter;
};

bool InterpreterApp::OnInit() {
    // wxWidgets sucks so we can't use unique_ptr.
    interpreter = new Interpreter();
    interpreter->Show();
    return true;
} // end InterpreterApp::OnInit

wxIMPLEMENT_APP(InterpreterApp);