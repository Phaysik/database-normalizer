/*! \file literalToken.h
    \brief Header file for creating a literal token.
    \details Contains the function declarations for creating a literal token
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>

#include "aliases.h"
#include "token.h"
#include "tokenConstants.h"

namespace normalizer::interpreter::token
{
    /*! \headerfile literalToken.h
        \brief A Token with a defined type
        \date 10/11/2023
        \version 1.0
        \author Matthew Moore
    */
    class LiteralToken : public Token
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Create a String literal token
            \pre \p tokType must be a valid #TokenConstants value.
            \post Creates a #Token from the parameters
            \param[in] value The value of the token
            \param[in] tokType The type of the token
            \param[in] lineNum The line of the token
            \param[in] lineOffset The offset of the token in the line
            \param[in] tokLength The length of the token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
        */
        LiteralToken(const std::string &value, const TokenConstants &tokType, const us lineNum, const us lineOffset, const us tokLength) : Token(TokenCategories::STRING, tokType, value, lineNum, lineOffset, tokLength) {}

        /*! \brief Create a Character literal token
            \pre \p tokType must be a valid #TokenConstants value.
            \post Creates a #Token from the parameters
            \param[in] value The value of the token
            \param[in] tokType The type of the token
            \param[in] lineNum The line of the token
            \param[in] lineOffset The offset of the token in the line
            \param[in] tokLength The length of the token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
        */
        LiteralToken(const char value, const TokenConstants &tokType, const us lineNum, const us lineOffset, const us tokLength) : Token(TokenCategories::CHAR, tokType, std::string(1, value), lineNum, lineOffset, tokLength) {}

        /*! \brief Create an Integer literal token
            \post Creates a #Token from the parameters
            \param[in] value The value of the token
            \param[in] lineNum The line of the token
            \param[in] lineOffset The offset of the token in the line
            \param[in] tokLength The length of the token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
        */
        LiteralToken(const ul value, const us lineNum, const us lineOffset, const us tokLength) : Token(TokenCategories::STRING, TokenConstants::T_INTCONST, std::to_string(value), lineNum, lineOffset, tokLength) {}
    };
}