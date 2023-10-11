/*! \file fileValidator.h
    \brief Header file for creating a validator for file information.
    \details Contains the function declarations for creating a validator for file information
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <iostream>
#include <fstream>
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
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
        */
        class FileValidator
        {
        public:
            /* Static Functions */

            /*! \brief Determines is the \p directoryPath parameter is a valid directory
                \post The program may throw an error if the \p directoryPath parameter is not a valid directory path
                \param[in] directoryPath The directory path to validate
                \date 10/04/2023
                \version 1.0
                \author Matthew Moore
            */
            static void validateDirectoryPath(const std::string &directoryPath);

            /*! \brief Determines is the \p filePath parameter is a valid directory
                \post The program may throw an error if the \p filePath parameter is not a valid file path
                \param[in] filePath The file path to validate
                \date 10/04/2023
                \version 1.0
                \author Matthew Moore
            */
            static void validateFilePath(const std::string &filePath);

            /*! \brief Determines if the \p file is open
                \pre The parameter \p file must already be created an initialized with the parameter \p fileName
                \post The program may throw an error if the \p file parameter is not open
                \param[in] file The file to determine if it is open
                \param[in] fileName The name of the file being opened
                \date 10/11/2023
                \version 1.0
                \author Matthew Moore
            */
            static void validateFileOpen(const std::ifstream &file, const std::string &fileName);

            /*! \brief Validates calls to #normalizer::file::FileManager::grabFileContents
                \details Checks to see if the function is called with just a single file or is being called by a directory file grabber.
                \post The program may throw an error is the \p directoryCalling parameter is false and the \p isPathADirectory parameter is true
                \param[in] directoryCalling If the function is called from a directory file grabber
                \param[in] isPathADirectory If #normalizer::file::FileManager::FileManager was created with directory access in mind
                \param[in] pathName The path of the file/directory trying to be read from.
                \date 10/11/2023
                \version 1.0
                \author Matthew Moore
            */
            static void validateReadFileOrCallFromDirectory(const bool directoryCalling, const bool isPathADirectory, const std::string &pathName);
        };
    }
}