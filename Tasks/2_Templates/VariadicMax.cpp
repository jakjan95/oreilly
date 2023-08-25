/**************************************************************************************************
*
* \file VariadicMax.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Extend the 'max()' function template for an arbitrary number of elements.
*
* Step 2: Use the 'max()' function template to determine the size of the largest type given to
*         the 'Variant' class template.
*
**************************************************************************************************/

#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>


// Definition of the 'max()' function template
template< typename T1, typename T2 >
constexpr auto max( T1 const& a, T2 const& b )
//   -> typename std::common_type<T1,T2>::type  // Trailing return type necessary for C++11
{
   return ( a < b ) ? b : a;
}


// 'max()' function template for an arbitrary number of elements
// TODO
template <typename T, typename... Ts>
constexpr auto max(const T& value, const Ts&... values)
{
    return max(value, max(values...));
}

// Application of the 'max()' function template to determine the largest given type
template< typename T, typename... Ts >
struct Variant
{
 public:
   // ...

   static constexpr size_t capacity  = max(sizeof(T), sizeof(Ts)...);
   static constexpr size_t alignment = max(alignof(T), alignof(Ts)...);

 private:
   alignas(alignment) std::array<std::byte,capacity> buffer_;
};


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


   Variant<int,double,std::string> v{};

   std::cout << "\n"
                " v.capacity  = " << v.capacity << "\n"
                " v.alignment = " << v.alignment << "\n"
                "\n";

   return EXIT_SUCCESS;
}
