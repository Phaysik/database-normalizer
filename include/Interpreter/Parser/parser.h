/*! \file parser.h
    \brief Header file for creating a SQL and dependency parser.
    \details Contains the function declarations for creating a SQL and dependency parser
    \date 10/22/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "aliases.h"
#include "Interpreter/Lexer/lexer.h"
#include "Interpreter/Token/literalToken.h"
#include "Interpreter/Token/tokenConstants.h"
#include "Interpreter/Parser/parserValidator.h"

namespace normalizer::interpreter::parser
{
    /*! \headerfile parser.h
        \brief The parser class
        \details The parser that will validate the SQL and dependency inputs
        \date 10/22/2023
        \version 1.0
        \author Matthew Moore
    */
    class Parser
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Creates a Parser instance
            \param[in] textContent The text content to be parsed
            \date 10/22/2023
            \version 1.0
            \author Matthew Moore
        */
        Parser(const std::string &textContent);

        /* Member Functions */

        /*! \brief Parses the input text
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parse();

    private:
        /* Member Functions */

        /*! \brief Gets the next token
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
            \return LiteralToken The next token to parse
        */
        normalizer::interpreter::token::LiteralToken getNextToken();

        /*! \brief Gets the previous token
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
            \return LiteralToken The previous token to parse
        */
        normalizer::interpreter::token::LiteralToken goBackToPreviousToken();

        /*! \brief Determins if #tokensIndex is at the end of #tokens
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
            \return bool Whether or not #tokensIndex is at the end of #tokens
        */
        bool hasMoreTokens() const;

        /*! \brief Parses the \ref normalizer::interpreter::token::TokenConstants::T_CREATE "T_CREATE" statement
            \date 10/22/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseCreateStatement();

        /*! \brief Parses the \ref normalizer::interpreter::token::TokenConstants::T_TABLE "T_TABLE" statement
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseTableStatement();

        /*! \brief Parses the body of the CREATE TABLE statement
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseTableBody();

        /*! \brief Parses a row in the TABLE body
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseTableRows();

        /*! \brief Parses the \ref normalizer::interpreter::token::TokenConstants::T_INTEGER "T_INTEGER" statement
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseIntegerToken();

        /*! \brief Parses the \ref normalizer::interpreter::token::TokenConstants::T_VARCHAR "T_VARCHAR" statement
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseVarcharToken();

        /*! \brief Parses the \ref normalizer::interpreter::token::TokenConstants::T_INTCONST "T_INTCONST" for datatypes, such as \ref normalizer::interpreter::token::TokenConstants::T_INTEGER "T_INTEGER" and \ref normalizer::interpreter::token::TokenConstants::T_VARCHAR "T_VARCHAR"
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseDataTypeSize();

        /*! \brief Parses the generic tokens that can be applied to all table rows
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseGenericColumnDefinitions();

        /*! \brief Parses the dependencies of the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseDependencies();

        /*! \brief Parses multi valued dependency
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseMultiValuedDependencies();

        /*! \brief Parses multiple dependent columns
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseMultipleDependentColumns();

        /*! \brief Parses the primary key of the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseKey();

        /*! \brief Parses the multiple primary keys of the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void parseMultiplePrimaryKeys();

        us tokensIndex;                                                   /*!< The index of #tokens */
        std::vector<normalizer::interpreter::token::LiteralToken> tokens; /*!< The list of tokens from \ref normalizer::interpreter::lexer::Lexer::grabAllTokens "Lexer::grabAllTokens()" */
        std::vector<std::string> splitTextContent;                        /*!< The text content split on newlines for easier error printing */
    };
} // Namespace normalizer::interpreter::parser