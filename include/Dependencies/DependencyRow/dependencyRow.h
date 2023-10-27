/*! \file dependencyRow.h
    \brief Header file for creating a dependency row object.
    \details Contains the function declarations for creating a dependency row object
    \date 10/27/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

#include <string>
#include <vector>

namespace normalizer::dependencies::row
{
    /*! \headerfile dependencyRow.h
        \brief Contains the function declarations for definining a dependency row object
        \date 10/27/2023
        \version 1.0
        \author Matthew Moore
    */
    class DependencyRow
    {
    public:
        /* Constructors and Destructors */

        /*! \brief The default constructor
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        DependencyRow() {}

        /*! \brief Constructs the class with #rowName initialized
            \param[in] name The name of the row
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        DependencyRow(const std::string &name) : rowName(name) {}

        /*! \brief The default destructor
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        ~DependencyRow() {}

        /* Getters and Setters */

        /*! \brief Get the name of the dependency row
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return std::string The name of the dependency row
        */
        std::string getRowName() const;

        /*! \brief Gets the single valued functional dependencies
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The single valued functional dependencies
        */
        std::vector<std::string> getSingleDependencies() const;

        /*! \brief Gets the multi valued functional dependencies
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
            \return std::vector<std::string> The multi valued functional dependencies
        */
        std::vector<std::string> getMultiDependencies() const;

        /* Member Functions */

        /*! \brief Adds a single valued functional dependency to the dependency row
            \param[in] dependency The single valued functional dependency
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void addSingleDependency(const std::string &dependency);

        /*! \brief Adds a multi valued functional dependency to the dependency row
            \param[in] dependency The multi valued functional dependency
            \date 10/27/2023
            \version 1.0
            \author Matthew Moore
        */
        void addMultiDependency(const std::string &dependency);

    private:
        std::string rowName;                               /*!< The name of the row */
        std::vector<std::string> singleValuedDependencies; /*!< The single valued functional dependencies */
        std::vector<std::string> multiValuedDependencies;  /*!< The multi valued functional dependencies */
    };
}