/*! \file fileValidator.h
    \brief Header file for creating a validator for file information.
    \details Contains the function declarations for creating a validator for file information
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <system_error>

#include "constants.h"

namespace normalizer
{
    namespace file
    {
        /*! \headerfile fileValidator.h
            \brief Validates file information
            \details Parses file paths or file input to determine if it is valid
            \date 10/04/2023
            \version 1.0
            \author Matthew Moore
        */
        class FileValidator
        {
        public:
            /* Static Functions */

            /*! \brief Determines is the directoryPath parameter is a valid directory
                \post The program may throw an error if the directoryPath parameter is not a valid directory path
                \param[in] directoryPath The directory path to validate
                \date 10/04/2023
                \version 1.0
                \author Matthew Moore
            */
            static void validateDirectoryPath(const std::string &directoryPath);

            /*! \brief Determines is the filePath parameter is a valid directory
                \post The program may throw an error if the filePath parameter is not a valid file path
                \param[in] filePath The file path to validate
                \date 10/04/2023
                \version 1.0
                \author Matthew Moore
            */
            static void validateFilePath(const std::string &filePath);
        };
    }
}