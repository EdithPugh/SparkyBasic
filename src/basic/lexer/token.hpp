#pragma once
// By Edith Pugh on 2026-04-10

#include <variant>
#include <string>
#include <cassert>
#include <ostream>

namespace basic::lexer {

struct Token {
    enum Type {
        // erases all stored commands
        KwNew,
        // executes commands in program
        KwRun,
        // lists all the commands in program, sorted by line number.
        KwList,
        // frees a value
        KwClear,
        // prints a value
        KwPrint,
        // prints a question mark and space, then takes input and places it
        // in a variable. If no input is entered, the program is aborted.
        KwInput,
        // optional for declaring a new variable
        KwLet,
        // allows additional list memory to be allocate by variables
        // (all variables can be trivially converted to lists)
        KwDim,
        // If and Then keywords for condititonal jumping, else is not
        // supported in either 4k or 8k BASIC as far as I can tell
        KwIf,
        KwThen,

        // Like NumLiteral, but no funny business with negatives or non-int
        // values.
        LineNum,
        // a number
        NumLiteral,
        // a string
        StrLiteral,

        // For variable names
        NumVar,

        // For variable names which end in $
        StrVar,

        // used for concatonating two values in print
        Semicolon,
        // indicates that the line will be split into 5 columns of 14, and
        // then moves to the next column.
        Comma,

        // Relation tokens, for comparing and, in the case of Equal,
        // assignment
        Equal,
        GreaterThan,
        LessThan,
        // The <> operator
        NotEqualTo,
        LessThanOrEqualTo,
        GreaterThanOrEqualTo,

        // Just used for indexing lists, as far as I can tell
        OpenParen,
        CloseParen,
    } type; // End enum Type

    std::variant<std::monostate, std::string, double, size_t> value;

    static Token from_literal(double num);
    static Token from_literal(const std::string& str);
    static Token from_line_num(size_t num);
    static Token from_var_or_keyword(const std::string& id);
    
    Token(Type sym)
        : type(sym)
        , value(std::monostate()) {
        assert(sym != NumLiteral && sym != StrLiteral);
    }
private:
    Token(Type type, std::variant<std::monostate, 
        std::string, double, size_t>&& value)
        : type(type)
        , value(std::move(value)) {}
}; // End struct Token

std::ostream& operator<<(std::ostream& os, const Token& token);

}