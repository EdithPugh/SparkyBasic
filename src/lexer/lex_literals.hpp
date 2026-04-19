#pragma once
// By Edith Pugh on 2026-04-14

#include <variant>

#include "token.hpp"
#include "lex_line.hpp"

namespace lexer {

/**
 * A helper function for use by lex_token that eats a string.
 * @param line: The line that is currently being parsed
 * @param index: The index of line that contains the opening quote.
 * @return Returns a variant containing either a single Token or a
 * LexResult::Err to be passed back to the original caller.
 * @exception: assert failure if line[index] is not a quote
 */
std::variant<Token, LexResult::Err> lex_string(
    std::string_view line, size_t& index);

/**
 * A helper function for use by lex_token that eats a number.
 * @param line: The line that is currently being parsed
 * @param index: The index of line that contains the dot or digit that starts
 * the number.
 * @return Returns a variant containing either a single Token or a
 * LexResult::Err to be passed back to the original caller.
 * @exception: assert failure if line[index] is not either a number or period.
 */
std::variant<Token, LexResult::Err> lex_num(
    std::string_view line, size_t& index);

}