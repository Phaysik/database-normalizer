/*! \file genericRowDefinition.cpp
    \brief C++ file for creating a genericRowDefinition.
    \details Contains the function definitions for creating a genericRowDefinition
    \date 10/26/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Table/TableRow/RowDefinition/genericRowDefinition.h"

namespace normalizer::table::row
{
    /* Getters and Setters */

    std::string GenericRowDefinition::getDataType() const
    {
        return this->dataType;
    }

    bool GenericRowDefinition::getNullable() const
    {
        return this->nullable;
    }

    sl GenericRowDefinition::getSize() const
    {
        return this->size;
    }

    void GenericRowDefinition::setDataType(const std::string &type)
    {
        this->dataType = type;
    }

    void GenericRowDefinition::setNullable(const bool isNull)
    {
        this->nullable = isNull;
    }

    void GenericRowDefinition::setSize(const sl dataSize)
    {
        this->size = dataSize;
    }

    /* Member Functions */

    void GenericRowDefinition::defaultValues()
    {
        this->dataType = "";
        this->nullable = false;
        this->size = -1;
    }

    /* Operator Overloads */

    bool GenericRowDefinition::operator==(const GenericRowDefinition &other) const
    {
        return this->dataType == other.dataType && this->nullable == other.nullable && this->size == other.size;
    }
}