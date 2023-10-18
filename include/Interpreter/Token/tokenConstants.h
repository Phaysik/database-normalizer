/*! \file tokenConstants.h
    \brief Header file for Token constants.
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <unordered_map>

namespace normalizer::interpreter::token
{
    /*! \headerfile tokenConstants.h
        \brief List of valid tokens
        \details Valid tokens represented in an enum class
        \date 10/11/2023
        \version 1.0
        \author Matthew Moore
    */
    enum class TokenConstants
    {
        T_IDENTIFIER,
        T_CREATE,
        T_TABLE,
        T_IF,
        T_NOT,
        T_NULL,
        T_EXISTS,
        T_INT,
        T_INTEGER,
        T_VARCHAR,
        T_LPAREN,
        T_RPAREN,
        T_INTCONST,
        T_SEMICOLON,
        T_COMMA,
        T_KEY,
        T_COLON,
        T_DASH,
        T_RANGLE,
        T_UNKNOWN,
    };

    static std::unordered_map<TokenConstants, std::string> tokenToString = {
        {TokenConstants::T_IDENTIFIER, "T_IDENTIFIER"},
        {TokenConstants::T_CREATE, "T_CREATE"},
        {TokenConstants::T_TABLE, "T_TABLE"},
        {TokenConstants::T_IF, "T_IF"},
        {TokenConstants::T_NOT, "T_NOT"},
        {TokenConstants::T_NULL, "T_NULL"},
        {TokenConstants::T_EXISTS, "T_EXISTS"},
        {TokenConstants::T_INT, "T_INT"},
        {TokenConstants::T_INTEGER, "T_INTEGER"},
        {TokenConstants::T_VARCHAR, "T_VARCHAR"},
        {TokenConstants::T_LPAREN, "T_LPAREN"},
        {TokenConstants::T_RPAREN, "T_RPAREN"},
        {TokenConstants::T_INTCONST, "T_INTCONST"},
        {TokenConstants::T_SEMICOLON, "T_SEMICOLON"},
        {TokenConstants::T_COMMA, "T_COMMA"},
        {TokenConstants::T_KEY, "T_KEY"},
        {TokenConstants::T_COLON, "T_COLON"},
        {TokenConstants::T_DASH, "T_DASH"},
        {TokenConstants::T_RANGLE, "T_RANGLE"},
        {TokenConstants::T_UNKNOWN, "T_UNKNOWN"},
    }; /*!< Convert a string to it's \ref normalizer::interpreter::token::Token "Token" representation */

    static std::unordered_map<std::string, TokenConstants> stringToToken = {
        {"CREATE", TokenConstants::T_CREATE},
        {"TABLE", TokenConstants::T_TABLE},
        {"IF", TokenConstants::T_IF},
        {"NOT", TokenConstants::T_NOT},
        {"NULL", TokenConstants::T_NULL},
        {"EXISTS", TokenConstants::T_EXISTS},
        {"INT", TokenConstants::T_INT},
        {"INTEGER", TokenConstants::T_INTEGER},
        {"VARCHAR", TokenConstants::T_VARCHAR},
        {"(", TokenConstants::T_LPAREN},
        {")", TokenConstants::T_RPAREN},
        {";", TokenConstants::T_SEMICOLON},
        {",", TokenConstants::T_COMMA},
        {"KEY", TokenConstants::T_KEY},
        {":", TokenConstants::T_COLON},
        {"-", TokenConstants::T_DASH},
        {">", TokenConstants::T_RANGLE},
    }; /*!< Convert a string to it's \ref normalizer::interpreter::token::Token "Token" representation */

    /*! \headerfile tokenConstants.h
        \brief The categories that a \ref normalizer::interpreter::token::Token "Token" may be
        \date 10/11/2023
        \version 1.0
        \author Matthew Moore
    */
    enum class TokenCategories
    {
        STRING,
        INT,
        CHAR
    };
}