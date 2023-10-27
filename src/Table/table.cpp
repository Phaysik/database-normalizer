/*! \file table.cpp
    \brief C++ file for creating a table.
    \details Contains the function definitions for creating a table
    \date 10/26/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Table/table.h"

namespace normalizer::table
{
    /* Getters and Setters */

    std::string Table::getTableName() const
    {
        return this->tableName;
    }

    std::vector<row::TableRow> Table::getTableRows() const
    {
        return this->tableRows;
    }

    bool Table::getIfNotExists() const
    {
        return this->ifNotExists;
    }

    void Table::setTableName(const std::string &name)
    {
        this->tableName = name;
    }

    void Table::setIfNotExists(const bool &exists)
    {
        this->ifNotExists = exists;
    }

    /* Member Functions */

    void Table::addTableRow(const row::TableRow &row)
    {
        this->tableRows.push_back(row);
    }
}