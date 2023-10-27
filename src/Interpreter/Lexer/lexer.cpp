/*! \file lexer.cpp
    \brief C++ file for creating a lexer.
    \details Contains the function definitions for creating a lexer
    \date 10/12/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Interpreter/Lexer/lexer.h"

namespace normalizer::interpreter
{
    namespace lexer
    {

        /* Member Functions */

        char Lexer::nextChar()
        {
            char currentValue = 0;

            LexerValidator::validateTextContentInRange(this->textContent, this->characterIndex);

            currentValue = this->textContent[this->characterIndex++];

            if (currentValue == '\n' || currentValue == '\r')
            {
                bool isWindowsMachine = this->canGrabNewChar(); // Checks to see if the file ends in CRLF (Windows)

                if (currentValue == '\r' && isWindowsMachine && this->textContent[this->characterIndex] == '\n') // Checks for CR and then LF characters
                {
                    ++this->lineOffset;
                }
                else
                {
                    this->lineOffset = 0;
                    ++this->lineNumber;
                }
            }
            else
            {
                ++this->lineOffset;
            }

            return currentValue;
        }

        void Lexer::putBackChar()
        {
            LexerValidator::validateCharacterIndexAboveZero(this->characterIndex);

            char previousValue = this->textContent[--this->characterIndex];

            if (previousValue == '\n' || previousValue == '\r')
            {
                // Checks to see if there is a '\n' followin the previous value and will thus only decrement the line offset
                if (previousValue == '\r' && this->textContent[this->characterIndex + 1] == '\n')
                {
                    --this->lineOffset;
                }
                else
                {
                    --this->lineNumber;
                    this->lineOffset = 0;

                    sl beforePeviousValue = this->characterIndex - 1;

                    // Retreat to the end of the previous line
                    while (true)
                    {
                        if (beforePeviousValue >= 0 && !(this->textContent[static_cast<size_t>(beforePeviousValue)] == '\r' || this->textContent[static_cast<size_t>(beforePeviousValue)] == '\n'))
                        {
                            break;
                        }

                        ++this->lineOffset;
                        --beforePeviousValue;
                    }
                }
            }
            else
            {
                --this->lineOffset;
            }
        }

        void Lexer::eatWhitespace()
        {
            while (true)
            {
                LexerValidator::validateTextContentInRange(this->textContent, this->characterIndex);

                char whitespaceValue = this->nextChar();

                switch (whitespaceValue)
                {
                case '\n': // New line
                case '\t': // h-tab
                case '\f': // v-tab
                case '\r': // carriage return
                case ' ':
                    break;
                default:
                    this->putBackChar();
                    return;
                }
            }
        }

        bool lexer::Lexer::canGrabNewChar()
        {
            return this->characterIndex < this->textContent.length();
        }

        /* Static Functions */

        char Lexer::lowerCharacter(const char character)
        {
            return static_cast<char>(std::tolower(character));
        }
    } // Namespace lexer

    std::vector<token::LiteralToken> lexer::Lexer::grabAllTokens()
    {
        std::vector<token::LiteralToken> tokens;

        try
        {
            this->eatWhitespace();

            while (this->canGrabNewChar())
            {
                tokens.push_back(this->tokenize());

                if (this->canGrabNewChar())
                {
                    this->eatWhitespace();
                }
            }

            return tokens;
        }
        catch (const std::out_of_range &error)
        {
            throw error;
        }
    }

    token::LiteralToken lexer::Lexer::tokenize()
    {
        while (true)
        {
            char currentValue = Lexer::lowerCharacter(this->nextChar());

            switch (currentValue)
            {
            case '(':
                return {currentValue, token::TokenConstants::T_LPAREN, this->lineNumber, this->lineOffset, 1};
            case ')':
                return {currentValue, token::TokenConstants::T_RPAREN, this->lineNumber, this->lineOffset, 1};
            case ';':
                return {currentValue, token::TokenConstants::T_SEMICOLON, this->lineNumber, this->lineOffset, 1};
            case ':':
                return {currentValue, token::TokenConstants::T_COLON, this->lineNumber, this->lineOffset, 1};
            case ',':
                return {currentValue, token::TokenConstants::T_COMMA, this->lineNumber, this->lineOffset, 1};
            case '-':
                return {currentValue, token::TokenConstants::T_DASH, this->lineNumber, this->lineOffset, 1};
            case '>':
                return {currentValue, token::TokenConstants::T_RANGLE, this->lineNumber, this->lineOffset, 1};
            case 'a': // ASCII latin a-z and _
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case '_':
                this->putBackChar();
                return this->eatIdentifierOrKeyword();
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                this->putBackChar();
                return this->eatNumericLiteral();
            default:
                return {currentValue, token::TokenConstants::T_UNKNOWN, this->lineNumber, this->lineOffset, 1};
            }
        }
    }

    token::LiteralToken lexer::Lexer::eatIdentifierOrKeyword()
    {
        std::string trueValue;
        char trueCharacter = this->nextChar();
        char lowerCharacter = Lexer::lowerCharacter(trueCharacter);

        std::regex alphaRegex("[a-z_]");

        bool regexFailed = false;

        while (true)
        {
            if (!(std::regex_match(std::string(1, lowerCharacter), alphaRegex)))
            {
                regexFailed = true;
                break;
            }

            trueValue += trueCharacter;

            if (this->canGrabNewChar())
            {
                trueCharacter = this->nextChar();
                lowerCharacter = Lexer::lowerCharacter(trueCharacter);
            }
            else
            {
                break;
            }
        }

        if (this->canGrabNewChar() || regexFailed)
        {
            this->putBackChar(); // To remove the last grabbed character that was not a-z
        }

        std::string casedValue = trueValue;

        for (char &character : casedValue)
        {
            character = static_cast<char>(std::toupper(character));
        }

        // If the string value is a keyword return that token
        if (token::stringToToken.find(casedValue) != token::stringToToken.end())
        {
            return {trueValue, token::stringToToken[casedValue], this->lineNumber, this->lineOffset, static_cast<us>(trueValue.length())};
        }

        return {trueValue, token::TokenConstants::T_IDENTIFIER, this->lineNumber, this->lineOffset, static_cast<us>(trueValue.length())};
    }

    token::LiteralToken lexer::Lexer::eatNumericLiteral()
    {
        std::string trueValue;
        char trueCharacter = this->nextChar();

        std::regex numberRegex("[0-9]");

        bool regexFailed = false;

        while (true)
        {
            if (!(std::regex_match(std::string(1, trueCharacter), numberRegex)))
            {
                regexFailed = true;
                break;
            }

            trueValue += trueCharacter;

            if (this->canGrabNewChar())
            {
                trueCharacter = this->nextChar();
            }
            else
            {
                break;
            }
        }

        if (this->canGrabNewChar() || regexFailed)
        {
            this->putBackChar(); // To remove the last grabbed character that was not 0-9
        }

        ul parsedValue = std::strtoul(trueValue.c_str(), nullptr, normalizer::DECIMAL_BASE); // Convert it to an unsigned long

        return {parsedValue, this->lineNumber, this->lineOffset, static_cast<us>(trueValue.length())};
    }
} // Namespace normalizer::interpreter