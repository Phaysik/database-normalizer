/*! \file parserValidator.cpp
    \brief C++ file for creating a parserValidator.
    \details Contains the function definitions for creating a parserValidator
    \date 10/16/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Interpreter/Parser/parserValidator.h"

namespace normalizer::interpreter::parser
{
    /* Static Methods*/

    void ParserValidator::validateCanGetMoreTokens(const std::vector<normalizer::interpreter::token::LiteralToken> &tokens, const us tokensIndex)
    {
        if (tokensIndex >= tokens.size())
        {
            throw std::out_of_range("Error: Index out of range (Index too large)");
        }
    }

    void ParserValidator::validateCanGetPreviousToken(const us tokensIndex)
    {
        if (tokensIndex <= 0)
        {
            throw std::out_of_range("Error: Index out of range (Index too small)");
        }
    }

    void ParserValidator::throwUknownToken(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine)
    {
        std::string errorString = ParserValidator::constructBasicErrorMessage(token, textLine);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was an unknown token with value \"" + token.getTokenValue() + "\" found.\n";

        throw std::invalid_argument(errorString);
    }

    void ParserValidator::throwUnexpectedToken(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::string &expectedTokenValue)
    {
        std::string errorString = ParserValidator::constructBasicErrorMessage(token, textLine);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was an unexpected token with the token type \"T_" + token::tokenToString[token.getTokenType()] + "\" found.\n";

        for (us i = 0; i < parser::ERROR_WHAT_SIZE; ++i) // Zero base so 1 less than the line offset
        {
            errorString += " ";
        }

        errorString += "Expected grammar syntax is: \"" + expectedTokenValue + "\".\n";

        throw std::invalid_argument(errorString);
    }

    std::string ParserValidator::constructBasicErrorMessage(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine)
    {
        std::string errorString = textLine + '\n';

        for (us i = 0; i < static_cast<us>(token.getLineOffset() - token.getTokenLength() + parser::ERROR_WHAT_SIZE); ++i) // Zero base so 1 less than the line offset
        {
            errorString += " ";
        }

        for (us i = 0; i < token.getTokenLength(); ++i)
        {
            errorString += "^";
        }

        errorString += '\n';

        for (us i = 0; i < parser::ERROR_WHAT_SIZE; ++i) // Zero base so 1 less than the line offset
        {
            errorString += " ";
        }

        return errorString;
    }
} // Namespace normalizer::interpreter::parser