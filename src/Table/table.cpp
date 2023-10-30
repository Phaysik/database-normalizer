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

    void Table::removeTableRow(const row::TableRow &row)
    {
        auto it = std::find(this->tableRows.begin(), this->tableRows.end(), row);

        if (it != this->tableRows.end())
        {
            this->tableRows.erase(it);
        }
    }

    void Table::addPrimaryKey(const std::string &primaryKey)
    {
        this->primaryKeys.push_back(primaryKey);
    }

    void Table::removePrimaryKey(const std::string &primaryKey)
    {
        auto it = std::find(this->primaryKeys.begin(), this->primaryKeys.end(), primaryKey);

        if (it != this->primaryKeys.end())
        {
            this->primaryKeys.erase(it);
        }
    }

    void Table::addForeignKey(const foreign::ForeignKey &foreignKey)
    {
        this->foreignKeys.push_back(foreignKey);
    }

    /* Operator Overload */

    bool Table::operator==(const Table &other) const
    {
        if (this->foreignKeys.size() != other.foreignKeys.size())
        {
            return false;
        }

        if (this->primaryKeys.size() != other.primaryKeys.size())
        {
            return false;
        }

        if (this->tableRows.size() != other.tableRows.size())
        {
            return false;
        }

        if (this->tableName != other.tableName || (this->ifNotExists != other.ifNotExists))
        {
            return false;
        }

        for (us i = 0; i < this->foreignKeys.size(); ++i)
        {
            if (this->foreignKeys[i] != other.foreignKeys[i])
            {
                return false;
            }
        }

        for (us i = 0; i < this->primaryKeys.size(); ++i)
        {
            if (this->primaryKeys[i] != other.primaryKeys[i])
            {
                return false;
            }
        }

        for (us i = 0; i < this->tableRows.size(); ++i)
        {
            if (this->tableRows[i] != other.tableRows[i])
            {
                return false;
            }
        }

        return true;
    }
}