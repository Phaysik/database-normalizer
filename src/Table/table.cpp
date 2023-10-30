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

    std::vector<row::TableRow> &Table::getTableRows()
    {
        return this->tableRows;
    }

    bool Table::getIfNotExists() const
    {
        return this->ifNotExists;
    }

    std::vector<std::string> Table::getPrimaryKeys() const
    {
        return this->primaryKeys;
    }

    std::vector<foreign::ForeignKey> Table::getForeignKeys() const
    {
        return this->foreignKeys;
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

    void Table::addPrimaryKey(const std::string &primaryKey)
    {
        this->primaryKeys.push_back(primaryKey);
    }

    void Table::addForeignKey(const foreign::ForeignKey &foreignKey)
    {
        this->foreignKeys.push_back(foreignKey);
    }
}