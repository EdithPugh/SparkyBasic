// By Edith Pugh on 2026-04-14

#include "lex_token.hpp"

#include "token.hpp"
#include "error_messages.hpp"
#include "lex_literals.hpp"

#include <variant>
#include <string>
#include <sstream>

namespace basic::lexer {

// lexes one token from the line
std::variant<Token, LexResult::Err> lex_token(const std::string& line,
    size_t& index) {
    // match identifiers
    if (std::isalpha(line[index])) {
        std::stringstream id;
        id << std::toupper(line[index]);
        while (index < line.size() && std::isalpha(line[index])) {
            id << std::toupper(line[index]);
            index++;
        }
        // eat string sign, if there is one
        if (index < line.size() && line[index] == '$') {
            id << line[index];
            index++;
        }
        return Token::from_var_or_keyword(id.str());
    }
    // match string
    if (line[index] == '"') {
        return lex_string(line, index);
    }
    // match number
    if (std::isdigit(line[index]) || line[index] == '.') {
        return lex_num(line, index);
    }
    // match operator tokens
    switch (line[index]) {
    case '(': 
        index++;
        return Token(Token::OpenParen);
    case ')':
        index++; 
        return Token(Token::CloseParen);
    case '=':
        index++;
        return Token(Token::Equal);
    case '>':
        if (index + 1 >= line.size() || line[index + 1] != '=') {
            index++;
            return Token(Token::GreaterThan);
        } else {
            index += 2;
            return Token(Token::GreaterThanOrEqualTo);
        }
    case '<':
        if (index + 1 >= line.size()
            || (line[index + 1] != '=' && line[index + 1] != '>')) {
            index++;
            return Token(Token::LessThan);
        } else if (line[index + 1] == '>') {
            index += 2;
            return Token(Token::NotEqualTo);
        } else {
            index += 2;
            return Token(Token::LessThanOrEqualTo);
        }
    default:
        // since literal and keyword functions already return, this means that
        // there must be an unknown token. Uh oh!
        std::stringstream err_msg;
        err_msg << k_msg_unknown_token;
        err_msg << line[index];
        return LexResult::Err{err_msg.str()};
    } // end switch(line[index])
}

}