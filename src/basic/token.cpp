// By Edith Pugh on 2026-04-11

// Implements some of the static functions from token.hpp for help with
// constructing

#include "token.hpp"

#include <sstream>

using namespace basic;

Token Token::from_literal(double num) {
    return Token(Token::NumLiteral, num);
}
Token Token::from_literal(const std::string& str) {
    return Token(Token::StrLiteral, str);
}
Token Token::from_line_num(size_t num) {
    return Token(Token::LineNum, num);
}
Token Token::from_var_or_keyword(const std::string& id) {
    std::stringstream stream_toupper;
    for (const char& id_char: id) {
        stream_toupper << std::toupper(id_char);
    }
    std::string id_upper = stream_toupper.str();
    if (id_upper == "NEW") { return Token(Token::KwNew); }
    else if (id_upper == "RUN") { return Token(Token::KwRun); }
    else if (id_upper == "LIST") { return Token(Token::KwList); }
    else if (id_upper == "CLEAR") { return Token(Token::KwClear); }
    else if (id_upper == "PRINT") { return Token(Token::KwPrint); }
    else if (id_upper == "INPUT") { return Token(Token::KwInput); }
    else if (id_upper == "LET") { return Token(Token::KwLet); }
    else if (id_upper == "DIM") { return Token(Token::KwDim); }
    else if (id_upper == "IF") { return Token(Token::KwIf); }
    else if (id_upper == "THEN") { return Token(Token::KwThen); }
    else if (id_upper[id_upper.size()-1] == '$') {
        return Token(Token::NumVar, id_upper);
    }
    else {
        return Token(Token::StrVar, id_upper);
    }
}