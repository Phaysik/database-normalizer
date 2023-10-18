/*! \file constants.h
    \brief Header file for global constants.
    \date 10/02/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>

#include "aliases.h"

namespace normalizer
{
    namespace file
    {
        // For grabbing the user input files
        const std::string RESOURCES_FOLDER = "resources/";                                     /*!< The top level folder where all user input files will go in */
        const std::string SQL_DATASET_FOLDER = RESOURCES_FOLDER + "sql/";                      /*!< The folder where the sql dataset file(s) will go in */
        const std::string FUNCTIONAL_DEPENDENCIES_FOLDER = RESOURCES_FOLDER + "dependencies/"; /*!< The folder where the functional dependency file(s) will go in */

        // For file validation
        const std::string DIRECTORY_DOES_NOT_EXIST = "Directory does not exist"; /*!< Error message for if the user's directory path is not valid */
        const std::string FILE_DOES_NOT_EXIST = "File does not exist";           /*!< Error message for if the user's file path is not valid */
        const std::string FILE_DID_NOT_OPEN = "File did not open";               /*!< Error message for if the user's file does not open */
        const std::string READ_DIRECTORY_NOT_FILE = "File did not open";         /*!< Error message for if the user tries to read a directory not a file */
    }

    namespace interpreter::token
    {
        const bool TOKEN_DEBUG = false; /*!< Enable debugging for #normalizer::interpreter::token::Token */
    }

    namespace interpreter::lexer
    {
        const us DECIMAL_BASE = 10; /*!< The base of a standard decimal value */
    }
}