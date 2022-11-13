/**************************************************************************************************
*
* \file Print.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
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
// SOLUTION 1
/*
template <typename T>
void print(std::ostream& os, const T& value)
{
    os << value;
}

template <typename T, typename... Ts>
void print(std::ostream& os, const T& value, const Ts&... values)
{
    print(os, value);
    print(os, values...);
}
*/

// SOLUTION 2
template <typename T, typename... Ts>
void print(std::ostream& os, const T& value, const Ts&... values)
{
    os << value;
    if constexpr (sizeof...(Ts) > 0U) { // C++17 constexpr if :)
        print(os, values...);
    }
}


// SOLUTION 3
/*
template <typename T, typename... Ts>
void print(std::ostream& os, const T& value, const Ts&... values)
{
    os << value;
    (os << ... << values); // Fold expression (works for operators +, -, << etc.)
}
*/

int main()
{

    print(std::cout, "Hallo\n");
    print(std::cout, "Two ", "words\n");
    print(std::cout, "Numbers: ", 1, ' ', 1.2, ' ', '\n');

    return EXIT_SUCCESS;
}
