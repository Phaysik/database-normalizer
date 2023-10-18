/*! \file lexerValidator.cpp
    \brief C++ file for creating a lexerValidator.
    \details Contains the function definitions for creating a lexerValidator
    \date 10/16/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Interpreter/Lexer/lexerValidator.h"

namespace normalizer::interpreter::lexer
{
    void LexerValidator::validateTextContentInRange(const std::string &textContent, const us characterIndex)
    {
        if (characterIndex >= textContent.length())
        {
            throw std::out_of_range("Error: Index out of range (Index too large)");
        }
    }

    void LexerValidator::validateCharacterIndexAboveZero(const us characterIndex)
    {
        if (characterIndex <= 0)
        {
            throw std::out_of_range("Error: Index out of range (Index too small)");
        }
    }
} // Namespace normalizer::interpreter::lexer