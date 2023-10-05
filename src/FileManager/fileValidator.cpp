/*! \file fileValidator.cpp
    \brief C++ file for creating a validator for file information.
    \details Contains the function definitions for creating a validator for file information
    \date 10/03/2023
    \version 1.0
    \author Matthew Moore
*/

#include "FileManager/fileValidator.h"

/* Static Functions */

void normalizer::file::FileValidator::validateDirectoryPath(const std::string &directoryPath)
{
    if (!std::filesystem::is_directory(directoryPath))
    {
        throw std::filesystem::filesystem_error(normalizer::file::DIRECTORY_DOES_NOT_EXIST, directoryPath, std::make_error_code(std::errc::no_such_file_or_directory));
    }
}

void normalizer::file::FileValidator::validateFilePath(const std::string &filePath)
{
    std::filesystem::file_status status = std::filesystem::status(filePath);

    if (!std::filesystem::is_regular_file(status))
    {
        throw std::filesystem::filesystem_error(normalizer::file::FILE_DOES_NOT_EXIST, filePath, std::make_error_code(std::errc::no_such_file_or_directory));
    }
}