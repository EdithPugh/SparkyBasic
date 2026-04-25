// By Edith Pugh on 2026-04-15

#include "lex_literals.hpp"

#include "error_messages.hpp"
#include "lex_line.hpp"

#include <cassert>
#include <stdexcept>
#include <string>

namespace lexer {

const size_t k_num_literal_prealloc = 20;
const size_t k_str_literal_prealloc = 20;

std::variant<Token, LexResult::Err> lex_string(
    std::string_view line, size_t& index) {
    assert(line[index] == '"');
    index++;
    std::string str_literal;
    str_literal.reserve(k_str_literal_prealloc);
    while (index < line.size() && line[index] != '"') {
        if (line[index] == '\\') {
            index++;
            if (index >= line.size()) {
                return LexResult::Err{
                    std::string(k_msg_unexpected_eol_reading_string)
                };
            }
            switch (std::tolower(line[index])) {
            case 't':
                str_literal.push_back('\t');
                break;
            case 'n':
                str_literal.push_back('\n');
                break;
            case '\\':
                str_literal.push_back('\\');
                break;
            case '"':
                str_literal.push_back('"');
                break;
            default:
                std::string err_msg;
                err_msg.append(k_msg_unknown_backspace_sequence);
                err_msg.push_back(line[index]);
                return LexResult::Err {
                    err_msg
                };
            }
        } // end if (line[index] == '\\')
        else {
            str_literal.push_back(line[index]);
        }
        index++;
    } // end while (index < line.size() && line[index] != '"')
    if (index >= line.size()) {
        return LexResult::Err{
            std::string(k_msg_unexpected_eol_reading_string)
        };
    }
    // skips last quotation mark
    index++;
    return Token::from_literal(std::move(str_literal));
}

bool is_num_component(char com) {
    return std::isdigit(com) || com == '.' || std::toupper(com) == 'E';
}

// match numbers, initial + or - is not included as those are handled by
// the parser
std::variant<Token, LexResult::Err> lex_num(
    std::string_view line, size_t& index) {
    assert(std::isdigit(line[index]) || line[index] == '.');
    std::string num_literal;
    num_literal.reserve(k_num_literal_prealloc);

    while (index < line.size() && is_num_component(line[index])) {
        num_literal.push_back(line[index]);
        index++;
    }
    try {
        return Token::from_literal(std::stod(num_literal));
    }
    catch (std::invalid_argument&) {
        std::string err_msg;
        err_msg.append(k_msg_malformed_num_literal);
        err_msg.append(num_literal);
        return LexResult::Err{err_msg};
    }
    catch (std::out_of_range&) {
        std::string err_msg;
        err_msg.append(k_msg_num_literal_out_of_range);
        err_msg.append(num_literal);
        return LexResult::Err{err_msg};
    }
}

}