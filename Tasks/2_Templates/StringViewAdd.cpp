/**************************************************************************************************
*
* \file StringViewAdd.cpp
* \brief C++ Training - Example for a std::string_view Problem with Generic Addition
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
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
#include <type_traits>


std::string operator+( std::string_view lhs, std::string_view rhs )
{
   return std::string( lhs ) + std::string( rhs );
}

template <typename T>
auto add(const T& lhs, const T& rhs)
{
    return lhs + rhs;
}

/*
/ We are returning string_view which is constructed based on string
/ At point when we are returning it we return freed stuff which cause danling pointer to freed table
/ The reason for that is string_view which is non-owning view :) 
/ Solution can be auto which deduce return type as std::string
*/

int main()
{
   std::string s1{ "Hello," };
   std::string s2{ " World" };

   std::string_view sv1{ s1 };
   std::string_view sv2{ s2 };

   const auto result = add( sv1, sv2 );
   std::cout << typeid(result).name() <<'\n';

   std::cout << "\n result = " << result << "\n\n";

   return EXIT_SUCCESS;
}
