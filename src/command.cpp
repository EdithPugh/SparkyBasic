// By Edith Pugh on 2026-04-10, Sparky's third birthday!!!

#include "command.hpp"

#include <cassert>

namespace basic {

std::optional<bool> Command::is_direct_command(void) const {
    if (tokens.size() == 0) {
        return std::nullopt;
    }
    return tokens[0].get_type() == lexer::Token::LineNum;
} // end Command::is_direct_command

std::optional<size_t> Command::get_line_number(void) const {
    if (tokens.empty() || tokens[0].get_type() != lexer::Token::LineNum) {
        return std::nullopt;
    }

    return tokens[0].get_line_num().value();
} // end Command::get_line_number

}