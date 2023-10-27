/*! \file parser.cpp
    \brief C++ file for creating a parser.
    \details Contains the function definitions for creating a parser
    \date 10/22/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Interpreter/Parser/parser.h"

namespace normalizer::interpreter
{
    /* Constructors and Destructors */

    parser::Parser::Parser(const std::string &text) : tokensIndex(0)
    {
        lexer::Lexer lexer(text);

        for (const token::LiteralToken &token : lexer.grabAllTokens())
        {
            this->tokens.push_back(token);
        }

        std::string lineContent;

        for (const char character : text)
        {
            if (character == '\n')
            {
                this->splitTextContent.push_back(lineContent);
                lineContent = "";
            }
            else
            {
                lineContent += character;
            }
        }

        this->splitTextContent.push_back(lineContent); // After last \n add the remainig line
    }

    /* Getters and Setters */

    normalizer::table::Table parser::Parser::getTable() const
    {
        return this->table;
    }

    /* Member Functions */

    void parser::Parser::parse()
    {
        try
        {
            while (this->hasMoreTokens())
            {
                token::LiteralToken currentToken = this->getNextToken();

                switch (currentToken.getTokenType())
                {
                case token::TokenConstants::T_CREATE:
                    this->parseCreateStatement();
                    break;
                case token::TokenConstants::T_IDENTIFIER: // For parsing dependencies
                    this->parseDependencies();
                    break;
                case token::TokenConstants::T_KEY: // For parsing the primary key of the dependencies
                    this->parseKey();
                    break;
                default:
                    // Don't need to specify T_UNKNOWN as a case here as default will catch it
                    ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                    break;
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    token::LiteralToken parser::Parser::getNextToken()
    {
        ParserValidator::validateCanGetMoreTokens(this->tokens, this->tokensIndex);

        return this->tokens[this->tokensIndex++];
    }

    token::LiteralToken parser::Parser::goBackToPreviousToken()
    {
        ParserValidator::validateCanGetPreviousToken(this->tokensIndex - 1);

        return this->tokens[--this->tokensIndex - 1];
    }

    bool parser::Parser::hasMoreTokens() const
    {
        return this->tokensIndex < this->tokens.size();
    }

    void parser::Parser::parseCreateStatement()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_TABLE:
            this->parseTableStatement();
            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            break;
        }
    }

    void parser::Parser::parseTableStatement()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_IF:
            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_NOT:
                currentToken = this->getNextToken();

                switch (currentToken.getTokenType())
                {
                case token::TokenConstants::T_EXISTS:
                    currentToken = this->getNextToken();

                    this->table.setIfNotExists(true);

                    switch (currentToken.getTokenType())
                    {
                    case token::TokenConstants::T_IDENTIFIER:
                        this->table.setTableName(currentToken.getTokenValue());
                        this->parseTableBody();
                        break;
                    case token::TokenConstants::T_UNKNOWN:
                        ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                        break;
                    default:
                        ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "table_name");
                        break;
                    }

                    break;
                case token::TokenConstants::T_UNKNOWN:
                    ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                    break;
                default:
                    ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_EXISTS]);
                    break;
                }

                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_NOT]);
                break;
            }

            break;
        case token::TokenConstants::T_IDENTIFIER:
            this->table.setTableName(currentToken.getTokenValue());
            this->parseTableBody();
            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "[IF NOT EXISTS] table_name");
            break;
        }
    }

    void parser::Parser::parseTableBody()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_LPAREN:
            this->parseTableRows();
            this->goBackToPreviousToken();

            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_RPAREN:
                currentToken = this->getNextToken();

                switch (currentToken.getTokenType())
                {
                case token::TokenConstants::T_SEMICOLON:
                    return;
                case token::TokenConstants::T_UNKNOWN:
                    ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                    break;
                default:
                    ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_SEMICOLON]);
                    break;
                }

                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_RPAREN]);
                break;
            }

            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_LPAREN]);
            break;
        }
    }

    void parser::Parser::parseTableRows()
    {
        while (true)
        {
            token::LiteralToken currentToken = this->getNextToken();

            this->currentRowDefinition.defaultValues();

            std::string rowName;

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_IDENTIFIER:
                rowName = currentToken.getTokenValue();

                ParserValidator::validateRowNameDoesntExist(currentToken, this->splitTextContent[currentToken.getLineNumber()], this->table, rowName);

                currentToken = this->getNextToken();

                switch (currentToken.getTokenType())
                {
                case token::TokenConstants::T_INT:
                    this->currentRowDefinition.setDataType(token::tokenToString[token::TokenConstants::T_INT]);
                    this->parseIntegerToken();
                    break;
                case token::TokenConstants::T_INTEGER:
                    this->currentRowDefinition.setDataType(token::tokenToString[token::TokenConstants::T_INTEGER]);
                    this->parseIntegerToken();
                    break;
                case token::TokenConstants::T_VARCHAR:
                    this->currentRowDefinition.setDataType(token::tokenToString[token::TokenConstants::T_VARCHAR]);
                    this->parseVarcharToken();
                    break;
                case token::TokenConstants::T_UNKNOWN:
                    ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                    break;
                default:
                    ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "column_definition");
                    break;
                }

                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "column_name");
                break;
            }

            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_COMMA:
                this->table.addTableRow({rowName, this->currentRowDefinition});
                break;
            case token::TokenConstants::T_RPAREN:
                this->table.addTableRow({rowName, this->currentRowDefinition});
                return;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], ", or )");
                break;
            }
        }
    }

    void parser::Parser::parseIntegerToken()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_LPAREN:
            this->parseDataTypeSize();
            this->parseGenericColumnDefinitions();
            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default: // No optional parameters
            this->goBackToPreviousToken();
            this->parseGenericColumnDefinitions();
            break;
        }
    }

    void parser::Parser::parseVarcharToken()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_LPAREN:
            this->parseDataTypeSize();
            this->parseGenericColumnDefinitions();
            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "(max_column_length_in_characters)");
            break;
        }
    }

    void parser::Parser::parseDataTypeSize()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_INTCONST:
            this->currentRowDefinition.setSize(std::strtol(currentToken.getTokenValue().c_str(), nullptr, normalizer::DECIMAL_BASE));

            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_RPAREN:
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_LPAREN]);
                break;
            }

            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "INTEGER VALUE");
            break;
        }
    }

    void parser::Parser::parseGenericColumnDefinitions()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_RPAREN:
        case token::TokenConstants::T_COMMA:
            this->goBackToPreviousToken(); // Backtrack to last token as there are no optional tokens
            return;
        case token::TokenConstants::T_NOT:
            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_NULL:
                this->currentRowDefinition.setNullable(false);
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_NULL]);
                break;
            }

            break;
        case token::TokenConstants::T_NULL:
            this->currentRowDefinition.setNullable(true);
            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "[NOT NULL | NULL]");
            break;
        }
    }

    void parser::Parser::parseDependencies()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_DASH:
            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_RANGLE:
                this->parseMultiValuedDependencies();
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], ">[>]");
                break;
            }

            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "-");
            break;
        }
    }

    void parser::Parser::parseMultiValuedDependencies()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_RANGLE:
            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_IDENTIFIER:
                break;
            case token::TokenConstants::T_LPAREN: // Multiple dependent columns
                this->parseMultipleDependentColumns();
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "[(] or dependent_column");
                break;
            }

            break;
        case token::TokenConstants::T_IDENTIFIER: // If no multi value dependency
            break;
        case token::TokenConstants::T_LPAREN: // Multiple dependent columns
            this->parseMultipleDependentColumns();
            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "[>], [(], or dependent_column");
            break;
        }
    }

    void parser::Parser::parseMultipleDependentColumns()
    {
        while (true)
        {
            token::LiteralToken currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_IDENTIFIER:
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "dependent_column");
                break;
            }

            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_COMMA:
                break;
            case token::TokenConstants::T_RPAREN:
                return;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], ", or )");
                break;
            }
        }
    }

    void parser::Parser::parseKey()
    {
        token::LiteralToken currentToken = this->getNextToken();

        switch (currentToken.getTokenType())
        {
        case token::TokenConstants::T_COLON:
            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_IDENTIFIER:
                break;
            case token::TokenConstants::T_LPAREN:
                this->parseMultiplePrimaryKeys();
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "[(] or primary_key");
                break;
            }

            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], ":");
            break;
        }
    }

    void parser::Parser::parseMultiplePrimaryKeys()
    {
        while (true)
        {
            token::LiteralToken currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_IDENTIFIER:
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "primary_key");
                break;
            }

            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_COMMA:
                break;
            case token::TokenConstants::T_RPAREN:
                return;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], ", or )");
                break;
            }
        }
    }
} // Namespace normalizer::interpreter