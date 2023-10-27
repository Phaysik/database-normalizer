/*! \file dependencyRow.cpp
    \brief C++ file for creating a dependencyRow.
    \details Contains the function definitions for creating a dependencyRow
    \date 10/27/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Dependencies/DependencyRow/dependencyRow.h"

namespace normalizer::dependencies::row
{
    /* Getters and Setters */

    std::string DependencyRow::getRowName() const
    {
        return this->rowName;
    }

    std::vector<std::string> DependencyRow::getSingleDependencies() const
    {
        return this->singleValuedDependencies;
    }

    std::vector<std::string> DependencyRow::getMultiDependencies() const
    {
        return this->multiValuedDependencies;
    }

    /* Member Functions */

    void DependencyRow::addSingleDependency(const std::string &dependency)
    {
        this->singleValuedDependencies.push_back(dependency);
    }

    void DependencyRow::addMultiDependency(const std::string &dependency)
    {
        this->multiValuedDependencies.push_back(dependency);
    }
}