/**************************************************************************************************
*
* \file Max.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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
#include <type_traits>

struct Widget {
    int i;
};

bool operator<(Widget a, Widget b)
{
    return a.i < b.i;
}

// Dynamic polymorphism - achieved by inheritance at runtime
// Compile time polymorphism

// One Definition Rule  - everything must be defined only once
// >compiler picks the first definition and ignores the rest

// auto f() -> int; //Trailing return type

// (1)
template <typename T>
    // requires std::integral<T> || std::is_floating_point<T> //C++20 concepts limiting types for template
T max(T a, T b) 
{
    return (a < b ? b : a);
}

// (2)
template <typename T, typename U> // Template Argument Deduction
auto max(T a, U b) //Return type deduction(C++14)
{
    return (a < b ? b : a); // Conditional operator -> common type uses it under the hood
    /*
    if (a < b)
        return b;
    else
        return a;
    */
}

// (3) - most special case for two ints(absolutely the best match for two intigers)
int max(int a, int b)
{
    return (a < b ? b : a);
}

// Only for special cases
// (4) => Only considered when function template (1) is used
template <> // Function template specialization => explicit instantiation of the (1)
int max<int>(int a, int b)
{
    return (a < b ? b : a);
}

/*
// what the compiler does(after use of (max,1,5)):
template <> // Template Instantiation
int max(int a, int b)   // T => int
{
    if (a < b)
        return a;
    return b;
}
*/


int main()
{
   std::cout << "\n"
                " max( 1, 5 )     = " << max( 1, 5 ) << "\n" // (3)
                " max( 3, 2 )     = " << max( 3, 2 ) << "\n" // (3)
                " max( 1.2, 2.3 ) = " << max( 1.2, 2.3 ) << "\n" // (1)
                " max( 1.2, -4 )  = " << max( 1.2, -4 ) << "\n" // (2) => Ignoring complication error with (1) -> Subtitution Failure Is Not An Error (SFINAE)
                " max( 1, 2.8 )   = " << max( 1, 2.8 ) << "\n" // (2)
                "\n";

   auto result = max(Widget{1}, Widget{5});
   return EXIT_SUCCESS;
}
