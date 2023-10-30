/*! \file foreignKey.h
    \brief Header file for creating a foreign key.
    \details Contains the function declarations for creating a foreign key
    \date 10/29/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>

namespace normalizer::table::foreign
{
    /*! \headerfile foreignKey.h
        \brief Creates a foreign key.
        \date 10/29/2023
        \version 1.0
        \author Matthew Moore
    */
    class ForeignKey
    {
    public:
        /* Constructors and Destructors */

        /*! \brief Creates a foreign key
            \param[in] inRow The row in the table that is a foreign key
            \param[in] refTableName The table that \p inRow references
            \param[in] refTableRow The row in \p refTableName that is being referenced
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
        */
        ForeignKey(const std::string &inRow, const std::string &refTableName, const std::string &refTableRow) : tableRow(inRow), referencedTableName(refTableName), referencedTableRow(refTableRow) {}

        /*! \brief The default destructor
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
        */
        ~ForeignKey(){};

        /* Getters and Setters */

        /*! \brief Gets the row in the table that is a foreign key
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The row in the table that is a foreign key
        */
        std::string getTableRow() const;

        /*! \brief Gets the table that #tableRow references
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The table that #tableRow references
        */
        std::string getReferencedTableName() const;

        /*! \brief Gets the row in #referencedTableName that is being referenced
            \date 10/29/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The row in #referencedTableName that is being referenced
        */
        std::string getReferencedTableRow() const;

        /* Operator Overloads */

        /*! \brief Checks to see if two foreign keys are the same
            \param[in] other The foreign key to compare against
            \date 10/30/2023
            \version 1.0
            \author Matthew Moore
            \return bool If the two foreign keys are the same
        */
        bool operator==(const ForeignKey &other) const;

    private:
        std::string tableRow;            /*!< The row in the table that is a foreign key */
        std::string referencedTableName; /*!< The table that #tableRow references */
        std::string referencedTableRow;  /*!< The row in #referencedTableName that is being referenced */
    };
}