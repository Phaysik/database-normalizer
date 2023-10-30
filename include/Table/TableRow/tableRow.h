/*! \file tableRow.h
    \brief Header file for creating a table row object.
    \details Contains the function declarations for creating a table row object.
    \date 10/26/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>

#include "RowDefinition/genericRowDefinition.h"

namespace normalizer::table::row
{
    /*! \headerfile tableRow.h
        \brief Contains the function declarations for defining a table row object
        \date 10/26/2023
        \version 1.0
        \author Matthew Moore
    */
    class TableRow
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Create the definition of a table row
            \param[in] name The name of the table row
            \param[in] definition The definition of the table row
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        TableRow(const std::string &name, const GenericRowDefinition &definition) : rowName(name), rowDefinition(definition) {}

        /*! \brief The default destructor
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
        */
        ~TableRow() {}

        /* Getters and Setters */

        /*! \brief Get the name of the table row
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The name of the table row
        */
        std::string getRowName() const;

        /*! \brief Get the definition of the table row
            \date 10/26/2023
            \version 1.0
            \author Matthew Moore
            \return GenericRowDefinition The definition of the table row
        */
        GenericRowDefinition &getRowDefinition();

        /* Operator Overloads */

        /*! \brief Checks to see if two table rows are equal
            \param[in] other The other table row to compare to
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return bool If the two table rows are equal
        */
        bool operator==(const TableRow &other) const;

    private:
        std::string rowName;                /*!< The name of the row */
        GenericRowDefinition rowDefinition; /*!< The definition of the row */
    };
}