/**************************************************************************************************
*
* \file AddSub.cpp
* \brief C++ Training - Variadic Templates Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'addsub()' function, which performs an alternating addition/subtraction
*       of the given arguments. Examples:
*
*             addsub( 10, 9, 8, 7, 6 )    => 10 - 9 + 8 - 7 + 6     = 8
*             addsub( 10, 9, 8, 7, 6, 5 ) => 10 - 9 + 8 - 7 + 6 - 5 = 3
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


// TODO: Implement the 'addsub()' function, which performs an alternating addition/subtraction
//       of the given arguments.
template <typename T>
constexpr auto subadd(const T& value)
{
    return -value;
}

template <typename T>
constexpr auto addsub(const T& value)
{
    return value;
}

template <typename T, typename... Ts>
constexpr auto addsub(const T& value, const Ts&... values);

template <typename T, typename... Ts>
constexpr auto subadd(const T& value, const Ts&... values)
{
    return -value + addsub(values...);
}

template <typename T, typename... Ts>
constexpr auto addsub(const T& value, const Ts&... values)
{
    return value + subadd(values...);
}

int main()
{
   
   std::cout << "\n"
             << " addsub( 10, 9, 8, 7, 6    ) = " << addsub( 10, 9, 8, 7, 6    ) << " (expected: 8)\n"
             << " addsub( 10, 9, 8, 7, 6, 5 ) = " << addsub( 10, 9, 8, 7, 6, 5 ) << " (expected: 3)\n"
             << "\n";
   

   return EXIT_SUCCESS;
}

