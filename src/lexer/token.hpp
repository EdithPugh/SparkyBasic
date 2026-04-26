#pragma once
// By Edith Pugh on 2026-04-10

#include <variant>
#include <string>
#include <cassert>
#include <ostream>
#include <optional>

namespace lexer {

/**
 * A struct representing a single Token produced by the lexer.
 */
class Token {
public:
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

        // Used for indexing lists and grouping mathematical operations
        OpenParen,
        CloseParen,

        // numerical operators
        Add,
        Sub,
        Mul,
        Div,
    };
private:
    using ValueType = std::variant<
        std::monostate,
        std::string,
        double,
        size_t
    >;

    const Type type;
    const ValueType value;
    Token(Type type, ValueType value)
        : type(type)
        , value(value) {}
public:
    auto get_type() const -> Type { return type; }
    
    /**
     * Getter function for the name of a num or str variable.
     * @result: Returns nullopt if the token is not a num or str variable.
     */
    auto get_var_name() const -> std::optional<std::string_view>;
    /**
     * Getter function returning the contents of a string literal, without the
     * surrounding quotes.
     * @result: Returns nullopt if the token is not a string literal.
     */
    auto get_string() const -> std::optional<std::string_view>; 
    /**
     * Getter function that returns the value of a num literal.
     * @result: Returns nullopt if the token is not a num literal.
     */
    auto get_number() const -> std::optional<double>;
    /**
     * A getter function for the line num token that returns the line num.
     * @result: Returns nullopt if the token is not a line number.
     */
    auto get_line_num() const -> std::optional<size_t>;
    /**
     * Creates a token from a num literal.
     * @param num the number that comprises the literal
     * @return the newly constructed token.
     */
    static auto from_literal(double num) -> Token;
    /**
     * Creates a token from a string literal
     * @param str the string that comprises the literal, without quotes.
     * @return the newly constructed token
     */
    static auto from_literal(std::string&& str) -> Token;
    /**
     * Creates a token from a line number literal.
     * @param num the line number
     * @return the newly constructed token
     */
    static auto from_line_num(size_t num) -> Token;
    /**
     * Creates a token from a set of uppercase letters and optionally a dollar
     * sign at the end.
     * @param id the characters that make up the symbol
     * @return a new Token that is either a keyword, function, or variable name.
     */
    static auto from_var_or_keyword(std::string&& id) -> Token;
    /**
     * The base constructor for tokens that do not contain a value.
     * @param new_type the type of the new token. must refer to a monostatic
     * type, i.e. not a literal, var name, or line number.
     * @return an optional that contains the new Token if param was valid.
     */
    static auto from_mono(Type new_type) -> Token;
    
    friend auto operator<<(std::ostream& stream, const Token& token)
        -> std::ostream&;
}; // End struct Token

/**
 * Allows a Token to be directly outputted into a stream for debug purposes.
 * Will print the Token's type as well as any value it may have.
 * @param os: The stream that the Token is printed to.
 * @param token: The Token that is to be printed.
 * @return returns os as is standard with stream operators.
 */
auto operator<<(std::ostream& stream, const Token& token) -> std::ostream&;

}