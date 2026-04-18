#pragma once
// By Edith Pugh on 2026-04-14

#include <string>

#include "lex_line.hpp"

namespace basic::lexer {

std::variant<Token, LexResult::Err> lex_token(const std::string& line,
    size_t& index);

}