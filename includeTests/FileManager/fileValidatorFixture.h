/*! \file fileValidatorFixture.h
    \brief Header file for creating a test fixture for file validation.
    \details Contains the function declarations for creating the file validation fixture
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <cstdio>

#include "gtest/gtest.h"
#include "constants.h"

/*! \headerfile fileValidatorFixture.h
    \brief A test fixture for #normalizer::file::FileValidator
    \details Creates a test fixture to be used in some #normalizer::file::FileValidator tests
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/
class FileValidatorTest : public ::testing::Test
{
protected:
    /*! \brief Runs before the first test in a test suite
        \details Initializes #dummySqlDatasetFilePath and #dummyFunctionalDependenciesFilePath before any tests in the test suite are run
        \post #dummySqlDatasetFilePath and #dummyFunctionalDependenciesFilePath are initialized on the heap
        \date 10/04/2023
        \version 1.0
        \author Matthew Moore
    */
    static void SetUpTestSuite();

    /*! \brief Runs after the last test in a test suite
        \details De-allocate the memory of #dummySqlDatasetFilePath and #dummyFunctionalDependenciesFilePath
        \post Both #dummySqlDatasetFilePath and #dummyFunctionalDependenciesFilePath will be de-allocated and set to a nullptr
        \date 10/04/2023
        \version 1.0
        \author Matthew Moore
    */
    static void TearDownTestSuite();

    static std::string *dummySqlDatasetFilePath;             /*!< The dummy sql data path to create a file to */
    static std::string *dummyFunctionalDependenciesFilePath; /*!< The dummy funtional dependencies path to create a file to */
};