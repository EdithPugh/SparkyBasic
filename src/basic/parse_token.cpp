// By Edith Pugh on 2026-04-14

#include "parse_token.hpp"

#include "token.hpp"
#include "error_messages.hpp"

#include <vector>
#include <string>
#include <optional>
#include <sstream>

using namespace basic;

// parses one token from the line
std::optional<ParseResult::Err> parse_token(const std::string& line,
    size_t& index,
    std::vector<Token>& tokens) {
    // match identifiers
    if (std::isalpha(line[index])) {
        std::stringstream id;
        id << std::toupper(line[index]);
        while (index < line.size() && std::isalpha(line[index])) {
            id << std::toupper(line[index]);
            index++;
        }
        tokens.push_back(Token::from_var_or_keyword(id.str()));
        // return early so that only one token is returned.
        // not strictly necessary.
        return std::nullopt;
    }
    // match string
    if (line[index] == '"') {
        index++;
        std::stringstream str_literal;
        while (index < line.size() && line[index] != '"') {
            if (line[index] == '\\') {
                index++;
                if (index >= line.size()) {
                    return ParseResult::Err{
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
                    return ParseResult::Err {
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
            return ParseResult::Err{
                k_msg_unexpected_eol_reading_string
            };
        }
        // skips last quotation mark
        index++;
        tokens.push_back(Token::from_literal(str_literal.str()));
        return std::nullopt;
    }
    // match numbers
    if(std::isdigit(line[index])) {
        std::stringstream num_literal;
        while (std::isdigit(line[index])) {

        }
    }
    // match operator tokens
    switch (line[index]) {
    case '(': 
        tokens.push_back(Token(Token::OpenParen));
        index++;
        break;
    case ')':
        tokens.push_back(Token(Token::CloseParen));
        index++; 
        break;
    case '=':
        tokens.push_back(Token(Token::Equal));
        index++;
        break;
    case '>':
        if (index + 1 < line.size() || line[index + 1] != '=') {
            tokens.push_back(Token(Token::GreaterThan));
        } else {
            index++;
            tokens.push_back(Token(Token::GreaterThanOrEqualTo));
        }
        index++;
        break;
    case '<':
        if (index + 1 < line.size()
            || (line[index + 1] != '=' && line[index + 1] != '>')) {
            tokens.push_back(Token(Token::LessThan));
        } else if (line[index + 1] == '>') {
            tokens.push_back(Token(Token::NotEqualTo));
            index++;
        } else {
            tokens.push_back(Token(Token::LessThanOrEqualTo));
            index++;
        }
        index++;
        break;
    } // end switch(line[index])
    return std::nullopt;
}