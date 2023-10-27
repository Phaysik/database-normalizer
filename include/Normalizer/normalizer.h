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

#include "aliases.h"
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
            \param[in] sqlFilePath The file path of the sql dataset file
            \param[in] functionalDependencies The file path of the functional dependencies file path
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        Normalizer(const us normalizeForm, const std::string &sqlFilePath, const std::string &dependencyFilePath);

        /*! \brief Creates a normalizer based on the desired normalization form as well as an already parsed sql table and functional dependencies file.
            \param[in] normalizeForm The form to normalize to
            \param[in] sqlTable The already parsed SQL dataset
            \param[in] functionalDependencies The already parsed functional dependencies
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        Normalizer(const us normalizeForm, const table::Table &sqlTable, const dependencies::DependencyManager &functionalDependencies) : normalizeTo(normalizeForm), table(sqlTable), dependencies(functionalDependencies) {}

        /*! \brief The default destructor
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        ~Normalizer() {}

    private:
        us normalizeTo;                               /*!< The normalization form to go to */
        table::Table table;                           /*!< The table to normalizer */
        dependencies::DependencyManager dependencies; /*!< The functional dependencies of the project */
    };
}