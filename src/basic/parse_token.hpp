#pragma once
// By Edith Pugh on 2026-04-14

#include <optional>
#include <string>

#include "parse.hpp"

namespace basic {
    std::optional<ParseResult::Err> parse_token(const std::string& line,
        size_t& index,
        std::vector<Token>& tokens);
}