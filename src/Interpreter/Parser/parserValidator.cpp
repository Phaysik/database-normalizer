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

    void ParserValidator::validateRowNameDoesntExist(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const normalizer::table::Table &table, const std::string &rowName)
    {
        const std::vector<normalizer::table::row::TableRow> tableRows = table.getTableRows();

        std::string errorString = ParserValidator::constructBasicErrorMessage(token, textLine);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was a duplicated row name found";

        for (const normalizer::table::row::TableRow &tableRow : tableRows)
        {
            if (rowName == tableRow.getRowName())
            {
                throw std::invalid_argument(errorString);
            }
        }
    }

    void ParserValidator::validatePrimaryKey(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const normalizer::dependencies::DependencyManager &dependencyManager)
    {
        std::string errorString = ParserValidator::constructBasicErrorMessage(token, textLine);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was a duplicated primary key declaration found.\n";

        if (dependencyManager.getPrimaryKeys().size() > 0)
        {
            throw std::invalid_argument(errorString);
        }
    }

    void ParserValidator::validateSingleDependencyExists(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName)
    {
        std::string errorString = ParserValidator::constructBasicDependencyMessage(token, textLine, false);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was a duplicated single dependency row name found.\n";

        for (const normalizer::dependencies::row::DependencyRow &dependencyRow : dependencyRows)
        {
            if (dependencyRow.getRowName() == currentRowName)
            {
                if (dependencyRow.getSingleDependencies().size() > 0)
                {
                    throw std::invalid_argument(errorString);
                }
            }
        }
    }

    void ParserValidator::validateSingleDependentValue(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName)
    {
        std::string errorString = ParserValidator::constructBasicErrorMessage(token, textLine);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was a duplicated dependent value found.\n";

        for (const normalizer::dependencies::row::DependencyRow &dependencyRow : dependencyRows)
        {
            if (dependencyRow.getRowName() == currentRowName)
            {
                for (const std::string &dependencyValue : dependencyRow.getSingleDependencies())
                {
                    if (token.getTokenValue() == dependencyValue)
                    {
                        throw std::invalid_argument(errorString);
                    }
                }
            }
        }
    }

    void ParserValidator::validateMultiDependencyExists(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName)
    {
        std::string errorString = ParserValidator::constructBasicDependencyMessage(token, textLine, true);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was a duplicated multi dependency row name found.\n";

        for (const normalizer::dependencies::row::DependencyRow &dependencyRow : dependencyRows)
        {
            if (dependencyRow.getRowName() == currentRowName)
            {
                if (dependencyRow.getMultiDependencies().size() > 0)
                {
                    throw std::invalid_argument(errorString);
                }
            }
        }
    }

    void ParserValidator::validateMultiDependentValue(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const std::vector<normalizer::dependencies::row::DependencyRow> &dependencyRows, const std::string &currentRowName)
    {
        std::string errorString = ParserValidator::constructBasicErrorMessage(token, textLine);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was a duplicated dependent value found.\n";

        for (const normalizer::dependencies::row::DependencyRow &dependencyRow : dependencyRows)
        {
            if (dependencyRow.getRowName() == currentRowName)
            {
                for (const std::string &dependencyValue : dependencyRow.getMultiDependencies())
                {
                    if (token.getTokenValue() == dependencyValue)
                    {
                        throw std::invalid_argument(errorString);
                    }
                }
            }
        }
    }

    void ParserValidator::validateRowName(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const normalizer::table::Table &table)
    {
        std::string errorString = ParserValidator::constructBasicErrorMessage(token, textLine);

        errorString += "On line number " + std::to_string(token.getLineNumber() + 1) + " there was a row name that does not exist in the table found.\n";

        const std::vector<normalizer::table::row::TableRow> tableRows = table.getTableRows();

        for (const normalizer::table::row::TableRow &row : tableRows)
        {
            if (row.getRowName() == token.getTokenValue())
            {
                return;
            }
        }

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

    std::string ParserValidator::constructBasicDependencyMessage(const normalizer::interpreter::token::LiteralToken &token, const std::string &textLine, const bool isMultiValued)
    {
        std::string errorString = textLine + '\n';

        for (us i = 0; i < static_cast<us>(token.getLineOffset()); ++i) // Zero base so 1 less than the line offset
        {
            errorString += " ";
        }

        for (us i = 0; i < 2 + (isMultiValued ? 1 : 0); ++i)
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