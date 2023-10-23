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

    /* Member Functions */

    void parser::Parser::parse()
    {
        while (this->hasMoreTokens())
        {
            token::LiteralToken currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_CREATE:
                this->parseCreateStatement();
                break;
            default:
                // Don't need to specify T_UNKNOWN as a case here as default will catch it
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            }

            break;
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

                    switch (currentToken.getTokenType())
                    {
                    case token::TokenConstants::T_IDENTIFIER:
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

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_IDENTIFIER:
                currentToken = this->getNextToken();

                switch (currentToken.getTokenType())
                {
                case token::TokenConstants::T_INTEGER:
                    this->parseIntegerToken();
                    break;
                case token::TokenConstants::T_VARCHAR:
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
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "[(min_display_width)]");
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
        case token::TokenConstants::T_COMMA:
            this->goBackToPreviousToken(); // Backtrack to last token as there are no optional tokens
            return;
        case token::TokenConstants::T_NOT:
            currentToken = this->getNextToken();

            switch (currentToken.getTokenType())
            {
            case token::TokenConstants::T_NULL:
                break;
            case token::TokenConstants::T_UNKNOWN:
                ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
                break;
            default:
                ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], token::tokenToString[token::TokenConstants::T_NULL]);
                break;
            }

            break;
        case token::TokenConstants::T_UNKNOWN:
            ParserValidator::throwUknownToken(currentToken, this->splitTextContent[currentToken.getLineNumber()]);
            break;
        default:
            ParserValidator::throwUnexpectedToken(currentToken, this->splitTextContent[currentToken.getLineNumber()], "[NOT NULL]");
            break;
        }
    }

} // Namespace normalizer::interpreter