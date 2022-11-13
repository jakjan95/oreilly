/**************************************************************************************************
*
* \file IsPointer.cpp
* \brief C++ Training - Easy Type Trait Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'is_pointer' type trait in the following example. The type trait should
*       determine if the given type is a pointer type. In case the given type is a pointer type,
*       the type trait should inherit from 'std::true_type', else it should derive from
*       'std::false_type'.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


// TODO: Implement the 'is_pointer' type trait to determine whether a given type is a pointer type.
template<typename T>
struct is_pointer{
    static constexpr bool value = false;

};

template <typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};

template <typename T>
struct is_pointer<T* const> {
    static constexpr bool value = true;
};

template <typename T>
struct is_pointer<T* volatile> {
    static constexpr bool value = true;
};

template <typename T>
struct is_pointer<T* const volatile> {
    static constexpr bool value = true;
};


int main()
{
   using Type1 = int;
   using Type2 = int const;
   using Type3 = int volatile;
   using Type4 = int const volatile;
   using Type5 = int*;
   using Type6 = int* const;
   using Type7 = int* volatile;
   using Type8 = int* const volatile;

   static_assert( !is_pointer<Type1>::value );
   static_assert( !is_pointer<Type2>::value );
   static_assert( !is_pointer<Type3>::value );
   static_assert( !is_pointer<Type4>::value );
   static_assert(  is_pointer<Type5>::value );
   static_assert(  is_pointer<Type6>::value );
   static_assert(  is_pointer<Type7>::value );
   static_assert(  is_pointer<Type8>::value );

   return EXIT_SUCCESS;
}
