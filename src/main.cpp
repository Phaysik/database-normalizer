/*! \file main.cpp
    \brief C++ file for creating the entry point for the database-normalizer program.
    \details Contains the function definitions for creating the entry point for the database-normalizer program
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#include <iostream>
#include <string>
#include <vector>

#include "FileManager/fileManager.h"
#include "Interpreter/Token/token.h"
#include "Interpreter/Token/literalToken.h"
#include "Interpreter/Token/tokenConstants.h"
#include "Interpreter/Lexer/lexer.h"
#include "Interpreter/Parser/parser.h"
#include "Table/table.h"
#include "constants.h"

/*! \brief The entry point for the program
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
    \return int The status code of the program
*/
int main()
{
    normalizer::file::FileManager sqlManager(normalizer::file::SQL_DATASET_FOLDER + "dataset.sql", false);

    std::string sqlContents = sqlManager.grabFileContents();

    normalizer::file::FileManager dependencyManager(normalizer::file::FUNCTIONAL_DEPENDENCIES_FOLDER + "dependencies.txt", false);

    std::string dependencyContents = dependencyManager.grabFileContents();

    normalizer::interpreter::parser::Parser sqlParser(sqlContents);

    sqlParser.parse();

    normalizer::table::Table sqlTable = sqlParser.getTable();

    std::cout << sqlTable.getTableName() << " " << sqlTable.getIfNotExists() << std::endl;

    std::vector<normalizer::table::row::TableRow> sqlRows = sqlTable.getTableRows();

    for (const normalizer::table::row::TableRow &row : sqlRows)
    {
        normalizer::table::row::GenericRowDefinition rowDefinition = row.getRowDefinition();
        std::cout << "RowName: " << row.getRowName() << " DataType: " << rowDefinition.getDataType() << " Nullable: " << rowDefinition.getNullable() << " DataSize: " << rowDefinition.getSize() << std::endl;
    }

    // for (const normalizer::interpreter::token::LiteralToken &newToken : sqlTokens)
    // {
    //     std::cout << newToken << std::endl;
    //     // std::cout << newToken.getLineNumber() << " " << newToken.getLineOffset() << " " << newToken.getTokenLength() << std::endl;
    // }

    normalizer::interpreter::parser::Parser dependencyParser(dependencyContents);

    dependencyParser.parse();

    // for (const normalizer::interpreter::token::LiteralToken &newToken : dependencyTokens)
    // {
    //     std::cout << newToken << std::endl;
    //     // std::cout << newToken.getLineNumber() << " " << newToken.getLineOffset() << " " << newToken.getTokenLength() << std::endl;
    // }

    return 0;
}