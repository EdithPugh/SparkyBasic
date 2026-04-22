// By Edith Pugh on 2026-04-11

// Implements some of the static functions from token.hpp for help with
// constructing

#include "token.hpp"

#include <variant>

namespace lexer {

Token Token::from_literal(double num) {
    return Token(Token::NumLiteral, num);
}
Token Token::from_literal(std::string&& str) {
    return Token(Token::StrLiteral, str);
}
Token Token::from_line_num(size_t num) {
    return Token(Token::LineNum, num);
}
Token Token::from_var_or_keyword(std::string&& id) {
    // whole loop should be optimized out with NDEBUG?
    for (auto& character: id) {
        assert(std::isupper(character));
    }
    if (id == "NEW") { return from_mono(Token::KwNew).value(); }
    else if (id == "RUN") { return from_mono(Token::KwRun).value(); }
    else if (id == "LIST") { return from_mono(Token::KwList).value(); }
    else if (id == "CLEAR") { return from_mono(Token::KwClear).value(); }
    else if (id == "PRINT") { return from_mono(Token::KwPrint).value(); }
    else if (id == "INPUT") { return from_mono(Token::KwInput).value(); }
    else if (id == "LET") { return from_mono(Token::KwLet).value(); }
    else if (id == "DIM") { return from_mono(Token::KwDim).value(); }
    else if (id == "IF") { return from_mono(Token::KwIf).value(); }
    else if (id == "THEN") { return from_mono(Token::KwThen).value(); }
    else if (id[id.size()-1] == '$') {
        return Token(Token::StrVar, id);
    }
    else {
        return Token(Token::NumVar, id);
    }
}

std::optional<Token> Token::from_mono(Type new_type) {
    switch (new_type) {
    case NumVar:
    case StrVar:
    case NumLiteral:
    case StrLiteral:
    case LineNum:
        return std::nullopt;
    default:
        return Token(new_type, std::monostate());
    }
}

std::optional<std::string_view> Token::get_var_name(void) const {
    if (type == NumVar || type == StrVar) {
        return std::get<std::string>(value);
    }
    return std::nullopt;
}
std::optional<std::string_view> Token::get_string(void) const {
    if (type == StrLiteral) {
        return std::get<std::string>(value);
    }
    return std::nullopt;
}
std::optional<double> Token::get_number(void) const {
    if (type == NumLiteral) {
        return std::get<double>(value);
    }
    return std::nullopt;
}
std::optional<size_t> Token::get_line_num(void) const {
    if (type == LineNum) {
        return std::get<size_t>(value);
    }
    return std::nullopt;
}

}