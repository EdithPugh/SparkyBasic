// By Edith Pugh on 2026-04-15

#include "lex_literals.hpp"

#include "error_messages.hpp"
#include "lex_line.hpp"

#include <sstream>
#include <cassert>
#include <stdexcept>

namespace lexer {

std::variant<Token, LexResult::Err> lex_string(
    const std::string& line, size_t& index) {
    assert(line[index] == '"');
    index++;
    std::stringstream str_literal;
    while (index < line.size() && line[index] != '"') {
        if (line[index] == '\\') {
            index++;
            if (index >= line.size()) {
                return LexResult::Err{
                    k_msg_unexpected_eol_reading_string
                };
            }
            switch (std::tolower(line[index])) {
            case 't':
                str_literal << '\t';
                break;
            case 'n':
                str_literal << '\n';
                break;
            case '\\':
                str_literal << '\\';
                break;
            case '"':
                str_literal << '"';
            default:
                std::stringstream err_msg;
                err_msg << k_msg_unknown_backspace_sequence;
                err_msg << line[index];
                return LexResult::Err {
                    err_msg.str()
                };
            }
        } // end if (line[index] == '\\')
        else {
            str_literal << line[index];
        }
        index++;
    } // end while (index < line.size() && line[index] != '"')
    if (index < line.size()) {
        return LexResult::Err{
            k_msg_unexpected_eol_reading_string
        };
    }
    // skips last quotation mark
    index++;
    return Token::from_literal(str_literal.str());
}

bool is_num_component(char com) {
    return std::isdigit(com) || com == '.' || std::toupper(com) == 'E';
}

// match numbers, initial + or - is not included as those are handled by
// the parser
std::variant<Token, LexResult::Err> lex_num(
    const std::string& line, size_t& index) {
    assert(std::isdigit(line[index]) || line[index] == '.');
    std::stringstream num;

    while (index < line.size() && is_num_component(line[index])) {
        num << line[index];
        index++;
    }
    try {
        return Token::from_literal(std::stod(num.str()));
    }
    catch (std::invalid_argument) {
        std::stringstream err_msg;
        err_msg << k_msg_malformed_num_literal;
        err_msg << num.str();
        return LexResult::Err{err_msg.str()};
    }
    catch (std::out_of_range) {
        std::stringstream err_msg;
        err_msg << k_msg_num_literal_out_of_range;
        err_msg << num.str();
        return LexResult::Err{err_msg.str()};
    }
}

}