/*! \file table.h
    \brief Header file for creating a Table.
    \details Contains the function declarations for creating a Table
    \date 10/26/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <vector>

#include "TableRow/tableRow.h"
#include "ForeignKey/foreignKey.h"

namespace normalizer::table
{
    /*! \headerfile table.h
        \brief Creates a table in the database
        \date 10/26/2023
        \version 1.0
        \author Matthew Moore
    */
    class Table
    {
    public:
        /* Construtors and Destructors */

        /*! \brief Create a default table object
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        Table() {}

        /*! \brief Create a table object
            \param[in] name The name of the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        Table(const std::string &name) : tableName(name), ifNotExists(false) {}

        /*! \brief The default destructor
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        ~Table() {}

        /* Getters and Setters */

        /*! \brief Get the name of the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The name of the table
        */
        std::string getTableName() const;

        /*! \brief Get the rows of the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::vector<row::TableRow>> The rows of the table
        */
        std::vector<row::TableRow> &getTableRows();

        /*! \brief Get if the table should be created if it does not exist
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return bool If the table should be created if it does not exist
        */
        bool getIfNotExists() const;

        /*! \brief Gets the primary keys of the table
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The primary keys of the table
        */
        std::vector<std::string> getPrimaryKeys() const;

        /*! \brief Gets the foreign keys of the table
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<foreign::ForeignKey> The foreign keys of the table
        */
        std::vector<foreign::ForeignKey> getForeignKeys() const;

        /*! \brief Set the name of the table
            \param[in] name The name of the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return Return type
        */
        void setTableName(const std::string &name);

        /*! \brief Set if the table should be created if it does not exist
            \param[in] exists If the table should be created if it does not exist
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void setIfNotExists(const bool &exists);

        /* Member Functions */

        /*! \brief Add a row to the table
            \param[in] row The row to be added to the table
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void addTableRow(const row::TableRow &row);

        /*! \brief Adds a primary key to the manager
            \param[in] primaryKey The primary key to add
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
        */
        void addPrimaryKey(const std::string &primaryKey);

        /*! \brief Adds a foreign key to the manager
            \param[in] foreignKey The foreign key to add
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
        */
        void addForeignKey(const foreign::ForeignKey &foreignKey);

    private:
        std::string tableName;                        /*!< The name of the table */
        bool ifNotExists;                             /*!< Whether to create the table if it exists or not */
        std::vector<std::string> primaryKeys;         /*!< The primary keys of the table */
        std::vector<foreign::ForeignKey> foreignKeys; /*!< The foreign keys of the table */
        std::vector<row::TableRow> tableRows;         /*!< The rows of the table */
    };
}