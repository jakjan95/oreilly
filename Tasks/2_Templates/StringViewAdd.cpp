/**************************************************************************************************
*
* \file StringViewAdd.cpp
* \brief C++ Training - Example for a std::string_view Problem with Generic Addition
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: The following code example contains a serious bug. Explain the bug and discuss a solution.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>


std::string operator+( std::string_view lhs, std::string_view rhs )
{
   return std::string( lhs ) + std::string( rhs );
}


/*
By addition of two string views, we deduce a result type of the function as the string_view which is a pointer
despite the operator+ for string_views, we return the addres of a local temporary object
To fix this problem we can either: 
- change the return type for the function to auto
- overload this function for std::string_views
*/

// Solution 1:
template< typename T >
auto add( const T& lhs, const T& rhs )
{
   return lhs + rhs;
}

/*
// Solution 2:
std::string add(std::string_view lhs, std::string_view rhs)
{
    return lhs + rhs;
}
*/


int main()
{
   std::string s1{ "Hello," };
   std::string s2{ " World" };

   std::string_view sv1{ s1 };
   std::string_view sv2{ s2 };

   const auto result = add( sv1, sv2 );

   std::cout << "\n result = " << result << "\n\n";

   return EXIT_SUCCESS;
}
