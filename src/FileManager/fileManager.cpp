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

/* Getters and Setters */

std::string normalizer::file::FileManager::getFOrdPath() const
{
    return this->fOrdPath;
}

bool normalizer::file::FileManager::getIsPathADirectory() const
{
    return this->isPathADirectory;
}

/* Member Functions */

std::string normalizer::file::FileManager::grabFileContents(const bool directoryCalling, const std::string &filePath) const
{
    const std::string fileToRead = (filePath != "") ? filePath : this->fOrdPath;

    normalizer::file::FileValidator::validateReadFileOrCallFromDirectory(directoryCalling, this->isPathADirectory, fileToRead);

    std::ifstream inputFile(fileToRead);

    normalizer::file::FileValidator::validateFileOpen(inputFile, fileToRead);

    std::string fileContents = "";

    std::string line = "";

    while (std::getline(inputFile, line))
    {
        fileContents += line;
        fileContents += "\n";
    }

    inputFile.close();

    // Substring the final '\n' off
    return fileContents.substr(0, fileContents.length() - 1);
}

std::vector<std::string> normalizer::file::FileManager::grabDirectoryFileContents() const
{
    normalizer::file::FileValidator::validateDirectoryPath(this->fOrdPath);

    std::vector<std::string> directoryFileContents;

    for (const auto &entry : std::filesystem::directory_iterator(this->fOrdPath))
    {
        normalizer::file::FileValidator::validateFilePath(entry.path());

        const std::string intermediateFileContents = this->grabFileContents(true, entry.path());

        directoryFileContents.push_back(intermediateFileContents);
    }

    return directoryFileContents;
}