/*! \file genericRowDefinition.h
    \brief Header file for creating an inheritable column definition.
    \details Contains the function declarations for creating an inheritable column definition.
    \date 10/26/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <iostream>

#include "aliases.h"

namespace normalizer::table::row
{
    /*! \headerfile genericRowDefinition.h
        \brief The base row definition class.
        \date 10/26/2023
        \version 1.0
        \author Matthew Moore
    */
    class GenericRowDefinition
    {
    public:
        /* Constructors and Destructors */

        /*! \brief The default constructor.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        GenericRowDefinition() {}

        /*! \brief Create an inheritable row definition
            \param [in] type The data type of the row
            \param [in] isNull Whether or not the row is null.
            \param [in] dataSize The number of bits or row length of the row
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        GenericRowDefinition(const std::string &type, const bool isNull = false, const sl dataSize = -1) : dataType(type), nullable(isNull), size(dataSize) {}

        /* Getters and Setters */

        /*! \brief Get the data type of the row.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The data type of the row.
        */
        std::string getDataType() const;

        /*! \brief Get if the row is nullable.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return bool If the row is nullable.
        */
        bool getNullable() const;

        /*! \brief Get the number of bits or row length of the row.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return sl The number of bits or row length of the row.
        */
        sl getSize() const;

        /*! \brief Set the data type of the row.
            \param[in] type The data type of the row.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void setDataType(const std::string &type);

        /*! \brief Set the nullability of the row.
            \param[in] isNull The nullability of the row.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void setNullable(const bool isNull);

        /*! \brief Set the data size of the row.
            \param[in] dataSize The data size of the row.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void setSize(const sl dataSize);

        /* Member Functions */

        /*! \brief Sets all member variables to their default values.
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        void defaultValues();

        /* Operator Overloads */

        /*! \brief Checks to see if two row definitions are equal.
            \param[in] other The other row definition to compare to
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return bool If the two row definitions are equal.
        */
        bool operator==(const GenericRowDefinition &other) const;

    private:
        std::string dataType; /*!< The type of the data */
        bool nullable;        /*!< If the row value can contain NULL */
        sl size;              /*!< The number of bits or row length of the row */
    };
}