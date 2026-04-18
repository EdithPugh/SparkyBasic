// By Edith Pugh on 2026-04-10, Sparky's third birthday!!!

#include "command.hpp"

#include <cassert>

namespace basic {

bool Command::is_direct_command(void) const {
    // aborts if statement is somehow in an invalid state
    assert(!tokens.empty());
    return tokens[0].type == lexer::Token::NumLiteral;
} // end Command::is_direct_command

std::optional<unsigned int> Command::get_line_number(void) const {
    if (tokens.empty() || tokens[0].type != lexer::Token::NumLiteral) {
        return std::nullopt;
    }

    double line_num = std::get<double>(tokens[0].value);

    // negative line numbers should be detected by the parser
    assert(line_num >= 0.0);
    return static_cast<unsigned int>(line_num);
} // end Command::get_line_number

}