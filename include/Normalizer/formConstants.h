/*! \file formConstants.h
    \brief Header file for creating enums for specifying a normalization form.
    \details Contains the function declarations for creating enums for specifying a normalization form.
    \date 10/30/2023
    \version 1.0
    \author Matthew Moore
*/

#pragma once

namespace normalizer
{
    /*! \headerfile formConstants.h
        \brief List of valid normalization forms
        \details Valid normalization forms represented in an enum class
        \date 10/30/2023
        \version 1.0
        \author Matthew Moore
    */
    enum class NormalizationForm
    {
        ONE,   /*!< 1NF */
        TWO,   /*!< 2NF */
        THREE, /*!< 3NF */
        BCNF,  /*!< BCNF */
        FOUR,  /*!< 4NF */
        FIVE   /*!< 5NF */
    };
}