#pragma once
// By Edith Pugh on 2026-04-14

#include <variant>

#include "token.hpp"
#include "lex_line.hpp"

namespace basic::lexer {

std::variant<Token, LexResult::Err> lex_string(
    const std::string& line, size_t& index);
std::variant<Token, LexResult::Err> lex_num(
    const std::string& line, size_t& index);

}