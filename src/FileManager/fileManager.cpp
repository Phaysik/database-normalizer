/*! \file fileManager.cpp
    \brief C++ file for creating a file/directory manager.
    \details Contains the function definitions for creating a file/directory manager
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#include "FileManager/fileManager.h"

namespace normalizer::file
{
    /* Constructors and Destructors */

    FileManager::FileManager(const std::string &path, const bool isDirectory)
    {
        if (isDirectory)
        {
            FileValidator::validateDirectoryPath(path);
        }
        else
        {
            FileValidator::validateFilePath(path);
        }

        this->fOrdPath = path;
        this->isPathADirectory = isDirectory;
    }

    /* Getters and Setters */

    std::string FileManager::getFOrdPath() const
    {
        return this->fOrdPath;
    }

    bool FileManager::getIsPathADirectory() const
    {
        return this->isPathADirectory;
    }

    /* Member Functions */

    std::string FileManager::grabFileContents(const bool directoryCalling, const std::string &filePath) const
    {
        const std::string fileToRead = !filePath.empty() ? filePath : this->fOrdPath;

        FileValidator::validateReadFileOrCallFromDirectory(directoryCalling, this->isPathADirectory, fileToRead);

        std::ifstream inputFile(fileToRead);

        FileValidator::validateFileOpen(inputFile, fileToRead);

        std::string fileContents;

        std::string line;

        while (true)
        {
            if (!std::getline(inputFile, line))
            {
                break;
            }

            fileContents += line;
            fileContents += "\n";
        }

        inputFile.close();

        // Substring the final '\n' off
        return fileContents.substr(0, fileContents.length() - 1);
    }

    std::vector<std::string> FileManager::grabDirectoryFileContents() const
    {
        FileValidator::validateDirectoryPath(this->fOrdPath);

        std::vector<std::string> directoryFileContents;

        for (const auto &entry : std::filesystem::directory_iterator(this->fOrdPath))
        {
            FileValidator::validateFilePath(entry.path());

            const std::string intermediateFileContents = this->grabFileContents(true, entry.path());

            directoryFileContents.push_back(intermediateFileContents);
        }

        return directoryFileContents;
    }
} // Namespace normalizer::file
