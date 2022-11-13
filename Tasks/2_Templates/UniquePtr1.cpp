/**************************************************************************************************
*
* \file UniquePtr1.cpp
* \brief C++ Training - unique_ptr Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a (simplified) 'std::unique_ptr' class template.
*       Step 1: Implement the 'unique_ptr' base template for single memory resources
*       Step 2: Add a template parameter for a deleter
*       Step 3: Implement a 'unique_ptr' specialization for arrays
*       Step 4: Implement the copy and move operations
*       Step 5: Implement move operations for different pointer types
*       Step 6: Implement the 'reset()' and 'release()' functions
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


//---- <Widget.h> ---------------------------------------------------------------------------------

// Auxiliary class for testing purposes
class Widget
{
 public:
   Widget()
   {
      std::cout << " Widget has been created (i=" << i_ << ")\n";
   }

   Widget( int i ) noexcept
      : i_( i )
   {
      std::cout << " Widget has been created (i=" << i_ << ")\n";
   }

   ~Widget() noexcept
   {
      std::cout << " Widget has been destroyed (i=" << i_ << ")\n";
   }

   void set( int i ) noexcept { i_ = i;    }
   int  get() const  noexcept { return i_; }

 private:
   int i_{ 0 };
};




//---- <memory> -----------------------------------------------------------------------------------

// Step 1: Implement the 'unique_ptr' base template for single memory resources
// Step 2: Add a template parameter for a deleter
template< typename T >
class unique_ptr
{
 public:
   using pointer = T*;
   using element_type = T;

   // Step 1: Think about the following functions:
   //  - default constructor
   unique_ptr() = default;

   //  - constructor taking a pointer to a dynamic resource
   explicit unique_ptr(T* ptr);

   //  - destructor
   ~unique_ptr();

   // Step 4: Implement the copy and move operations:
   //  - copy constructor
   unique_ptr(const unique_ptr& ) = delete;

   //  - move constructor
   unique_ptr(unique_ptr&& other)
       : ptr_ { other.ptr_ }
   {
       other.ptr_ = nullptr;
   }

   //  - copy assignment operator
   unique_ptr& operator=(const unique_ptr& ) = delete;

   //  - move assignment operator

   // Step 5: Implement move operations for different pointer types:
   //  - move constructor for different pointer types
   template <typename U>
   unique_ptr(unique_ptr<U>&& other);

   template<typename U> friend class unique_ptr;

   //  - move assignment operator for different pointer types

   // Step 6: Implement the 'reset()' and 'release()' functions

   T& operator*()  const { return *ptr_; }
   T* operator->() const { return ptr_;  }

 private:
   T* ptr_{};
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_ { ptr }
{
}

template <typename T>
unique_ptr<T>::~unique_ptr() { delete ptr_; }

template <typename T> // List of class template parameteres
template <typename U> // List of member function template parameteres
unique_ptr<T>::unique_ptr(unique_ptr<U>&& other)
    : ptr_ { other.ptr_ }
{
    static_assert(std::is_convertible<U*, T*>::value, "Invalid pointer conversion!");
    other.ptr_ = nullptr;
}

// Step 3: Implement a 'unique_ptr' specialization for arrays




//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unique_ptr for a single Widget
   {
      // Step 1+2
      /*
      auto a = unique_ptr<Widget>( new Widget(2) );
      std::cout << " a has been created (a=" << (*a).get() << ")\n\n";

      auto b = unique_ptr<Widget>( new Widget(3) );
      std::cout << " b has been created (b=" << b->get() << ")\n\n";
      */

      // Step 4+5
      /*
      //a = b;  // Compilation error!!!

      unique_ptr<const Widget> c( std::move( a ) );
      std::cout << " a has been moved to c (c=" << c->get() << ")\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=" << a->get() << ")\n\n";
      */
   }

   // unique_ptr for an array of Widgets
   {
      // Step 3
      /*
      auto a = unique_ptr<Widget[]>( new Widget[2] );
      a[0].set( 1 );
      a[1].set( 2 );
      std::cout << " a has been created (a=[" << a[0].get() << "," << a[1].get() << "])\n\n";

      auto b = unique_ptr<Widget[]>( new Widget[3] );
      b[0].set( 3 );
      b[1].set( 4 );
      b[2].set( 5 );
      std::cout << " b has been created (a=[" << b[0].get() << "," << b[1].get() << "," << b[2].get() << "])\n\n";
      */

      // Step 4+5
      /*
      //a = b;  // Compilation error!!!

      unique_ptr<Widget[]> c( std::move( a ) );
      std::cout << " a has been moved to c (c=[" << c[0].get() << "," << c[1].get() << "])\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=[" << a[0].get() << "," << a[1].get() << "," << a[2].get() << "])\n\n";
      */
   }

   return EXIT_SUCCESS;
}
