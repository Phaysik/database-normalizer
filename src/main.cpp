/*! \file main.cpp
    \brief C++ file for creating the entry point for the database-normalizer program.
    \details Contains the function definitions for creating the entry point for the database-normalizer program
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
*/

#include "main.h"

/*! \brief The entry point for the program
    \date 10/11/2023
    \version 1.0
    \author Matthew Moore
    \return int The status code of the program
*/
int main()
{
    std::string datasetFile;
    std::string dependencyFile;
    char normalizeTo;
    normalizer::NormalizationForm normalizationForm;

    std::cout << "Enter the path to the SQL dataset file (It must be in the resources/sql folder): ";
    std::cin >> datasetFile;

    std::cout << "Enter the path to the functional dependencies file (It must be in the resources/dependencies folder): ";
    std::cin >> dependencyFile;

    std::cout << "Enter the normalization form required (1: 1NF, 2: 2NF, 3: 3NF, B: BCNF, 4: 4NF, 5: 5NF): ";
    std::cin >> normalizeTo;

    switch (normalizeTo)
    {
    case '1':
        normalizationForm = normalizer::NormalizationForm::ONE;
        break;
    case '2':
        normalizationForm = normalizer::NormalizationForm::TWO;
        break;
    case '3':
        normalizationForm = normalizer::NormalizationForm::THREE;
        break;
    case 'B':
        normalizationForm = normalizer::NormalizationForm::BCNF;
        break;
    case '4':
        normalizationForm = normalizer::NormalizationForm::FOUR;
        break;
    case '5':
        normalizationForm = normalizer::NormalizationForm::FIVE;
        break;
    default:
        std::cout << "Invalid normalization form." << std::endl;
        return 1;
    }

    normalizer::Normalizer normalizer(normalizationForm, normalizer::file::SQL_DATASET_FOLDER + datasetFile, normalizer::file::FUNCTIONAL_DEPENDENCIES_FOLDER + dependencyFile);

    normalizer.normalize();

    std::cout << normalizer << std::endl;

    return 0;
}