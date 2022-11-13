/**************************************************************************************************
*
* \file VariadicMax.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Extend the 'max()' function template for an arbitrary number of elements.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>

// SOLUTION 1
/*
// Definition of the 'max()' function template
template< typename T1, typename T2 >
inline auto max( const T1& a, const T2& b )
//   -> std::common_type_t<T1,T2>    // Trailing return type necessary for C++11
{
   return ( a < b ) ? b : a;
}


// 'max()' function template for an arbitrary number of elements
template <typename T1, typename T2, typename... Ts>
inline auto max(const T1& a, const T2& b, const Ts&... values)
{
    return max(max(a, b), values...);
}
*/

// SOLUTION 2
template <typename T1, typename T2, typename... Ts>
inline auto max(const T1& a, const T2& b, const Ts&... values)
{
    const auto tmp = (a < b) ? b : a;
    if constexpr (sizeof...(Ts) == 0U) {
        //   return (a < b) ? b : a;
        return tmp;
    } else {
        //   return max(((a < b) ? b : a), values...);
        return max(tmp, values...);
    }
}

int main()
{
   std::cout << "\n"
                " max( 1, 5 )          = " << max( 1, 5 ) << "\n"
                " max( 3, 2 )          = " << max( 3, 2 ) << "\n"
                " max( 1.2, 2.3 )      = " << max( 1.2, 2.3 ) << "\n"
                " max( 1.2, -4 )       = " << max( 1.2, -4 ) << "\n"
                " max( 1, 2.8 )        = " << max( 1, 2.8 ) << "\n"
                " max( 1, 5, 4 )       = " << max( 1, 5, 4 ) << "\n"
                " max( 1, -1.3F, 2.3 ) = " << max( 1, -1.3F, 2.3 ) << "\n"
                "\n";

   return EXIT_SUCCESS;
}
