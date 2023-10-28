/*! \file tableRow.cpp
    \brief C++ file for creating a tableRow.
    \details Contains the function definitions for creating a tableRow
    \date 10/26/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Table/TableRow/tableRow.h"

namespace normalizer::table::row
{
    /* Getters and Setters */

    std::string TableRow::getRowName() const
    {
        return this->rowName;
    }

    GenericRowDefinition &TableRow::getRowDefinition()
    {
        return this->rowDefinition;
    }
}