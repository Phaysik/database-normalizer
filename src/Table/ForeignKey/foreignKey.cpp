/*! \file foreignKey.cpp
    \brief C++ file for creating a foreignKey.
    \details Contains the function definitions for creating a foreignKey
    \date 10/29/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Table/ForeignKey/foreignKey.h"

namespace normalizer::table::foreign
{
    /* Getters and Setters */

    std::string ForeignKey::getTableRow() const
    {
        return this->tableRow;
    }

    std::string ForeignKey::getReferencedTableName() const
    {
        return this->referencedTableName;
    }

    std::string ForeignKey::getReferencedTableRow() const
    {
        return this->referencedTableRow;
    }
}