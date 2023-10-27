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
        /* Static Methods*/

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

    private:
        /* Static Functions */

        /*! \brief Constructs a basic error message
            \param[in] token The unknown token
            \param[in] textLine The line of the text where \p token was found
            \date 10/23/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The basic error message
        */
        static std::string constructBasicErrorMessage(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine);
    };
}