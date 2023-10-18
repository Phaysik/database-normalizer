/*! \file lexerValidator.h
    \brief Header file for creating a validator for lexical analysis.
    \details Contains the function declarations for creating a validator for lexical analysis
    \date 10/16/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <system_error>

#include "aliases.h"

namespace normalizer::interpreter::lexer
{
    /*! \headerfile lexerValidator.h
        \brief Validates lexical analysis
        \details Determines whether certain calls in the lexer are valid
        \date 10/16/2023
        \version 1.0
        \author Matthew Moore
    */
    class LexerValidator
    {
    public:
        /* Static Functions */

        /*! \brief Determines if the \p lineNumber is in range of \p textContent
            \post The program may throw an error depending on it \p lineNumber is in range of \p textContent
            \param[in] textContent The text content to check the range of
            \param[in] characterIndex The index to validate
            \date 10/16/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateTextContentInRange(const std::string &textContent, const us characterIndex);

        /*! \brief Determines if \p characterIndex is greater than 0
            \post The program may throw an error depending on if \p characterIndex is less than or equal to 0
            \param[in] characterIndex The index to verfiy
            \date 10/17/2023
            \version 1.0
            \author Matthew Moore
        */
        static void validateCharacterIndexAboveZero(const us characterIndex);
    };
}