// By Edith Pugh on 2026-04-10

#include "lex_line.hpp"

#include "token.hpp"
#include "error_messages.hpp"
#include "lex_token.hpp"

#include <vector>
#include <cctype>
#include <string>
#include <optional>
#include <variant>

namespace lexer {

const size_t k_line_num_prealloc = 4;

// helper function to eat line num
auto lex_line_num(std::string_view line,
    size_t& index,
    std::vector<Token>& tokens)
    -> std::optional<LexResult::Err>;

void skip_whitespace(std::string_view line, size_t& index);

auto lex_line(std::string_view line) -> LexResult {
    std::vector<Token> tokens;
    size_t index = 0;

    skip_whitespace(line, index);

    if (auto error = lex_line_num(line, index, tokens)) {
        return { LexResult::Err{*error} };
    }

    skip_whitespace(line, index);

    // now get to actual tokenizing
    while (index < line.size()) {

        if (line[index] == '\'') {
            break;
        }
        if (index + 2 < line.size()
            && (char)std::toupper(line[index]) == 'R'
            && (char)std::toupper(line[index+1]) == 'E'
            && (char)std::toupper(line[index+2]) == 'M'
        ) {
            break;
        }

        auto token_result = lex_token(line, index);
        if (std::holds_alternative<Token>(token_result)) {
            tokens.push_back(std::get<Token>(token_result));
        }
        else {
            return {std::get<LexResult::Err>(token_result)};
        }

        skip_whitespace(line, index);
    } // end while(index < line.size())
    return {
        LexResult::Ok{tokens}
    };
} // end lex_line

auto lex_line_num(std::string_view line,
    size_t& index,
    std::vector<Token>& tokens)
    -> std::optional<LexResult::Err> {
    if (line[index] == '0') {
        return LexResult::Err{
            std::string(k_msg_line_num_leading_zero)
        };
    }
    if (line[index] == '-') {
        return LexResult::Err{
            std::string(k_msg_line_num_negative)
        };
    }
    // eat linenum rq
    std::string line_num_str;
    line_num_str.reserve(k_line_num_prealloc);
    while (index < line.size() && std::isdigit(line[index]) != 0) {
        line_num_str.push_back(line[index]);
        index++;
    }
    if (line[index] == '.') {
        return LexResult::Err{
            std::string(k_msg_line_num_non_int)
        };
    }
    if (!line_num_str.empty()) {
        // shouldn't throw, since it's just a string of digits
        size_t line_num = std::stoul(line_num_str);
        tokens.push_back(Token::from_line_num(line_num));
    }
    return std::nullopt;
}

void skip_whitespace(std::string_view line, size_t& index) {
    while (index < line.size() && std::isspace(line[index]) != 0) {
        index++;
    }
}

}