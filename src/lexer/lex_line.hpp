#pragma once
// By Edith Pugh on 2026-04-10

#include "token.hpp"

#include<variant>
#include<vector>
#include<string>

namespace lexer {

/**
 * A simple struct representing the result of a call to lex_line.
 */
struct LexResult {
    struct Ok { std::vector<Token> tokens; };
    struct Err { std::string msg; };
    std::variant<Ok, Err> result;
}; // end struct ParseResult

/**
 * A function that takes in an input string and returns either a vector of
 * tokens or, on an error, an error message.
 * @param line: The input string that is to be tokenized.
 * @return: Returns a LexResult, a simple wrapped around std::variant.
 */
LexResult lex_line(const std::string& line);

} // end namespace basic
