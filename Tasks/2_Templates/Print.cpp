/**************************************************************************************************
*
* \file Print.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Extend the given 'print()' function by variadic templates to enable an arbitrary
*       number of function arguments.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>


// TODO: Extend the given 'print()' function by variadic templates to enable an arbitrary
//       number of function arguments.
template< typename... Ts >
void print( std::ostream& os, const Ts&... values )
{
   (os << ... << values);
}


int main()
{
   print( std::cout, "Hello\n" );
   print( std::cout, "Two ", "words\n" );
   print( std::cout, "Three ", "different ", "words\n" );
   print( std::cout, "Numbers: ", 1, ' ', 1.2, ' ', '\n' );
   // last one: (os << ( ... << ' ' << ( << '\n' )))

   return EXIT_SUCCESS;
}
