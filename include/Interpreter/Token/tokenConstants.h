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
        T_IDENTIFIER, /*!< Indentifiers */
        T_CREATE,     /*!< CREATE */
        T_TABLE,      /*!< TABLE */
        T_IF,         /*!< IF */
        T_NOT,        /*!< NOT */
        T_NULL,       /*!< NULL */
        T_EXISTS,     /*!< EXISTS */
        T_INT,        /*!< INT */
        T_INTEGER,    /*!< INTEGER */
        T_VARCHAR,    /*!< VARCHAR */
        T_LPAREN,     /*!< ( */
        T_RPAREN,     /*!< ) */
        T_INTCONST,   /*!< INTEGER VALUE */
        T_SEMICOLON,  /*!< ; */
        T_COMMA,      /*!< , */
        T_KEY,        /*!< KEY */
        T_COLON,      /*!< : */
        T_DASH,       /*!< - */
        T_RANGLE,     /*!< > */
        T_UNKNOWN,    /*!< UNKNOWN */
    };

    static std::unordered_map<TokenConstants, std::string> tokenToString = {
        {TokenConstants::T_IDENTIFIER, "IDENTIFIER"},
        {TokenConstants::T_CREATE, "CREATE"},
        {TokenConstants::T_TABLE, "TABLE"},
        {TokenConstants::T_IF, "IF"},
        {TokenConstants::T_NOT, "NOT"},
        {TokenConstants::T_NULL, "NULL"},
        {TokenConstants::T_EXISTS, "EXISTS"},
        {TokenConstants::T_INT, "INT"},
        {TokenConstants::T_INTEGER, "INTEGER"},
        {TokenConstants::T_VARCHAR, "VARCHAR"},
        {TokenConstants::T_LPAREN, "LPAREN"},
        {TokenConstants::T_RPAREN, "RPAREN"},
        {TokenConstants::T_INTCONST, "INTCONST"},
        {TokenConstants::T_SEMICOLON, "SEMICOLON"},
        {TokenConstants::T_COMMA, "COMMA"},
        {TokenConstants::T_KEY, "KEY"},
        {TokenConstants::T_COLON, "COLON"},
        {TokenConstants::T_DASH, "DASH"},
        {TokenConstants::T_RANGLE, "RANGLE"},
        {TokenConstants::T_UNKNOWN, "UNKNOWN"},
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