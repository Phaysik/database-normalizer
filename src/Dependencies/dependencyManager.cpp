/*! \file dependencyManager.cpp
    \brief C++ file for creating a functional dependency manager.
    \details Contains the function definitions for creating a functional dependency manager
    \date 10/27/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Dependencies/dependencyManager.h"

namespace normalizer::dependencies
{
    /* Getters and Setters */

    std::vector<row::DependencyRow> DependencyManager::getDependencyRows() const
    {
        return this->dependencyRows;
    }

    /* Member Functions */

    void DependencyManager::addDependency(const row::DependencyRow &row)
    {
        this->dependencyRows.push_back(row);
    }
}