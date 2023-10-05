/*! \file testMain.cpp
    \brief C++ file for running all tests.
    \date 10/04/2023
    \version 1.0
    \author Matthew Moore
*/

#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}