// By Edith Pugh on 2026-04-11

// Implements some of the static functions from token.hpp for help with
// constructing

#include "token.hpp"

#include <variant>

namespace lexer {

auto Token::from_literal(double num) -> Token {
    return { Token::NumLiteral, num };
}
auto Token::from_literal(std::string&& str) -> Token {
    return { Token::StrLiteral, std::move(str) };
}
auto Token::from_line_num(size_t num) -> Token {
    return { Token::LineNum, num };
}
auto Token::from_var_or_keyword(std::string&& identifier) -> Token {
    // whole loop should be optimized out with NDEBUG?
    for (auto& character: identifier) {
        assert(std::isupper(character) || character == '$');
    }
    if (identifier == "NEW")   { return from_mono(Token::KwNew); }
    if (identifier == "RUN")   { return from_mono(Token::KwRun); }
    if (identifier == "LIST")  { return from_mono(Token::KwList); }
    if (identifier == "CLEAR") { return from_mono(Token::KwClear); }
    if (identifier == "PRINT") { return from_mono(Token::KwPrint); }
    if (identifier == "INPUT") { return from_mono(Token::KwInput); }
    if (identifier == "LET")   { return from_mono(Token::KwLet); }
    if (identifier == "DIM")   { return from_mono(Token::KwDim); }
    if (identifier == "IF")    { return from_mono(Token::KwIf); }
    if (identifier == "THEN")  { return from_mono(Token::KwThen); }

    if (identifier[identifier.size()-1] == '$') {
        return { Token::StrVar, std::move(identifier) };
    }
    return { Token::NumVar, std::move(identifier) };
}

auto Token::from_mono(Type new_type) -> Token {
    switch (new_type) {
    case NumVar:
    case StrVar:
    case NumLiteral:
    case StrLiteral:
    case LineNum:
        assert(0);
    default:
        return { new_type, std::monostate() };
    }
}

auto Token::get_var_name() const -> std::optional<std::string_view> {
    if (type == NumVar || type == StrVar) {
        return std::get<std::string>(value);
    }
    return std::nullopt;
}
auto Token::get_string() const -> std::optional<std::string_view> {
    if (type == StrLiteral) {
        return std::get<std::string>(value);
    }
    return std::nullopt;
}
auto Token::get_number() const -> std::optional<double> {
    if (type == NumLiteral) {
        return std::get<double>(value);
    }
    return std::nullopt;
}
auto Token::get_line_num() const -> std::optional<size_t> {
    if (type == LineNum) {
        return std::get<size_t>(value);
    }
    return std::nullopt;
}

}