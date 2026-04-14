// By Edith Pugh on 2026-04-10

#include "parse.hpp"

#include "token.hpp"
#include "error_messages.hpp"
#include "parse_token.hpp"

#include <vector>
#include <cctype>
#include <sstream>
#include <string>
#include <optional>

using namespace basic;

// helper function to eat line num
std::optional<ParseResult::Err> parse_line_num(const std::string& line,
    size_t& index,
    std::vector<Token>& tokens);

ParseResult parse_line(const std::string& line) {
    std::vector<Token> tokens;
    size_t index = 0;
    { // run line num
        auto opt_result = parse_line_num(line, index, tokens);
        if (opt_result.has_value()) {
            return {
                opt_result.value()
            };
        }
    }
    // now get to actual tokenizing
    while (index < line.size()) {
        auto opt_result = parse_token(line, index, tokens);
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

// HELPERS

std::optional<ParseResult::Err> parse_line_num(const std::string& line,
    size_t& index,
    std::vector<Token>& tokens) {
    // skip initial whitespace to allow for indentation
    while (std::isspace(line[index])) {
        index++;
    }
    if (line[index] == '0') {
        return ParseResult::Err{k_msg_line_num_leading_zero};
    }
    if (line[index] == '-') {
        return ParseResult::Err{k_msg_line_num_negative};
    }
    // eat linenum rq
    std::stringstream line_num_stream;
    while (index < line.size() && std::isdigit(line[index])) {
        line_num_stream << line[index];
        index++;
    }
    // specialised more helpful error message
    if (line[index] == '.') {
        return ParseResult::Err{k_msg_line_num_non_int};
    }
    if (!std::isspace(line[index])) {
        return ParseResult::Err{
            k_msg_line_num_missing_space};
    }
    std::string line_num_string = line_num_stream.str();
    if (line_num_string.size() != 0) {
        // shouldn't throw, since it's just a string of digits
        size_t line_num = std::stoul(line_num_string);
        tokens.push_back(Token::from_line_num(line_num));
    }
    return std::nullopt;
}