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
// void print(std::ostream&) // (1)
// {
// }

/*
//Multiple instantiation for different numbers of parameters
template<typename T, typename... Ts > // T is parameter pack
void print( std::ostream& os, const T& value, const Ts&... values ) // (2)
{
   os << value;
   if constexpr(sizeof...(Ts)>0U){ // if it is false, the compiler doesn't peak inside it :) C++17
      print(os, values...); // Tail recursion
   }
}
*/

//third solution with at least one parameter:
// template <typename T, typename... Ts> // T is parameter pack
// void print(std::ostream& os, const T& value, const Ts&... values) // (2)
// {
//     os << value;
//     (os << ... << values); // Fold expression (C++17) -> only for operators
// }

// Instantiation just once
template <typename... Ts> // T is parameter pack
void print(std::ostream& os, const Ts&... values) // (2)
{
   (os << ... << values); // Fold expression (C++17) -> only for operators
}

int main()
{
   print( std::cout, "Hello\n" ); // C-style string literal: char[7]
   print( std::cout, "Two ", "words\n" ); //char[5], char[7] ...
   print( std::cout, "Three ", "different ", "words\n" );
   //print( std::cout, "Numbers: ", 1, ' ', 1.2, ' ', '\n' );

   return EXIT_SUCCESS;
}
