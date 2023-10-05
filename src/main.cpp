/*! \file main.cpp
    \brief C++ file for creating the entry point for the database-normalizer program.
    \details Contains the function definitions for creating the entry point for the database-normalizer program
    \date 10/02/2023
    \version 1.0
    \author Matthew Moore
*/

#include "FileManager/fileManager.h"
#include "constants.h"

int main()
{
    normalizer::file::FileManager fileManager(normalizer::file::SQL_DATASET_FOLDER, true);

    return 0;
}