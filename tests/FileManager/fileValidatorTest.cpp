/*! \file fileValidatorTest.cpp
    \brief C++ file for creating tests for file validation.
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#include <string>
#include <filesystem>
#include <fstream>
#include <cstdio>

#include "gtest/gtest.h"
#include "FileManager/fileValidator.h"
#include "FileManager/fileValidatorFixture.h"
#include "constants.h"

TEST(FileValidator, DirectoryErrorThrown)
{
    const std::string erroneousDirectoryPath = "resources/spl";

    // Should throw an filesystem error
    EXPECT_THROW({
        try
        {
            normalizer::file::FileValidator::validateDirectoryPath(erroneousDirectoryPath);
        }
        catch (const std::filesystem::filesystem_error &error)
        {
            // Check if the DIRECTORY_DOES_NOT_EXIST string is a substring of the error message
            EXPECT_PRED_FORMAT2(::testing::IsSubstring, normalizer::file::DIRECTORY_DOES_NOT_EXIST, error.what());
            throw;
        }
    },
                 std::filesystem::filesystem_error);
}

TEST(FileValidator, SQLDatasetFolder)
{
    const std::string sqlDatasetFolder = normalizer::file::SQL_DATASET_FOLDER;

    EXPECT_NO_THROW(normalizer::file::FileValidator::validateDirectoryPath(sqlDatasetFolder));
}

TEST(FileValidator, FunctionalDependenciesFolder)
{
    const std::string funcDepenFolder = normalizer::file::FUNCTIONAL_DEPENDENCIES_FOLDER;

    EXPECT_NO_THROW(normalizer::file::FileValidator::validateDirectoryPath(funcDepenFolder));
}

TEST(FileValidator, FileErrorThrown)
{
    const std::string erroneousFilePath = "resources/sql/dataset.sql";

    // Should throw an filesystem error
    EXPECT_THROW({
        try
        {
            normalizer::file::FileValidator::validateFilePath(erroneousFilePath);
        }
        catch (const std::filesystem::filesystem_error &error)
        {
            // Check if the FILE_DOES_NOT_EXIST string is a substring of the error message
            EXPECT_PRED_FORMAT2(::testing::IsSubstring, normalizer::file::FILE_DOES_NOT_EXIST, error.what());
            throw;
        }
    },
                 std::filesystem::filesystem_error);
}

TEST_F(FileValidatorTest, SQLDatasetFile)
{
    std::ofstream outputFile(*dummySqlDatasetFilePath);

    ASSERT_TRUE(outputFile.is_open());

    outputFile.close();

    EXPECT_NO_THROW(normalizer::file::FileValidator::validateFilePath(*dummySqlDatasetFilePath));
}

TEST_F(FileValidatorTest, FunctionalDependenciesFile)
{
    std::ofstream outputFile(*dummyFunctionalDependenciesFilePath);

    ASSERT_TRUE(outputFile.is_open());

    outputFile.close();

    EXPECT_NO_THROW(normalizer::file::FileValidator::validateFilePath(*dummyFunctionalDependenciesFilePath));
}