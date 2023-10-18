/*! \file lexer.h
    \brief Header file for creating a Lexer.
    \details Contains the function declarations for creating a Lexer
    \date 10/12/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <regex>
#include <string>
#include <vector>

#include "aliases.h"
#include "constants.h"
#include "Interpreter/Lexer/lexerValidator.h"
#include "Interpreter/Token/literalToken.h"
#include "Interpreter/Token/tokenConstants.h"

namespace normalizer::interpreter::lexer
{
    /*! \headerfile lexer.h
        \brief The Tokenizer of input files
        \details Reads from an input file and tokenizes each value
        \date 10/12/2023
        \version 1.0
        \author Matthew Moore
    */
    class Lexer
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Creates a new #Lexer
            \param[in] inputText The text to tokenize
            \date 10/12/2023
            \version 1.0
            \author Matthew Moore
        */
        Lexer(const std::string &inputText) : textContent(inputText), characterIndex(0), lineNumber(0), lineOffset(0) {}

        /*! \brief Default destructor
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
        */
        ~Lexer(){};

        /* Member Functions */

        /*! \brief Get all tokens in #textContent
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<\ref normalizer::interpreter::token::LiteralToken "LiteralToken"> The list of tokens in #textContent
        */
        std::vector<normalizer::interpreter::token::LiteralToken> grabAllTokens();

    private:
        /* Member Functions */

        /*! \brief Get the next character
                \details Get the next character in the text content, effectively a peek ahead
                \date 10/13/2023
                \version 1.0
                \author Matthew Moore
                \return char The next character in the text content
            */
        char nextChar();

        /*! \brief Regurgitates the last character eaten
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
        */
        void putBackChar();

        /*! \brief Convert a string to a token
            \details Eats string characters to create a token
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
            \return \ref normalizer::interpreter::token::LiteralToken "LiteralToken" The parsed token of the string
        */
        normalizer::interpreter::token::LiteralToken tokenize();

        /*! \brief Will convert a string to an identifier token or an keyword token
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
            \return \ref normalizer::interpreter::token::LiteralToken "LiteralToken" The identifier or keyword token
        */
        normalizer::interpreter::token::LiteralToken eatIdentifierOrKeyword();

        /*! \brief Skips over whitespace characters
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
        */
        void eatWhitespace();

        /*! \brief Will convert a string to an integer token
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
            \return \ref normalizer::interpreter::token::LiteralToken "LiteralToken" The integer token
        */
        normalizer::interpreter::token::LiteralToken eatNumericLiteral();

        /*! \brief Checks if a new character can be grabbed
            \details Checks if #characterIndex is less than the length of #textContent
            \date 10/18/2023
            \version 1.0
            \author Matthew Moore
            \return bool If a new character can be grabbed
        */
        bool canGrabNewChar();

        /* Static Functions */

        /*! \brief Converts a character to their lowercase form
            \param[in] character The character to lowercase
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
            \return char The lowercased character
        */
        static char lowerCharacter(const char character);

        std::string textContent;            /*!< The contents to tokenize */
        us characterIndex;                  /*!< The current index of the string being tokenized */
        us lineNumber;                      /*!< The line number of the token being created */
        us lineOffset;                      /*!< The offset of the token being created */
        std::vector<std::string> allTokens; /*!< The list of all tokens in the input file */
    };
} // Namespace normalizer::interpreter::lexer