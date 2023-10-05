/*! \file fileManager.cpp
    \brief C++ file for creating a file/directory manager.
    \details Contains the function definitions for creating a file/directory manager
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#include "FileManager/fileManager.h"

/* Constructors and Destructors */

normalizer::file::FileManager::FileManager(const std::string &path, const bool isDirectory)
{
    if (isDirectory)
    {
        normalizer::file::FileValidator::validateDirectoryPath(path);
    }
    else
    {
        normalizer::file::FileValidator::validateFilePath(path);
    }

    this->fOrdPath = path;
    this->isPathADirectory = isDirectory;
}