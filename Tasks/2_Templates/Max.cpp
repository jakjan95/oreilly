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
inline T max(const T& lhs, const T& rhs)
{
    return lhs < rhs ? rhs : lhs;
}

// Step 2: Definition of the 'max()' function template with two template arguments
template <typename T1, typename T2>
inline auto max(const T1& lhs, const T2& rhs)
{
    return lhs < rhs ? rhs : lhs;
}

// Step 3: Overload of the 'max()' function
inline int max(int lhs, int rhs)
{
    return lhs < rhs ? rhs : lhs;
}

// Step 4: Specialization of the 'max()' function template with a single template argument
template <>
inline int max<int>(const int& lhs, const int& rhs)
{
    return lhs < rhs ? rhs : lhs;
}

// Step 4: Specialization of the 'max()' function template with two template arguments
template <>
inline auto max<int, int>(const int& lhs, const int& rhs)
{
    return lhs < rhs ? rhs : lhs;
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
