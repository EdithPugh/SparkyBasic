// By Edith Pugh on 2026-04-10

#include "parse.hpp"

#include "token.hpp"

#include <vector>
#include <cctype>
#include <strstream>
#include <string>
#include <optional>

using namespace basic;

std::optional<ParseResult::Err> parse_by_char(const std::string& line,
    size_t& index,
    std::vector<Token>& tokens) {
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
        case '>':
            if (index + 1 < line.size() || line[index + 1] != '=') {
                tokens.push_back(Token(Token::GreaterThan));
            } else {
                tokens.push_back(Token(Token::GreaterThanOrEqualTo));
            }
        case '<':
            if (index + 1 < line.size()
                || (line[index + 1] != '=' && line[index + 1] != '>')) {
                tokens.push_back(Token(Token::LessThan));
            } else if (line[index + 1] == '>') {
                tokens.push_back(Token(Token::NotEqualTo));
            } else {
                tokens.push_back(Token(Token::LessThanOrEqualTo));
            }
    } // end switch(line[index])
    return std::nullopt;
}

ParseResult parse_line(const std::string& line) {
    std::vector<Token> tokens;
    size_t index = 0;
    // skip initial whitespace to allow for indentation
    while (std::isspace(line[index])) {
        index++;
    }
    if (line[index] == '0') {
        return {
            ParseResult::Err{"Line numbers cannot have leading zeroes."}
        };
    }
    if (line[index] == '-') {
        return {
            ParseResult::Err{"Line numbers cannot be negative"}
        };
    }
    // eat linenum rq
    std::strstream line_num_stream;
    while (index < line.size() && std::isdigit(line[index])) {
        line_num_stream << line[index];
        index++;
    }
    // specialised more helpful error message
    if (line[index] == '.') {
        return {
            ParseResult::Err{"Line numbers must be integers"}
        };
    }
    if (!std::isspace(line[index])) {
        return {
            ParseResult::Err{"Missing space between line number and command."}
        };
    }
    std::string line_num_string = line_num_stream.str();
    if (line_num_string.size() != 0) {
        // shouldn't throw, since it's just a string of digits
        size_t line_num = std::stoul(line_num_string);
        tokens.push_back(Token::from_line_num(line_num));
    }
    // now get to actual tokenizing
    while (index < line.size()) {
        auto opt_result = parse_by_char(line, index, tokens);
        if (opt_result.has_value()) {
            return {
                opt_result.value()
            };
        }
    } // end while(index < line.size())
    return {
        ParseResult::Ok{tokens}
    };
} // end parse_line