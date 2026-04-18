#pragma once
// By Edith Pugh on 2026-04-10

#include "token.hpp"

#include<variant>
#include<vector>
#include<string>

namespace basic::lexer {

struct LexResult {
    struct Ok { std::vector<Token> tokens; };
    struct Err { std::string msg; };
    std::variant<Ok, Err> result;
}; // end struct ParseResult

LexResult parse_line(const std::string& line);

} // end namespace basic
