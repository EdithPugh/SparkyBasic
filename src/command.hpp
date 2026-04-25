#pragma once
// By Edith Pugh on 2026-04-25

#include "lexer/token.hpp"

#include <vector>

/**
 * A simple wrapper for std::vector<Token> for use in CommandList and
 * Interpreter.
 */
struct Command {
    std::vector<lexer::Token> tokens;

    std::optional<size_t> get_line_num(void) const {
        return tokens[0].get_line_num();
    }
};