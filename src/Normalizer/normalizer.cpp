/*! \file normalizer.cpp
    \brief C++ file for creating a normalizer.
    \details Contains the function definitions for creating a normalizer
    \date 10/27/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Normalizer/normalizer.h"

namespace normalizer
{
    /* Constructors and Destructors */

    Normalizer::Normalizer(const us normalizeForm, const std::string &sqlFilePath, const std::string &dependencyFilePath) : normalizeTo(normalizeForm)
    {
        file::FileManager sqlManager(sqlFilePath, false);

        std::string sqlContents = sqlManager.grabFileContents();

        file::FileManager dependencyManager(dependencyFilePath, false);

        std::string dependencyContents = dependencyManager.grabFileContents();

        interpreter::parser::Parser sqlParser(sqlContents);

        sqlParser.parse();

        this->table = sqlParser.getTable();

        interpreter::parser::Parser dependencyParser(dependencyContents, this->table);

        dependencyParser.parse();

        this->dependencies = dependencyParser.getDependencyManager();
    }
}