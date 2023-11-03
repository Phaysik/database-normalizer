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
#include "formConstants.h"
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
            \param[in] getNormalizedForm If the user wants to get the highest normalized form of the input table
            \param[in] sqlFilePath The file path of the sql dataset file
            \param[in] functionalDependencies The file path of the functional dependencies file path
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        Normalizer(const NormalizationForm &normalizeForm, const bool getNormalizedForm, const std::string &sqlFilePath, const std::string &dependencyFilePath);

        /*! \brief Creates a normalizer based on the desired normalization form as well as an already parsed sql table and functional dependencies file.
            \param[in] normalizeForm The form to normalize to
            \param[in] getNormalizedForm If the user wants to get the highest normalized form of the input table
            \param[in] sqlTable The already parsed SQL dataset
            \param[in] functionalDependencies The already parsed functional dependencies
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        Normalizer(const NormalizationForm &normalizeForm, const bool getNormalizedForm, const table::Table &sqlTable, const dependencies::DependencyManager &functionalDependencies) : normalizeTo(normalizeForm), getHighestForm(getNormalizedForm), table(sqlTable), dependencies(functionalDependencies) {}

        /*! \brief The default destructor
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        ~Normalizer() {}

        /* Getters and Setters */

        /*! \brief Gets the normalized tables of the database
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<Table> The normalized tables of the database
        */
        std::vector<table::Table> &getNormalizedTables();

        /* Member Functions */

        /*! \brief Normalizes the database according to #normalizeTo
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalize();

        /* Operator Overloads */

        /*! \brief Pretty print the \ref #normalizer::Normalizer "Normalizer"
            \pre \p outputStream must be a stream that is writeable to
            \post \p outputStream will have the updated text to write to the stream.
            \param[in, out] outputStream The stream to write to
            \param[in] normalizer The \ref #normalizer::Normalizer "Normalizer" to write out
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return std::ostream The output stream
        */
        friend std::ostream &operator<<(std::ostream &outputStream, Normalizer &normalizer);

    private:
        /* Member Functions */

        /*! \brief Converts a 1NF database into a string representation
            \param [in] inTable The table to print
            \date 10/28/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The string representation of the 1NF database
        */
        std::string printTable(table::Table &inTable);

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

        /*! \brief Normalizes the database into 3NF
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalizeToThreeNF();

        /*! \brief Normalizes the database into BCNF
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalizeToBCNF();

        /*! \brief Normalizes the database into 4NF
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalizeToFourNF();

        /*! \brief Normalizes the database into 5NF
            \date 10/31/2023
            \version 1.0
            \author Matthew Moore
        */
        void normalizeToFiveNF();

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

        /*! \brief Converts the tables foreign keys into a string representation
            \param[in] inTable The foreign keys to be converted
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The string representation of the tables foreign keys
        */
        std::string getTableRowForeignKeyString(table::Table &inTable);

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
            \return std::vector<std::pair<std::string, std::string>> The partial dependencies in the database
        */
        std::vector<std::pair<std::string, std::string>> getPartialDependencies();

        /*! \brief Gets the transitive dependencies in the database
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::pair<std::string, std::string>> The transitive dependencies in the database
        */
        std::vector<std::pair<std::string, std::string>> getTrasitiveDependencies();

        /*! \brief Gets the dependencies that violate BCNF
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::pair<std::string, std::string>> The dependencies that violate BCNF
        */
        std::vector<std::pair<std::string, std::string>> getBCNFDependencies();

        /*! \brief Gets the multi valued dependencies in the database
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::pair<std::string, std::string>> The multi valued dependencies in the database
        */
        std::vector<std::pair<std::string, std::string>> getMultiValuedDependencies();

        /*! \brief Gets the join dependencies in the database
            \date 10/31/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::pair<std::string, std::string>> The join dependencies in the database
        */
        std::vector<std::pair<std::string, std::string>> getJoinDependencies();

        /*! \brief Converts a row name into a table name
            \param[in] rowName The row name to be converted
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The table name of the row
        */
        std::string convertRowToTableName(const std::string &rowName) const;

        /*! \brief Creates a connection table based on the composite key
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
        */
        void createTableOnCompositeKey();

        /*! \brief Gets the highest normalized form of the user's input table
            \date 11/02/2023
            \version 1.0
            \author Matthew Moore
            \return us The highest normalized form of the user's input table
        */
        us getHighestNormalizedForm();

        NormalizationForm normalizeTo;                /*!< The normalization form to go to */
        bool getHighestForm;                          /*!< If the user wants to get the highest normalized form of the table */
        table::Table table;                           /*!< The table to normalizer */
        std::vector<table::Table> normalizedTables;   /*!< The normalized tables */
        dependencies::DependencyManager dependencies; /*!< The functional dependencies of the project */
        bool hasPrimaryKey;                           /*!< If the table has a primary key set */
        bool hasNullableRows;                         /*!< If the table has any nullable rows */
    };
}