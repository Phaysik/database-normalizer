/*! \file main.cpp
    \brief C++ file for creating the entry point for the database-normalizer program.
    \details Contains the function definitions for creating the entry point for the database-normalizer program
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#include "Normalizer/normalizer.h"
#include "Normalizer/formConstants.h"
#include "constants.h"

/*! \brief The entry point for the program
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
    \return int The status code of the program
*/
int main()
{
    normalizer::Normalizer normalizer(normalizer::NormalizationForm::FOUR, normalizer::file::SQL_DATASET_FOLDER + "4nf.sql", normalizer::file::FUNCTIONAL_DEPENDENCIES_FOLDER + "4nf.txt");

    normalizer.normalize();

    std::cout << normalizer << std::endl;

    return 0;
}