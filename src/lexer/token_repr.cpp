// Defines the ostream operator overload for tokens

#include "token.hpp"
#include <string_view>

namespace lexer {

const std::string_view k_KwNew_str = "Kw.New";
const std::string_view k_KwRun_str = "Kw.Run";
const std::string_view k_KwList_str = "Kw.List";
const std::string_view k_KwClear_str = "Kw.Clear";
const std::string_view k_KwPrint_str = "Kw.Print";
const std::string_view k_KwInput_str = "Kw.Input";
const std::string_view k_KwLet_str = "Kw.Let";
const std::string_view k_KwDim_str = "Kw.Dim";
const std::string_view k_KwIf_str = "Kw.If";
const std::string_view k_KwThen_str = "Kw.Then";

const std::string_view k_LineNum_str = "LINENUM";
const std::string_view k_NumLiteral_str = "NUM";
const std::string_view k_StrLiteral_str = "STR";

const std::string_view k_NumVar_str = "NUMVAR";
const std::string_view k_StrVar_str = "STRVAR";

const std::string_view k_Semicolon_str = "';'";
const std::string_view k_Comma_str = "','";
const std::string_view k_Equal_str = "'='";
const std::string_view k_GreaterThan_str = "'>'";
const std::string_view k_LessThan_str = "'<'";
const std::string_view k_NotEqualTo_str = "'<>'";
const std::string_view k_LessThanOrEqualTo_str = "'<='";
const std::string_view k_GreaterThanOrEqualTo_str = "'>='";
const std::string_view k_OpenParen_str = "'('";
const std::string_view k_CloseParen_str = "')'";

const std::string_view k_Add_str = "'+'";
const std::string_view k_Sub_str = "'-'";
const std::string_view k_Mul_str = "'*'";
const std::string_view k_Div_str = "'/'";

auto operator<<(std::ostream& stream, const Token& token) -> std::ostream& {
    switch (token.type) {
    case Token::KwNew: stream << k_KwNew_str; break;
    case Token::KwRun: stream << k_KwRun_str; break;
    case Token::KwList: stream << k_KwList_str; break;
    case Token::KwClear: stream << k_KwClear_str; break;
    case Token::KwPrint: stream << k_KwPrint_str; break;
    case Token::KwInput: stream << k_KwInput_str; break;
    case Token::KwLet: stream << k_KwLet_str; break;
    case Token::KwDim: stream << k_KwDim_str; break;
    case Token::KwIf: stream << k_KwIf_str; break;
    case Token::KwThen: stream << k_KwThen_str; break;
    
    case Token::LineNum: {
        stream << k_LineNum_str;
        stream << '(';
        stream << std::get<size_t>(token.value);
        stream << ')';
        break;
    }
    case Token::NumLiteral: {
        stream << k_NumLiteral_str;
        stream << '(';
        stream << std::get<double>(token.value);
        stream << ')';
        break;
    }
    case Token::StrLiteral: {
        stream << k_StrLiteral_str;
        stream << '(';
        stream << std::get<std::string>(token.value);
        stream << ')';
        break;
    }
    
    case Token::NumVar: {
        stream << k_NumVar_str;
        stream << '(';
        stream << std::get<std::string>(token.value);
        stream << ')';
        break;
    }
    case Token::StrVar: {
        stream << k_StrVar_str;
        stream << '(';
        stream << std::get<std::string>(token.value);
        stream << ')';
        break;
    }
    
    case Token::Semicolon: stream << k_Semicolon_str; break;
    case Token::Comma: stream << k_Comma_str; break;
    case Token::Equal: stream << k_Equal_str; break;
    case Token::GreaterThan: stream << k_GreaterThan_str; break;
    case Token::LessThan: stream << k_LessThan_str; break;
    case Token::NotEqualTo: stream << k_NotEqualTo_str; break;
    case Token::LessThanOrEqualTo: stream << k_LessThanOrEqualTo_str; break;
    case Token::GreaterThanOrEqualTo: stream << k_GreaterThanOrEqualTo_str; break;
    case Token::OpenParen: stream << k_OpenParen_str; break;
    case Token::CloseParen: stream << k_CloseParen_str; break;

    case Token::Add: stream << k_Add_str; break;
    case Token::Sub: stream << k_Sub_str; break;
    case Token::Mul: stream << k_Mul_str; break;
    case Token::Div: stream << k_Div_str; break;
    }
    return stream;
}

}