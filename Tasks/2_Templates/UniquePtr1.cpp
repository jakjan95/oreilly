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
#include <memory>
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
struct my_defaul_deleter {
    void operator()(T* resources)
    {
        delete resources;
    }
};

template <typename T, typename D = my_defaul_deleter<T>>
class unique_ptr {
public:
    using pointer = T*;
    using element_type = T;

    constexpr unique_ptr()
        : ptr_ { nullptr }
    {
    }

    explicit unique_ptr(T* ptr)
        : ptr_ { ptr }
    {
    }

    ~unique_ptr()
    {
        D {}(ptr_);
    }

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& other_ptr) noexcept
        : ptr_ { other_ptr.ptr_ }
    {

        other_ptr.ptr_ = nullptr;
    }
    template <typename U, typename E>
    unique_ptr(unique_ptr<U, E>&& other_ptr) noexcept
        : ptr_ { other_ptr.ptr_ }
    {

        other_ptr.ptr_ = nullptr;
    }

    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr& operator=(unique_ptr&& other_ptr) noexcept
    {
        D {}(ptr_);
        ptr_ = other_ptr.ptr_;
        other_ptr.ptr_ = nullptr;
        return *this;
    }

    template <typename U, typename E>
    unique_ptr& operator=(unique_ptr<U, E>&& other_ptr) noexcept
    {
        D {}(ptr_);
        ptr_ = other_ptr.ptr_;
        other_ptr.ptr_ = nullptr;
        return *this;
    }

    T* release() noexcept
    {
        T* tmp = std::move(ptr_);
        ptr_ = nullptr;
        return tmp;
    }

    void reset(T* new_ptr = nullptr) noexcept
    {
        D {}(ptr_);
        ptr_ = new_ptr;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

private:
    T* ptr_;

    template <typename U, typename E>
    friend class unique_ptr;
};

// Step 3: Implement a 'unique_ptr' specialization for arrays
template <typename T>
struct my_defaul_deleter<T[]> {

    template <typename U>
    void operator()(U* resources)
    {
        delete[] resources;
    }
};

template <typename T, typename D>
class unique_ptr<T[], D> {
public:
    using pointer = T*;
    using element_type = T;

    constexpr unique_ptr()
        : ptr_ { nullptr }
    {
    }

    explicit unique_ptr(T* ptr)
        : ptr_ { ptr }
    {
    }

    ~unique_ptr()
    {
        D {}(ptr_);
    }

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& other_ptr) noexcept
        : ptr_ { other_ptr.ptr_ }
    {

        other_ptr.ptr_ = nullptr;
    }
    template <typename U, typename E>
    unique_ptr(unique_ptr<U, E>&& other_ptr) noexcept
        : ptr_ { other_ptr.ptr_ }
    {

        other_ptr.ptr_ = nullptr;
    }

    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr& operator=(unique_ptr&& other_ptr) noexcept
    {
        D {}(ptr_);
        ptr_ = other_ptr.ptr_;
        other_ptr.ptr_ = nullptr;
        return *this;
    }

    template <typename U, typename E>
    unique_ptr& operator=(unique_ptr<U, E>&& other_ptr) noexcept
    {
        D {}(ptr_);
        ptr_ = other_ptr.ptr_;
        other_ptr.ptr_ = nullptr;
        return *this;
    }

    T* release() noexcept
    {
        T* tmp = std::move(ptr_);
        ptr_ = nullptr;
        return tmp;
    }

    void reset(T* new_ptr = nullptr) noexcept
    {
        D {}(ptr_);
        ptr_ = new_ptr;
    }

    T& operator[](size_t index) const { return ptr_[index]; }

private:
    T* ptr_;
};

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
      
      // a = b;  // Compilation error!!!

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
