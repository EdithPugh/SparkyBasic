#pragma once
// By Edith Pugh on 2026-04-14

/**
 * A file containing error messages used by the lexer.
 */

#include <string_view>

namespace lexer {

const std::string_view k_msg_line_num_leading_zero
    = "SN: Line numbers cannot have leading zeroes.";
const std::string_view k_msg_line_num_negative
    = "SN: Line numbers cannot be negative.";
const std::string_view k_msg_line_num_non_int
    = "SN: Line numbers must be integers";
const std::string_view k_msg_unexpected_eol_reading_string
    = "SN: Unexpected end of line while reading string";
const std::string_view k_msg_unknown_backspace_sequence
    = "SN: Unknown backspace sequence: \\";
const std::string_view k_msg_unknown_token
    = "SN: Unknown token: ";
const std::string_view k_msg_malformed_num_literal
    = "SN: Malformed number literal: ";
const std::string_view k_msg_num_literal_out_of_range
    = "SN: Number literal out of range: ";

}