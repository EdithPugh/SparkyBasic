// By Edith Pugh on 2026-04-14

#include "lex_token.hpp"

#include "token.hpp"
#include "error_messages.hpp"
#include "lex_literals.hpp"

#include <variant>
#include <string_view>

namespace lexer {

// lexes one token from the line
auto lex_token(std::string_view line,
    size_t& index)
    -> std::variant<Token, LexResult::Err> {
    // match identifiers
    if (std::isalpha(line[index]) != 0) {
        std::string identifier;
        while (index < line.size() && std::isalpha(line[index]) != 0) {
            identifier.push_back(
                static_cast<char>(std::toupper(line[index]))
            );
            index++;
        }
        // eat string sign, if there is one
        if (index < line.size() && line[index] == '$') {
            identifier.push_back('$');
            index++;
        }
        return Token::from_var_or_keyword(std::move(identifier));
    }
    // match string
    if (line[index] == '"') {
        return lex_string(line, index);
    }
    // match number
    if (std::isdigit(line[index]) != 0 || line[index] == '.') {
        return lex_num(line, index);
    }
    // match non-alphanumerical tokens
    switch (line[index]) {
    case '(': 
        index++;
        return Token::from_mono(Token::OpenParen);
    case ')':
        index++; 
        return Token::from_mono(Token::CloseParen);
    case '=':
        index++;
        return Token::from_mono(Token::Equal);
    case ',':
        index++;
        return Token::from_mono(Token::Comma);
    case ';':
        index++;
        return Token::from_mono(Token::Semicolon);
    case '+':
        index++;
        return Token::from_mono(Token::Add);
    case '-':
        index++;
        return Token::from_mono(Token::Sub);
    case '*':
        index++;
        return Token::from_mono(Token::Mul);
    case '/':
        index++;
        return Token::from_mono(Token::Div);
    case '>':
        if (index + 1 >= line.size() || line[index + 1] != '=') {
            index++;
            return Token::from_mono(Token::GreaterThan);
        } else {
            index += 2;
            return Token::from_mono(Token::GreaterThanOrEqualTo);
        }
    case '<':
        if (index + 1 >= line.size()
            || (line[index + 1] != '=' && line[index + 1] != '>')) {
            index++;
            return Token::from_mono(Token::LessThan);
        } else if (line[index + 1] == '>') {
            index += 2;
            return Token::from_mono(Token::NotEqualTo);
        } else {
            index += 2;
            return Token::from_mono(Token::LessThanOrEqualTo);
        }
    default:
        // since literal and keyword functions already return, this means that
        // there must be an unknown token. Uh oh!
        std::string err_msg;
        err_msg.append(k_msg_unknown_token);
        err_msg.push_back(line[index]);
        return LexResult::Err{err_msg};
    } // end switch(line[index])
}

}