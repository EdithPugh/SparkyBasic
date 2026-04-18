// By Edith Pugh on 2026-April-10, Sparky's third birthday.

#include "myframe.hpp"

#include <wx/wx.h>

// These names like MyApp, MyPanel, etc aren't very descriptive but I can't
// think of any better ways to describe them that aren't kinda verbose like
// SparkyBasicApp (which would also make autocomplete p much useless)
class MyApp : public wxApp {
public:
    bool OnInit() override;

    MyFrame* frame;
};

bool MyApp::OnInit() {
    // wxWidgets sucks so we can't use unique_ptr.
    frame = new MyFrame();
    frame->Show();
    return true;
} // end MyApp::OnInit

wxIMPLEMENT_APP(MyApp);