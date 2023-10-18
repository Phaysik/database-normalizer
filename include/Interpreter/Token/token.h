/*! \file token.h
    \brief Header file for creating a Token for lexical analysis.
    \details Contains the function declarations for creating a Token for lexical analysis
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "tokenConstants.h"
#include "aliases.h"

namespace normalizer::interpreter::token
{
    /*! \headerfile token.h
        \brief Creates a Token for lexical analysis
        \date 10/11/2023
        \version 1.0
        \author Matthew Moore
    */
    class Token
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Create a new #Token
            \details Creates a token with its line number, its offset, and its length
            \pre \p category must be a valid #TokenCategories and \p token must be a valid #TokenConstants value.
            \param[in] category The cateogry of the token
            \param[in] token The token type to create
            \param[in] value The token value as a string
            \param[in] lineNum The line of the token
            \param[in] lineOffset The offset of the token in the line
            \param[in] tokLength The length of the token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
        */
        Token(const TokenCategories &category, const TokenConstants &token, const std::string &value, const us lineNum, const us lineOffset, const us tokLength) : tokenCategory(category), tokenType(token), tokenValue(value), lineNumber(lineNum), offset(lineOffset), tokenLength(tokLength){};

        /* Getters and Setters */

        /*! \brief Get the category of the #Token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return TokenCategories The category of the token
        */
        TokenCategories getTokenCategory() const;

        /*! \brief Get the type of the #Token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return TokenConstants The token type
        */
        TokenConstants getTokenType() const;

        /*! \brief Get the line number of the #Token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return us The line number
        */
        us getLineNumber() const;

        /*! \brief Get the line offset of the #Token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return us The line offset of the token in the line
        */
        us getLineOffset() const;

        /*! \brief Get the length of the #Token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return us The length of the token
        */
        us getTokenLength() const;

        /*! \brief Get the value of the #Token
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return std::string the value of the token
        */
        std::string getTokenValue() const;

        /* Operator Overloads */

        /*! \brief Pretty print the \ref #normalizer::interpreter::token::Token "Token"
            \pre \p os must be a stream that is writeable to
            \post \p os will have the updated text to write to the stream.
            \param[in, out] outputStream The stream to write to
            \param[in] token The \ref #normalizer::interpreter::token::Token "Token" to write out
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return std::ostream The output stream
        */
        friend std::ostream &operator<<(std::ostream &outputStream, const Token &token);

    private:
        TokenCategories tokenCategory; /*!< The category of the token */
        TokenConstants tokenType;      /*!< The type of the token */
        std::string tokenValue;        /*!< The value of the token */
        us lineNumber;                 /*!< The line number of the token */
        us offset;                     /*!< The offset of the token in the line */
        us tokenLength;                /*!< The length of the token */
    };
}