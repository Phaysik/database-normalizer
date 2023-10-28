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

    Normalizer::Normalizer(const us normalizeForm, const std::string &sqlFilePath, const std::string &dependencyFilePath) : normalizeTo(normalizeForm), hasPrimaryKey(true), hasNullableRows(false)
    {
        file::FileManager sqlManager(sqlFilePath, false);

        std::string sqlContents = sqlManager.grabFileContents();

        file::FileManager dependencyManager(dependencyFilePath, false);

        std::string dependencyContents = dependencyManager.grabFileContents();

        interpreter::parser::Parser sqlParser(sqlContents);

        sqlParser.parse();

        this->table = sqlParser.getTable();

        // std::cout << this->table.getPrimaryKeys().size() << " " << sqlParser.getTable().getPrimaryKeys().size() << std::endl;

        interpreter::parser::Parser dependencyParser(dependencyContents, this->table);

        dependencyParser.parse();

        this->dependencies = dependencyParser.getDependencyManager();

        for (const std::string &key : dependencyParser.getTable().getPrimaryKeys())
        {
            this->table.addPrimaryKey(key);
        }
    }

    /* Member Functions */

    void Normalizer::normalize()
    {
        switch (this->normalizeTo)
        {
        case 1:
            this->normalizeToOneNF();
            std::cout << this->toOneNFString() << std::endl;
            break;
        default:
            break;
        }
    }

    bool Normalizer::determineInOneNF()
    {
        bool returnValue = true;

        if (this->table.getPrimaryKeys().size() == 0) // If primary key not set
        {
            this->hasPrimaryKey = false;
            returnValue = false;
        }

        for (table::row::TableRow &row : this->table.getTableRows())
        {
            if (row.getRowDefinition().getNullable()) // If one of the columns is nullable
            {
                this->hasNullableRows = true;
                returnValue = false;
            }
        }

        return returnValue;
    }

    void Normalizer::normalizeToOneNF()
    {
        if (this->determineInOneNF()) // If it's already in 1NF return
        {
            return;
        }

        if (!this->hasPrimaryKey)
        {
            // std::cout << "No primary key set." << std::endl;
            std::vector<std::string> nonDependentRows = this->getNonDependentRows();

            if (nonDependentRows.size() == 0)
            { // If there are no non-dependent rows, then every row becomes the primary key
                // std::cout << "No non-dependent rows. All rows to primary key" << std::endl;

                for (const table::row::TableRow &row : this->table.getTableRows())
                {
                    this->table.addPrimaryKey(row.getRowName());
                }
            }
            else
            {
                // std::cout << "Non dependent rows are: " << std::endl;
                for (const std::string &rowName : nonDependentRows)
                {
                    // std::cout << "\tRow name: " << rowName << std::endl;

                    this->table.addPrimaryKey(rowName);
                }
            }
        }

        if (this->hasNullableRows)
        {
            // std::cout << "Nullable rows exist" << std::endl;
            for (table::row::TableRow &row : this->table.getTableRows())
            {
                row.getRowDefinition().setNullable(false);
            }
        }
    }

    std::string Normalizer::toOneNFString()
    {
        std::string returnValue = "CREATE TABLE";

        if (this->table.getIfNotExists())
        {
            returnValue += " IF NOT EXISTS";
        }

        returnValue += " " + this->table.getTableName() + "(\n";
        returnValue += this->getTableRowString(this->table);
        returnValue += this->getTableRowPrimaryKeyString(this->table);
        returnValue += ");\n";

        return returnValue;
    }

    std::string Normalizer::getTableRowString(table::Table &inTable)
    {
        std::string returnValue = "";

        for (table::row::TableRow &row : inTable.getTableRows())
        {
            table::row::GenericRowDefinition &rowDefinition = row.getRowDefinition();

            returnValue += "\t" + row.getRowName() + " " + rowDefinition.getDataType();

            if (rowDefinition.getSize() != -1)
            {
                returnValue += "(" + std::to_string(rowDefinition.getSize()) + ")";
            }

            returnValue += (rowDefinition.getNullable() ? " NULL" : " NOT NULL");
            returnValue += ",\n";
        }

        return returnValue;
    }

    std::string Normalizer::getTableRowPrimaryKeyString(table::Table &inTable)
    {
        std::string returnValue = "\tPRIMARY KEY(";

        for (const std::string &key : inTable.getPrimaryKeys())
        {
            returnValue += key + ", ";
        }

        returnValue = returnValue.substr(0, returnValue.length() - 2);
        returnValue += ")\n";

        return returnValue;
    }

    std::vector<std::string> Normalizer::getNonDependentRows()
    {
        std::vector<std::string> nonDependentRows;

        std::vector<dependencies::row::DependencyRow> rows = this->dependencies.getDependencyRows();

        const us DEPENDENCY_ROW_SIZE = static_cast<us>(rows.size());

        for (us i = 0; i < DEPENDENCY_ROW_SIZE; ++i)
        {
            bool isDependentOnRow = false;

            for (us j = 0; j < DEPENDENCY_ROW_SIZE; ++j) // Loop through the rest of the rows
            {
                for (const std::string &singleValued : rows[j].getSingleDependencies())
                { // Loop through the single valued dependencies and check if dependent on the jth row
                    if (singleValued == rows[i].getRowName())
                    {
                        isDependentOnRow = true;
                        break;
                    }
                }

                for (const std::string &multiValued : rows[j].getMultiDependencies())
                { // Loop through the multi valued dependencies and check if dependent on the jth row
                    if (multiValued == rows[i].getRowName())
                    {
                        isDependentOnRow = true;
                        break;
                    }
                }
            }

            if (!isDependentOnRow) // If not dependent, add it to the unique rows
            {
                nonDependentRows.push_back(rows[i].getRowName());
            }
        }

        return nonDependentRows;
    }
}