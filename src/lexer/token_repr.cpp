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

std::ostream& operator<<(std::ostream& os, const Token& token) {
    switch (token.type) {
    case Token::KwNew: os << k_KwNew_str; break;
    case Token::KwRun: os << k_KwRun_str; break;
    case Token::KwList: os << k_KwList_str; break;
    case Token::KwClear: os << k_KwClear_str; break;
    case Token::KwPrint: os << k_KwPrint_str; break;
    case Token::KwInput: os << k_KwInput_str; break;
    case Token::KwLet: os << k_KwLet_str; break;
    case Token::KwDim: os << k_KwDim_str; break;
    case Token::KwIf: os << k_KwIf_str; break;
    case Token::KwThen: os << k_KwThen_str; break;
    
    case Token::LineNum: {
        os << k_LineNum_str;
        os << '(';
        os << std::get<size_t>(token.value);
        os << ')';
        break;
    }
    case Token::NumLiteral: {
        os << k_NumLiteral_str;
        os << '(';
        os << std::get<double>(token.value);
        os << ')';
        break;
    }
    case Token::StrLiteral: {
        os << k_StrLiteral_str;
        os << '(';
        os << std::get<std::string>(token.value);
        os << ')';
        break;
    }
    
    case Token::NumVar: {
        os << k_NumVar_str;
        os << '(';
        os << std::get<std::string>(token.value);
        os << ')';
        break;
    }
    case Token::StrVar: {
        os << k_StrVar_str;
        os << '(';
        os << std::get<std::string>(token.value);
        os << ')';
        break;
    }
    
    case Token::Semicolon: os << k_Semicolon_str; break;
    case Token::Comma: os << k_Comma_str; break;
    case Token::Equal: os << k_Equal_str; break;
    case Token::GreaterThan: os << k_GreaterThan_str; break;
    case Token::LessThan: os << k_LessThan_str; break;
    case Token::NotEqualTo: os << k_NotEqualTo_str; break;
    case Token::LessThanOrEqualTo: os << k_LessThanOrEqualTo_str; break;
    case Token::GreaterThanOrEqualTo: os << k_GreaterThanOrEqualTo_str; break;
    case Token::OpenParen: os << k_OpenParen_str; break;
    case Token::CloseParen: os << k_CloseParen_str; break;

    case Token::Add: os << k_Add_str; break;
    case Token::Sub: os << k_Sub_str; break;
    case Token::Mul: os << k_Mul_str; break;
    case Token::Div: os << k_Div_str; break;
    }
    return os;
}

}