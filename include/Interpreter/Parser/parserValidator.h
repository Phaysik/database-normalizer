/*! \file parserValidator.h
    \brief Header file for creating a validator for parsing.
    \details Contains the function declarations for creating a validator for parsing
    \date 10/22/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <vector>
#include <system_error>

#include "aliases.h"
#include "constants.h"
#include "Interpreter/Token/literalToken.h"
#include "Table/table.h"
#include "Table/TableRow/tableRow.h"
#include "Dependencies/dependencyManager.h"
#include "Dependencies/DependencyRow/dependencyRow.h"
namespace normalizer::interpreter::parser
{
    /*! \headerfile parserValidator.h
        \brief Validates semantic analysis
        \details Determines whether certain calls in the parser are valid
        \date 10/22/2023
        \version 1.0
        \author Matthew Moore
    */
    class ParserValidator
    {
    public:
        /* Static Methods */

        /*! \brief Determines if \p tokensIndex is in range of \p tokens
            \post The program may throw an error depending on it \p tokensIndex is in range of \p tokens
            \param[in] tokens The list of tokens
            \param[in] tokensIndex The index to validate
            \date 10/22/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateCanGetMoreTokens(const std::vector<normalizer::interpreter::token::LiteralToken> &tokens, const us tokensIndex);

        /*! \brief Determines if \p tokensIndex is greater than 0
            \post The program may throw an error depending on it \p tokensIndex is less than or equal to 0
            \param[in] tokensIndex The index to validate
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateCanGetPreviousToken(const us tokensIndex);

        /*! \brief Throw an error if a parsed token is  \ref normalizer::interpreter::token::TokenConstants::T_UNKNOWN "TokenConstants::T_UNKNOWN"
            \param[in] token The unknown token
            \param[in] textLine The line of the text where \p token was found
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        [[noreturn]] static void throwUknownToken(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine);

        /*! \brief Throw an error if the parsed token is unexpected
            \param[in] token The unexpected token
            \param[in] textLine The line of the text where \p token was
            \param[in] expectedTokenValue The expected value of the token
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
        */
        [[noreturn]] static void throwUnexpectedToken(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::string &expectedTokenValue);

        /*! \brief Determines if \p rowName is already in \p table
            \post The program may throw an error depending on it \p rowName is already in \p table
            \param[in] token The potentially duplicated row name
            \param[in] textLine The line of the text where \p token was
            \param[in] table The table to look through
            \param[in] rowName The row name to validate
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateRowNameDoesntExist(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const normalizer::table::Table &table, const std::string &rowName);

        /*! \brief Determines if \p dependencyManager already has set a primary key
            \post The program may throw an error depending on it \p dependencyManager already has set a primary key
            \param[in] token The potentially duplicated primary key token
            \param[in] textLine The line of the text where \p token was
            \param[in] dependencyManager The manager of the primary key(s)
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validatePrimaryKey(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const normalizer::dependencies::DependencyManager &dependencyManager);

        /*! \brief Determines if \p currentRowName already exists in \p dependencyRows for single valued dependencies
            \post The program may throw an error depending on if \p currentRowName already exists in \p dependencyRows for single valued dependencies
            \param[in] token The potentially duplicated single dependency name
            \param[in] textLine The line of the text where \p token was
            \param[in] dependencyRows The rows of dependencies to check
            \param[in] currentRowName The name of the current dependency row being evaluated
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateSingleDependencyExists(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName);

        /*! \brief Determines if the value of \p token already exists in \p dependencyRows for the \p currentRowName on single-valued dependencies
            \post The program may throw an error depending on if the value of \p token already exists in \p dependencyRows for the \p currentRowName on single-valued dependencies
            \param[in] token The potentially duplicated single dependency dependent value
            \param[in] textLine The line of the text where \p token was
            \param[in] dependencyRows The rows of dependencies to check
            \param[in] currentRowName The name of the current dependency row being evaluated
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateSingleDependentValue(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName);

        /*! \brief Determines if \p currentRowName already exists in \p dependencyRows
            \post The program may throw an error depending on if \p currentRowName already exists in \p dependencyRows for single valued dependencies
            \param[in] token The potentially duplicated single dependency name
            \param[in] textLine The line of the text where \p token was
            \param[in] dependencyRows The rows of dependencies to check
            \param[in] currentRowName The name of the current dependency row being evaluated
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateMultiDependencyExists(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName);

        /*! \brief Determines if the value of \p token already exists in \p dependencyRows for the \p currentRowName on multi-valued dependencies
            \post The program may throw an error depending on if the value of \p token already exists in \p dependencyRows for the \p currentRowName on multi-valued dependencies
            \param[in] token The potentially duplicated single dependency dependent value
            \param[in] textLine The line of the text where \p token was
            \param[in] dependencyRows The rows of dependencies to check
            \param[in] currentRowName The name of the current dependency row being evaluated
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateMultiDependentValue(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName);

        /*! \brief Determines if the value of \p token exists as name in the \p table
            \post The program may throw an error depending on if the value of \p token exists as name in the \p table
            \param[in] token The potentially erraneous row name
            \param[in] textLine The line of the text where \p token was
            \param[in] table The table to look through
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateRowName(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const normalizer::table::Table &table);

    private:
        /* Static Methods */

        /*! \brief Constructs a basic error message
            \param[in] token The unknown token
            \param[in] textLine The line of the text where \p token was found
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The basic error message
        */
        static std::string constructBasicErrorMessage(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine);

        /*! \brief Constructs a basic error message
            \param[in] token The unknown token
            \param[in] textLine The line of the text where \p token was found
            \param[in] isMultiValued Whether the token is a multi-valued token
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The basic error message
        */
        static std::string constructBasicDependencyMessage(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const bool isMultiValued);
    };
}