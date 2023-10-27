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
#include "Table/TableRow/RowDefinition/genericRowDefinition.h"
#include "Table/TableRow/tableRow.h"
#include "Table/table.h"
#include "Dependencies/DependencyRow/dependencyRow.h"
#include "Dependencies/dependencyManager.h"

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

        /*! \brief Creates a Parser instance
            \param[in] textContent The text content to be parsed
            \param[in] sqlTable The parsed sql table
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        Parser(const std::string &textContent, const normalizer::table::Table &sqlTable);

        /*! \brief The default destructor
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        ~Parser() {}

        /* Getters and Setters */

        /*! \brief Get the parsed table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return Table The parsed table
        */
        normalizer::table::Table getTable() const;

        /*! \brief Get the parsed dependency manager
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return DependencyManager The parsed dependency manager
        */
        normalizer::dependencies::DependencyManager getDependencyManager() const;

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

        /*! \brief Adds a dependency row to #dependencyRows if it does not already exist
            \param[in] rowName The name of the dependency row
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void addDependencyRowIfNotExists(const std::string &rowName);

        /*! \brief Adds a single valued dependency to #dependencyRows
            \param[in] dependentValue The value of the single valued dependency
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void addSingleDependency(const std::string &dependentValue);

        /*! \brief Adds a multi valued dependency to #dependencyRows
            \param[in] dependentValue The value of the multi valued dependency
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void addMultiDependency(const std::string &dependentValue);

        /*! \brief Calls the appropriate validation function for either single or multi valued dependencies
            \param[in] currentToken The current token to validate
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void callAppropriateDependentValidation(const token::LiteralToken &currentToken);

        us tokensIndex;                                                           /*!< The index of #tokens */
        std::vector<normalizer::interpreter::token::LiteralToken> tokens;         /*!< The list of tokens from \ref normalizer::interpreter::lexer::Lexer::grabAllTokens "Lexer::grabAllTokens()" */
        std::vector<std::string> splitTextContent;                                /*!< The text content split on newlines for easier error printing */
        normalizer::table::Table table;                                           /*!< The table that will be created */
        normalizer::table::row::GenericRowDefinition currentRowDefinition;        /*!< The current definition of the row to be added to #table */
        normalizer::dependencies::DependencyManager dependencyManager;            /*!< The dependency manager that will be used to create the dependencies */
        std::vector<normalizer::dependencies::row::DependencyRow> dependencyRows; /*!< The list of dependency rows that will be added to #dependencyManager */
        std::string currentDependencyRowName;                                     /*!< The name of the current dependency row */
        bool multiValuedDependency;
        /*!< Whether or not the current dependency row is a multi valued dependency */
    };
} // Namespace normalizer::interpreter::parser