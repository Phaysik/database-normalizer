/*! \file normalizer.h
    \brief Header file for creating a database manager.
    \details Contains the function declarations for creating a database manager
    \date 10/27/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "aliases.h"
#include "FileManager/fileManager.h"
#include "Table/table.h"
#include "Dependencies/dependencyManager.h"
#include "Interpreter/Parser/parser.h"

namespace normalizer
{
    /*! \headerfile normalizer.h
        \brief Normalizes databases up to 5NF
        \date 10/27/2023
        \version 1.0
        \author Matthew Moore
    */
    class Normalizer
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Create a normalizer based on the desired normalization form
            \param[in] normalizeForm The form to normalize to
            \param[in] sqlFilePath The file path of the sql dataset file
            \param[in] functionalDependencies The file path of the functional dependencies file path
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        Normalizer(const us normalizeForm, const std::string &sqlFilePath, const std::string &dependencyFilePath);

        /*! \brief Creates a normalizer based on the desired normalization form as well as an already parsed sql table and functional dependencies file.
            \param[in] normalizeForm The form to normalize to
            \param[in] sqlTable The already parsed SQL dataset
            \param[in] functionalDependencies The already parsed functional dependencies
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        Normalizer(const us normalizeForm, const table::Table &sqlTable, const dependencies::DependencyManager &functionalDependencies) : normalizeTo(normalizeForm), table(sqlTable), dependencies(functionalDependencies) {}

        /*! \brief The default destructor
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        ~Normalizer() {}

        /* Member Functions */

        /*! \brief Normalizes the database according to #normalizeTo
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalize();

        /*! \brief Determines if #table is in 1NF
            \details Checks to see if #table is in 1NF by determining if the columns are nullable, or if there is no primary key assigned
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return bool If #table is in 1NF
        */
        bool determineInOneNF();

        /*! \brief Normalizes the database into 1NF
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalizeToOneNF();

        /*! \brief Normalizes the database into 2NF
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalizeToTwoNF();

        /*! \brief Converts a 1NF database into a string representation
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The string representation of the 1NF database
        */
        std::string toOneNFString();

        /*! \brief Converts the tables rows into a string representation
            \param [in] inTable The table whos rows are to be converted
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The string representation of the tables rows
        */
        std::string getTableRowString(table::Table &inTable);

        /*! \brief Converts the tables primary keys into a string representation
            \param[in] inTable The primary keys to be converted
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The string representation of the tables primary keys
        */
        std::string getTableRowPrimaryKeyString(table::Table &inTable);

        /*! \brief Gets the rows in the database that do not depend on another row
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The rows in the database that do not depend on another row
        */
        std::vector<std::string> getNonDependentRows();

        /*! \brief Gets the partial dependencies in the database
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The partial dependencies in the database
        */
        std::vector<std::pair<std::string, std::string>> getPartialDependencies();

        /*! \brief Gets the transitive dependencies in the database
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The transitive dependencies in the database
        */
        std::vector<std::pair<std::string, std::string>> getTrasitiveDependencies();

    private:
        us normalizeTo;                               /*!< The normalization form to go to */
        table::Table table;                           /*!< The table to normalizer */
        std::vector<table::Table> normalizedTables;   /*!< The normalized tables */
        dependencies::DependencyManager dependencies; /*!< The functional dependencies of the project */
        bool hasPrimaryKey;                           /*!< If the table has a primary key set */
        bool hasNullableRows;                         /*!< If the table has any nullable rows */
    };
}