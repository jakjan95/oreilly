/**************************************************************************************************
*
* \file Max.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Write a 'max()' function template that takes a single template parameter for its two
*         function parameters.
*
* Step 2: Write a 'max()' function template that takes two template parameters instead of one
*         (one for each function parameter).
*
* Step 3: Overload the 'max()' function template for integers.
*
* Step 4: Specialize the 'max()' function template(s) for integers.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


// Step 1: Definition of the 'max()' function template with a single template argument
template <typename T>
T max(const T& a, const T& b)
{
    return a < b ? b : a;
}

// Step 2: Definition of the 'max()' function template with two template arguments
template <typename T, typename U>
auto max(const T& a, const U& b)
{
    return a < b ? b : a;
}

// Step 3: Overload of the 'max()' function
int max(int a, int b)
{
    return a < b ? b : a;
}

// Step 4: Specialization of the 'max()' function template with a single template argument
template <>
int max<int>(const int& a, const int& b)
{
    return a < b ? b : a;
}

// Step 4: Specialization of the 'max()' function template with two template arguments
template <>
auto max<double, int>(const double& a, const int& b)
{
    std::cout << "HERE!!\n";
    return a < b ? b : a;
}

int main()
{
   
   std::cout << "\n"
                " max( 1, 5 )     = " << max( 1, 5 ) << "\n"
                " max( 3, 2 )     = " << max( 3, 2 ) << "\n"
                " max( 1.2, 2.3 ) = " << max( 1.2, 2.3 ) << "\n"
                " max( 1.2, -4 )  = " << max( 1.2, -4 ) << "\n"
                " max( 1, 2.8 )   = " << max( 1, 2.8 ) << "\n"
                "\n";
   

   return EXIT_SUCCESS;
}
