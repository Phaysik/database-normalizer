/*! \file fileManager.h
    \brief Header file for creating a file/directory manager.
    \details Contains the function declarations for creating a file/directory manager.
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

#include "fileValidator.h"

namespace normalizer
{
    namespace file
    {
        /*! \headerfile fileManager.h
            \brief A class to manage directories and files
            \details Parses and processes information from files
            \date 10/04/2023
            \version 1.0
            \author Matthew Moore
        */
        class FileManager
        {
        public:
            /* Constructors and Destructors */

            /*! \brief Create a FileManager instance
                \details Creates a FileManager instance with either a file or directory passed in
                \post The path passed will be verified as a valid file path or directory path
                \param[in] path The path to verify
                \param[in] isDirectory Whether the path parameter is a directory path
                \date 10/04/2023
                \version 1.0
                \author Matthew Moore
            */
            FileManager(const std::string &path, const bool isDirectory = false);

        private:
            std::string fileDirectory; /*!< The directory that contains the user input files */
            std::string fOrdPath;      /*!< The path of the file or directory being managed */
            bool isPathADirectory;     /*!< If #fOrdPath is a directory path or file path */
        };
    }
}
