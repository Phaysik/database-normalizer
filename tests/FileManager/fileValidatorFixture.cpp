/*! \file fileValidatorFixture.cpp
    \brief C++ file for creating a file validator fixture.
    \details Contains the function definitions for creating a file validator fixture
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#include "FileManager/fileValidatorFixture.h"

std::string *FileValidatorTest::dummySqlDatasetFilePath = nullptr;
std::string *FileValidatorTest::dummyFunctionalDependenciesFilePath = nullptr;

/* Set up and tear down */

void FileValidatorTest::SetUpTestSuite()
{
    dummySqlDatasetFilePath = new std::string(normalizer::file::SQL_DATASET_FOLDER + "sqlDataset.sql");
    dummyFunctionalDependenciesFilePath = new std::string(normalizer::file::SQL_DATASET_FOLDER + "functionalDependencies.txt");
}

void FileValidatorTest::TearDownTestSuite()
{
    std::remove(dummySqlDatasetFilePath->c_str());
    std::remove(dummyFunctionalDependenciesFilePath->c_str());

    delete dummyFunctionalDependenciesFilePath;
    delete dummySqlDatasetFilePath;

    dummyFunctionalDependenciesFilePath = nullptr;
    dummySqlDatasetFilePath = nullptr;
}