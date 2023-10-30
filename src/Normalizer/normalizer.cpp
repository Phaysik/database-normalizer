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

    /* Getters and Setters */

    std::vector<table::Table> &Normalizer::getNormalizedTables()
    {
        return this->normalizedTables;
    }

    /* Member Functions */

    void Normalizer::normalize()
    {
        switch (this->normalizeTo)
        {
        case 1:
            this->normalizeToOneNF();
            this->normalizedTables.push_back(this->table);
            break;
        case 2:
            this->normalizeToTwoNF();
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

    void Normalizer::normalizeToTwoNF()
    {
        this->normalizeToOneNF(); // To be in 2NF, it must first be in 1NF

        std::vector<std::pair<std::string, std::string>> partialDependencies = this->getPartialDependencies();
        std::vector<std::pair<std::string, std::string>> transitiveDependencies = this->getTrasitiveDependencies(); // In 2NF we keep the transitive dependencies

        if (partialDependencies.size() == 0)
        {
            return; // Already in 2NF as there are no partial dependencies
        }

        std::unordered_map<std::string, table::Table> newTables;

        const std::vector<table::row::TableRow> &tableRows = this->table.getTableRows();

        for (const auto &dependency : partialDependencies)
        {
            // std::cout << "Primary Key: " << dependency.first << " Partial Dependency: " << dependency.second << std::endl;
            for (us i = 0; i < tableRows.size();)
            {
                if (tableRows[i].getRowName() != dependency.second) // Skip if not a partial dependency
                {
                    i++;
                    continue;
                }

                if (newTables.find(dependency.first) == newTables.end()) // If the primary key doesn't already exist
                {
                    newTables[dependency.first] = table::Table(this->convertRowToTableName(dependency.first));

                    newTables[dependency.first].addPrimaryKey(dependency.first); // Add the primary key to the new table
                    newTables[dependency.first].addTableRow(tableRows[i]);       // Add the row to the new table
                    this->table.removeTableRow(tableRows[i]);                    // Remove the row from the original table
                }
                else
                {
                    newTables[dependency.first].addTableRow(tableRows[i]); // Add the row to the new table
                    this->table.removeTableRow(tableRows[i]);              // Remove the row from the original table
                }
            }
        }

        for (const std::string &primaryKey : this->table.getPrimaryKeys())
        {
            if (newTables.find(primaryKey) != newTables.end()) // If the the new table exists
                for (const table::row::TableRow &row : tableRows)
                {
                    if (row.getRowName() == primaryKey) // Add the primary key to the new table
                    {
                        newTables[primaryKey].addTableRow(row);
                        break;
                    }
                }
        }

        for (const auto &dependency : transitiveDependencies)
        {
            for (const std::string &primaryKey : this->table.getPrimaryKeys())
            {
                if (newTables.find(primaryKey) != newTables.end()) // If the the new table exists
                {
                    for (const table::row::TableRow &row : newTables[primaryKey].getTableRows())
                    {
                        if (row.getRowName() == dependency.first) // Find the row that has the transitive dependency
                        {
                            for (const table::row::TableRow &innerRow : tableRows)
                            {
                                if (innerRow.getRowName() == dependency.second) // Find the row that is the transitive dependency
                                {
                                    newTables[primaryKey].addTableRow(innerRow); // Add the transitive dependency to the new table
                                    this->table.removeTableRow(innerRow);        // Remove the transitive dependency from the original table
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        for (auto &pair : newTables)
        {
            if (tableRows.size() > this->table.getPrimaryKeys().size()) // If the original table has more rows than just the primary keys, implies at least one row is dependent on the entire primary key
            {
                this->normalizedTables.push_back(this->table);
            }

            this->normalizedTables.push_back(pair.second);

            if (this->table.getPrimaryKeys().size() > 1 && this->normalizedTables.size() > 1)
            {
                this->createTableOnCompositeKey();
            }
        }
    }

    std::string Normalizer::printTable(table::Table &inTable)
    {
        std::string returnValue = "CREATE TABLE";

        if (inTable.getIfNotExists())
        {
            returnValue += " IF NOT EXISTS";
        }

        returnValue += " " + inTable.getTableName() + "(\n";
        returnValue += this->getTableRowString(inTable);
        returnValue += this->getTableRowPrimaryKeyString(inTable);
        returnValue += this->getTableRowForeignKeyString(inTable);
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
        std::string returnValue = "";

        if (inTable.getPrimaryKeys().size() > 0)
        {
            returnValue += "\tPRIMARY KEY(";

            for (const std::string &key : inTable.getPrimaryKeys())
            {
                returnValue += key + ", ";
            }

            returnValue = returnValue.substr(0, returnValue.length() - 2);
            returnValue += ")\n";
        }

        return returnValue;
    }

    std::string Normalizer::getTableRowForeignKeyString(table::Table &inTable)
    {
        std::string returnValue = "";

        if (inTable.getForeignKeys().size() > 0)
        {
            for (const table::foreign::ForeignKey &foreignKey : inTable.getForeignKeys())
            {
                returnValue += "\tFOREIGN KEY (";
                returnValue += foreignKey.getTableRow();
                returnValue += ") REFERENCES ";
                returnValue += foreignKey.getReferencedTableName();
                returnValue += "(";
                returnValue += foreignKey.getReferencedTableRow();
                returnValue += "),\n";
            }

            returnValue = returnValue.substr(0, returnValue.length() - 2);
            returnValue += "\n";
        }

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

    std::vector<std::pair<std::string, std::string>> Normalizer::getPartialDependencies()
    {
        std::vector<std::pair<std::string, std::string>> partialDependencies;

        std::unordered_map<std::string, std::vector<std::string>> primaryKeyDependencies;

        std::vector<std::string> primaryKeys = this->table.getPrimaryKeys();
        std::vector<dependencies::row::DependencyRow> dependencyRows = this->dependencies.getDependencyRows();

        for (us i = 0; i < primaryKeys.size(); ++i)
        {
            for (us j = 0; j < dependencyRows.size(); ++j)
            {
                if (primaryKeys[i] == dependencyRows[j].getRowName())
                {
                    for (const std::string &singleValued : dependencyRows[j].getSingleDependencies())
                    {
                        primaryKeyDependencies[primaryKeys[i]].push_back(singleValued);
                    }

                    for (const std::string &multiValued : dependencyRows[j].getMultiDependencies())
                    {
                        primaryKeyDependencies[primaryKeys[i]].push_back(multiValued);
                    }
                }
            }
        } // Get a map of the primary keys and their dependencies

        std::unordered_map<std::string, us> dependencyCounts;

        for (const auto &pair : primaryKeyDependencies)
        {
            for (const std::string &dependency : pair.second)
            {
                if (dependencyCounts.find(dependency) == dependencyCounts.end())
                {
                    dependencyCounts[dependency] = 1;
                }
                else
                {
                    ++dependencyCounts[dependency];
                }
            }
        } // Count how many times each dependency occurs

        for (const auto &dependencyPair : dependencyCounts)
        {
            if (dependencyPair.second != primaryKeys.size()) // If the dependency does not occur in every primary key
            {
                for (const auto &pair : primaryKeyDependencies)
                {
                    for (const std::string &dependency : pair.second)
                    {
                        if (dependency == dependencyPair.first) // If the depenency occurs in this specific primary key add it to the partial dependencies
                        {
                            partialDependencies.push_back(std::make_pair(pair.first, dependencyPair.first));
                        }
                    }
                }
            }
        }

        return partialDependencies;
    }

    std::vector<std::pair<std::string, std::string>> Normalizer::getTrasitiveDependencies()
    {
        std::vector<std::pair<std::string, std::string>> transitiveDependencies;

        std::unordered_map<std::string, std::vector<std::string>> primaryKeyDependencies;

        std::vector<std::string> primaryKeys = this->table.getPrimaryKeys();
        std::vector<dependencies::row::DependencyRow> dependencyRows = this->dependencies.getDependencyRows();
        std::vector<std::string> dependencyRowNames;
        std::vector<std::string> transitiveRowName;

        for (us i = 0; i < dependencyRows.size(); ++i)
        {
            dependencyRowNames.push_back(dependencyRows[i].getRowName());
        } // Get a list of all the dependency row names

        for (us i = 0; i < dependencyRowNames.size(); ++i)
        {
            bool isPrimaryKey = false;

            for (us j = 0; j < primaryKeys.size(); ++j)
            {
                if (primaryKeys[j] == dependencyRowNames[i])
                {
                    isPrimaryKey = true;
                    break;
                }
            }

            if (!isPrimaryKey)
            {
                for (us j = 0; j < dependencyRows.size(); ++j)
                {
                    if (dependencyRowNames[i] != dependencyRows[j].getRowName())
                    {
                        continue;
                    }
                    else
                    {
                        for (const std::string &singleValued : dependencyRows[j].getSingleDependencies())
                        {
                            transitiveDependencies.push_back(std::make_pair(dependencyRowNames[i], singleValued));
                        }

                        for (const std::string &multiValued : dependencyRows[j].getMultiDependencies())
                        {
                            transitiveDependencies.push_back(std::make_pair(dependencyRowNames[i], multiValued));
                        }

                        break;
                    }
                }
            }
        }

        return transitiveDependencies;
    }

    std::string Normalizer::convertRowToTableName(const std::string &rowName) const
    {
        std::string tableName;
        tableName += static_cast<char>(std::toupper(rowName[0]));

        for (us i = 1; i < rowName.length(); ++i)
        {
            tableName += rowName[i];
        }

        tableName += "Table";

        return tableName;
    }

    void Normalizer::createTableOnCompositeKey()
    {
        std::string compositeTableName;
        std::vector<table::row::TableRow> primaryKeyRows;

        for (const std::string &primaryKey : this->table.getPrimaryKeys())
        {
            compositeTableName += primaryKey;

            for (const table::row::TableRow &row : this->table.getTableRows())
            {
                if (row.getRowName() == primaryKey)
                {
                    primaryKeyRows.push_back(row);
                }
            }
        }

        compositeTableName += "Table";

        table::Table compositeTable(compositeTableName);

        for (const table::row::TableRow &primaryKeyRow : primaryKeyRows)
        {
            compositeTable.addTableRow(primaryKeyRow);

            std::string rowName = primaryKeyRow.getRowName();

            compositeTable.addForeignKey({rowName, this->convertRowToTableName(rowName), rowName});
        }

        this->normalizedTables.push_back(compositeTable);
    }

    /* Operator Overloads */

    std::ostream &operator<<(std::ostream &outputStream, Normalizer &normalizer)
    {
        for (table::Table &table : normalizer.getNormalizedTables())
        {
            outputStream << normalizer.printTable(table) << std::endl;
        }

        return outputStream;
    }
}