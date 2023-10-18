/*! \file fileManager.h
    \brief Header file for creating a file/directory manager.
    \details Contains the function declarations for creating a file/directory manager.
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "fileValidator.h"

namespace normalizer::file
{
    /*! \headerfile fileManager.h
        \brief A class to manage directories and files
        \details Parses and processes information from files
        \date 10/11/2023
        \version 1.0
        \author Matthew Moore
    */
    class FileManager
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Create a #FileManager instance
            \details Creates a #FileManager instance with either a file or directory passed in
            \post The \p path passed will be verified as a valid file path or directory path
            \param[in] path The path to verify
            \param[in] isDirectory Whether the path parameter is a directory path
            \date 10/04/2023
            \version 1.0
            \author Matthew Moore
        */
        FileManager(const std::string &path, const bool isDirectory = false);

        /* Getters and Setters */

        /*! \brief Get the file or directory path
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return std::string the file or directory path
        */
        std::string getFOrdPath() const;

        /*! \brief Get if the path is a directory path
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return bool If the path is a directory path
        */
        bool getIsPathADirectory() const;

        /* Member Functions */

        /*! \brief Grab all text in a given file
            \post A file will be opened and read from
            \param[in] directoryCalling If being called from a directory file grabber
            \param[in] filePath If the function is being called by #grabDirectoryFileContents
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The file contents
        */
        std::string grabFileContents(const bool directoryCalling = false, const std::string &filePath = "") const;

        /*! \brief Grab all text in all files in a given directory
            \post The directory will be iterated through and all files read and their contents grabbed
            \date 10/11/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The list of all file contents
        */
        std::vector<std::string> grabDirectoryFileContents() const;

    private:
        std::string fOrdPath;  /*!< The path of the file or directory being managed */
        bool isPathADirectory; /*!< If #fOrdPath is a directory path or file path */
    };
}