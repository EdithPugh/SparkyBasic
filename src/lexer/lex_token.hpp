#pragma once
// By Edith Pugh on 2026-04-14

#include <string_view>

#include "lex_line.hpp"

namespace lexer {

/**
 * A helper function for lex_line that lexes a single token and either returns
 * it or a LexResult::Err. Called in a loop to lex an entire line.
 * @param line: The line that is currently being lexed.
 * @param index: The current index from lex_line.
 * @return: returns a variant containing either a token or error
 */
auto lex_token(
    std::string_view line,
    size_t& index)
    -> std::variant<Token, LexResult::Err>;

}