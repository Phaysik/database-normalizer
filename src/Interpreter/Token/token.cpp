/*! \file token.cpp
    \brief C++ file for creating a token.
    \details Contains the function definitions for creating a token
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Interpreter/Token/token.h"

namespace normalizer::interpreter::token
{
    /* Getters and Setters */

    TokenCategories Token::getTokenCategory() const
    {
        return this->tokenCategory;
    }

    TokenConstants Token::getTokenType() const
    {
        return this->tokenType;
    }

    us Token::getLineNumber() const
    {
        return this->lineNumber;
    }

    us Token::getLineOffset() const
    {
        return this->offset;
    }

    us Token::getTokenLength() const
    {
        return this->tokenLength;
    }

    std::string Token::getTokenValue() const
    {
        return this->tokenValue;
    }

    /* Operator Overloads */

    std::ostream &operator<<(std::ostream &outputStream, const Token &token)
    {
        const std::string TOKEN_TEXT = "TOKEN: " + tokenToString[token.getTokenType()];
        const std::string LEXEME_TEXT = "LEXEME: " + token.getTokenValue();

        const us TOKEN_TEXT_WIDTH = 20;

        outputStream << std::left << std::setw(TOKEN_TEXT_WIDTH) << TOKEN_TEXT;
        outputStream << LEXEME_TEXT;

        return outputStream;
    }
} // Namespace normalizer::interpreter::token