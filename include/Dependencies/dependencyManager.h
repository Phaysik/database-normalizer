/*! \file dependencyManager.h
    \brief Header file for creating a functional dependency manager.
    \details Contains the function declarations for creating a functional dependency manager
    \date 10/27/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "DependencyRow/dependencyRow.h"

namespace normalizer::dependencies
{
    /*! \headerfile dependencyManager.h
        \brief Manager for functional dependencies.
        \date 10/27/2023
        \version 1.0
        \author Matthew Moore
    */
    class DependencyManager
    {
    public:
        /* Getters and Setters */

        /*! \brief Gets the primary keys of the table
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The primary keys of the table
        */
        std::vector<std::string> getPrimaryKeys() const;

        /*! \brief Gets the dependency rows of the table
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<DependencyRow> The dependency rows of the table
        */
        std::vector<row::DependencyRow> getDependencyRows() const;

        /* Member Functions */

        /*! \brief Adds a functional dependency to the manager.
            \param[in] row The functional dependencies of the row.
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void addDependency(const row::DependencyRow &row);

        /*! \brief Adds a primary key to the manager
            \param[in] primaryKey The primary key to add
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void addPrimaryKey(const std::string &primaryKey);

    private:
        std::vector<std::string> primaryKeys;           /*!< The primary keys of the table */
        std::vector<row::DependencyRow> dependencyRows; /*!< The dependencies of each row */
    };
}