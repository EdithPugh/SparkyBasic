// By Edith Pugh on 2026-04-21

#include "replgui.hpp"

#include "lexer/lex_line.hpp"

#include <wx/wx.h>

#include <variant>
#include <sstream>

void ReplGui::on_enter(wxCommandEvent& evt) {
    (void)evt;
    std::string line = entry_box->GetValue().ToAscii('?').data();
    
    // later this should be done through the Command class, this is just for
    // testing the lexer
    lexer::LexResult result = lexer::lex_line(line);

    if (std::holds_alternative<lexer::LexResult::Err>(result.result)) {
        *output_box << std::get<lexer::LexResult::Err>(result.result).msg;
    }
    else {
        auto tokens = std::get<lexer::LexResult::Ok>(result.result).tokens;
        for (size_t i=0;i!=tokens.size();i++) {
            std::stringstream token_str;
            token_str << tokens[i];
            *output_box << token_str.str();
            if (i != tokens.size() - 1) {
                *output_box << ", ";
            }
        }
    }

    *output_box << "\n";
    entry_box->Clear();
}