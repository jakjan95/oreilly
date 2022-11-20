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
template <typename T>
struct default_delete {

    constexpr void operator()(T* ptr) const noexcept
    {
        delete ptr;
    }
};

template <typename U>
struct default_delete<U[]> {

    constexpr void operator()(U* ptr) const noexcept
    {
        delete[] ptr;
    }
};

template< typename T, typename D = default_delete<T>>
class unique_ptr
{
 public:
   using pointer = T*;
   using element_type = T;

   //  - default constructor
   unique_ptr() = default;

   //  - constructor taking a pointer to a dynamic resource
   explicit unique_ptr(T* ptr);

   //  - destructor
   ~unique_ptr();

   //  - copy constructor
   unique_ptr(const unique_ptr& ) = delete;

   //  - move constructor
   unique_ptr(unique_ptr&& other);

   //  - copy assignment operator
   unique_ptr& operator=(const unique_ptr& ) = delete;

   //  - move assignment operator
   unique_ptr& operator=(unique_ptr&& other);

   //  - move constructor for different pointer types
   template <typename U, typename E>
   unique_ptr(unique_ptr<U, E>&& other);

   //  - move assignment operator for different pointer types
   template <typename U, typename E>
   unique_ptr& operator=(unique_ptr<U, E>&& other);

   template <typename U, typename E>
   friend class unique_ptr;

   void reset(T* ptr = nullptr);
   T* release() noexcept;

   T& operator*()  const { return *ptr_; }
   T* operator->() const { return ptr_;  }

 private:
   T* ptr_{};
};

template <typename T, typename D>
unique_ptr<T, D>::unique_ptr(T* ptr)
    : ptr_ { ptr }
{
}

template <typename T, typename D>
unique_ptr<T, D>::unique_ptr(unique_ptr&& other)
    : ptr_ { other.ptr_ }
{
    other.ptr_ = nullptr;
}

template <typename T, typename D>
unique_ptr<T, D>& unique_ptr<T, D>::operator=(unique_ptr&& other)
{
    D {}(ptr_);
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}

template <typename T, typename D>
unique_ptr<T, D>::~unique_ptr()
{
    D {}(ptr_);
}

template <typename T, typename D> // List of class template parameteres
template <typename U, typename E> // List of member function template parameteres
unique_ptr<T, D>::unique_ptr(unique_ptr<U, E>&& other)
    : ptr_ { other.ptr_ }
{
    static_assert(std::is_convertible<U*, T*>::value, "Invalid pointer conversion!");
    other.ptr_ = nullptr;
}

template <typename T, typename D> // List of class template parameteres
template <typename U, typename E> // List of member function template parameteres
unique_ptr<T, D>& unique_ptr<T, D>::operator=(unique_ptr<U, E>&& other)
{
    static_assert(std::is_convertible<U*, T*>::value, "Invalid pointer conversion!");
    D {}(ptr_);
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}

template <typename T, typename D>
void unique_ptr<T, D>::reset(T* ptr)
{
    D {}(ptr_);
    ptr_ = ptr;
}

template <typename T, typename D>
T* unique_ptr<T, D>::release() noexcept
{
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

// Step 3: Implement a 'unique_ptr' specialization for arrays
template<typename T, typename D>
class unique_ptr<T[], D>
{
 public:
   using pointer = T*;
   using element_type = T;

   unique_ptr() = default;

   explicit unique_ptr(T* ptr);

   ~unique_ptr();

   unique_ptr(const unique_ptr& ) = delete;
   unique_ptr(unique_ptr&& other);


   unique_ptr& operator=(const unique_ptr& ) = delete;
   unique_ptr& operator=(unique_ptr&& other);

   template <typename U, typename E>
   unique_ptr(unique_ptr<U, E>&& other);

   template <typename U, typename E>
   unique_ptr& operator=(unique_ptr<U, E>&& other);

   template <typename U, typename E>
   friend class unique_ptr;

   void reset(T* ptr = nullptr);
   T* release() noexcept;

   T& operator[](size_t index) const { return ptr_[index]; }

   private:
   T* ptr_{};
};

template <typename T, typename D>
unique_ptr<T[], D>::unique_ptr(T* ptr)
    : ptr_ { ptr }
{
}

template <typename T, typename D>
unique_ptr<T[], D>::unique_ptr(unique_ptr&& other)
    : ptr_ { other.ptr_ }
{
    other.ptr_ = nullptr;
}

template <typename T, typename D>
unique_ptr<T[], D>& unique_ptr<T[], D>::operator=(unique_ptr&& other)
{
    D {}(ptr_);
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}

template <typename T, typename D>
unique_ptr<T[], D>::~unique_ptr()
{
    D {}(ptr_);
}

template <typename T, typename D> // List of class template parameteres
template <typename U, typename E> // List of member function template parameteres
unique_ptr<T[], D>::unique_ptr(unique_ptr<U, E>&& other)
    : ptr_ { other.ptr_ }
{
    static_assert(std::is_convertible<U*, T*>::value, "Invalid pointer conversion!");
    other.ptr_ = nullptr;
}

template <typename T, typename D> // List of class template parameteres
template <typename U, typename E> // List of member function template parameteres
unique_ptr<T[], D>& unique_ptr<T[], D>::operator=(unique_ptr<U, E>&& other)
{
    static_assert(std::is_convertible<U*, T*>::value, "Invalid pointer conversion!");
    D {}(ptr_);
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}

template <typename T, typename D>
void unique_ptr<T[], D>::reset(T* ptr)
{
    D {}(ptr_);
    ptr_ = ptr;
}

template <typename T, typename D>
T* unique_ptr<T[], D>::release() noexcept
{
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}




//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unique_ptr for a single Widget
   {
      // Step 1+2
      
      auto a = unique_ptr<Widget>( new Widget(2) );
      std::cout << " a has been created (a=" << (*a).get() << ")\n\n";

      auto b = unique_ptr<Widget>( new Widget(3) );
      std::cout << " b has been created (b=" << b->get() << ")\n\n";
      

      // Step 4+5
      
      //a = b;  // Compilation error!!!

      unique_ptr<const Widget> c( std::move( a ) );
      std::cout << " a has been moved to c (c=" << c->get() << ")\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=" << a->get() << ")\n\n";
      
   }

   // unique_ptr for an array of Widgets
   {
      // Step 3
      
      auto a = unique_ptr<Widget[]>( new Widget[2] );
      a[0].set( 1 );
      a[1].set( 2 );
      std::cout << " a has been created (a=[" << a[0].get() << "," << a[1].get() << "])\n\n";

      auto b = unique_ptr<Widget[]>( new Widget[3] );
      b[0].set( 3 );
      b[1].set( 4 );
      b[2].set( 5 );
      std::cout << " b has been created (a=[" << b[0].get() << "," << b[1].get() << "," << b[2].get() << "])\n\n";
      

      // Step 4+5

      //a = b;  // Compilation error!!!

      unique_ptr<Widget[]> c( std::move( a ) );
      std::cout << " a has been moved to c (c=[" << c[0].get() << "," << c[1].get() << "])\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=[" << a[0].get() << "," << a[1].get() << "," << a[2].get() << "])\n\n";
   }

   return EXIT_SUCCESS;
}
