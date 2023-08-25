/**************************************************************************************************
*
* \file UniquePtr1.cpp
* \brief C++ Training - unique_ptr Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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
*       Step 7: Implement the free 'make_unique()' function
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

   explicit Widget( int i ) noexcept
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
template< typename T, typename Deleter = std::default_delete<T> >
class unique_ptr
{
 public:
   using pointer = T*;
   using element_type = T;

   // Step 1: Think about the following functions:
   //  - default constructor
   //  - constructor taking a pointer to a dynamic resource of type 'T*'
   //  - destructor
   
   constexpr unique_ptr() = default;
   explicit unique_ptr(T* ptr);
   ~unique_ptr() noexcept;

   // Step 4: Implement the copy and move operations:
   //  - copy constructor
   //  - move constructor
   //  - copy assignment operator
   //  - move assignment operator
   unique_ptr(const unique_ptr&) = delete;
   unique_ptr& operator=(const unique_ptr&) = delete;

   unique_ptr(unique_ptr&& other) noexcept;
   unique_ptr& operator=(unique_ptr&& other) noexcept;

   // Step 5: Implement move operations for different pointer types:
   //  - move constructor for different pointer types
   //  - move assignment operator for different pointer types
   template<typename U, typename E>
      unique_ptr(unique_ptr<U, E>&& other) noexcept;

   template<typename U, typename E>
   unique_ptr& operator=(unique_ptr<U,E>&& other);

   // Step 6: Implement the 'reset()' and 'release()' functions
   pointer release() noexcept;
   void reset(pointer ptr = pointer()) noexcept;

   T& operator*()  const { return *ptr_; }
   T* operator->() const { return ptr_;  }

 private:
   T* ptr_{ nullptr };
   Deleter deleter_{ Deleter{} };

   template <typename U, typename E>
   friend class unique_ptr;
};

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T* ptr)
    : ptr_ { ptr }
{
}
template <typename T, typename Deleter>
unique_ptr<T, Deleter>::~unique_ptr() noexcept
{
    deleter_(ptr_);
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr&& other) noexcept
    : ptr_ { std::exchange(other.ptr_, nullptr) }
{
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>& unique_ptr<T, Deleter>::operator=(unique_ptr&& other) noexcept
{
    if (this != &other) {
        deleter_(ptr_);
        ptr_ = std::exchange(other.ptr_, nullptr);
        deleter_ = other.deleter_;
    }
    return *this;
}

template <typename T, typename Deleter>
template <typename U, typename E>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr<U, E>&& other) noexcept
    : ptr_ { std::exchange(other.ptr_, nullptr) }
    , deleter_ { other.deleter_ }
{
}

template <typename T, typename Deleter>
template <typename U, typename E>
unique_ptr<T, Deleter>& unique_ptr<T, Deleter>::operator=(unique_ptr<U, E>&& other)
{
    deleter_(ptr_);
    ptr_ = std::exchange(other.ptr_, nullptr);
    deleter_ = other.deleter_;

    return *this;
}

template <typename T, typename Deleter>

auto unique_ptr<T, Deleter>::release() noexcept -> pointer
{
    return std::exchange(ptr_, nullptr);
}

template <typename T, typename Deleter>
void unique_ptr<T, Deleter>::reset(pointer ptr) noexcept
{
    unique_ptr(std::exchange(ptr_, ptr));
}

// Step 3: Implement a 'unique_ptr' specialization for arrays
template< typename T, typename Deleter >
class unique_ptr<T[], Deleter>
{
 public:
   using pointer = T*;
   using element_type = T;

   constexpr unique_ptr() = default;
   explicit unique_ptr(T* ptr);

   ~unique_ptr();

   unique_ptr(const unique_ptr&) = delete;
   unique_ptr& operator=(const unique_ptr&) = delete;

   unique_ptr(unique_ptr&& other) noexcept;
   unique_ptr& operator=(unique_ptr&& other) noexcept;

   pointer release() noexcept { return std::exchange(ptr_, nullptr); }
   void reset(std::nullptr_t ptr = nullptr) noexcept { unique_ptr(std::exchange(ptr_, ptr)); }

   template <typename U, typename E>
   void reset(pointer ptr) noexcept { unique_ptr(std::exchange(ptr_, ptr)); }

   T& operator[](std::size_t i) const { return ptr_[i]; }

   private:
   T* ptr_{ nullptr };
   Deleter deleter_{ Deleter{} };

   template< typename U, typename E > friend class unique_ptr;
};

template <typename T, typename Deleter>
unique_ptr<T[], Deleter>::unique_ptr(T* ptr)
    : ptr_ { ptr }
{
}

template <typename T, typename Deleter>
unique_ptr<T[], Deleter>::~unique_ptr()
{
    deleter_(ptr_);
}

template <typename T, typename Deleter>
unique_ptr<T[], Deleter>::unique_ptr(unique_ptr&& other) noexcept
    : ptr_ { std::exchange(other.ptr_, nullptr) }
    , deleter_ { other.deleter_ }
{
}

template <typename T, typename Deleter>
unique_ptr<T[], Deleter>& unique_ptr<T[], Deleter>::operator=(unique_ptr&& other) noexcept
{
    if (this != &other) {
        deleter_(ptr_);
        ptr_ = std::exchange(other.ptr_, nullptr);
        deleter_ = other.deleter_;
    }
    return *this;
}

// Step 7: Implement the free 'make_unique()' function




//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename T >
void transfer_ownership( unique_ptr<T> a )
{
   std::cout << " Ownership has been transfered (ptr=" << a->get() << ")\n\n";
}

int main()
{
   // unique_ptr for a single Widget
   {
      // Step 1+2
      auto a = unique_ptr<Widget>( new Widget(2) );
      std::cout << " a has been created (a=" << (*a).get() << ")\n\n";

      auto b = unique_ptr<Widget>( new Widget(3) );
      std::cout << " b has been created (b=" << b->get() << ")\n\n";

      // Step 4
      //a = b;  // Compilation error!!!

      {
         unique_ptr<Widget> c( std::move(a) );
         std::cout << " a has been moved to c (c=" << c->get() << ")\n\n";

         a = std::move(b);
         std::cout << " b has been moved to a (a=" << a->get() << ")\n\n";

         b = std::move(c);
         std::cout << " c has been moved to b (b=" << b->get() << ")\n\n";
      }

      // Step 5
      {
         unique_ptr<const Widget> c( std::move(a) );
         std::cout << " a has been moved to c (c=" << c->get() << ")\n\n";

         //b = std::move(b);  // Compilation error!!!

         c = std::move(b);
         std::cout << " c has been moved to c (c=" << c->get() << ")\n\n";

         transfer_ownership( std::move(c) );
      }
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

      unique_ptr<Widget[]> c( std::move(a) );
      std::cout << " a has been moved to c (c=[" << c[0].get() << "," << c[1].get() << "])\n\n";

      a = std::move(b);
      std::cout << " b has been moved to a (a=[" << a[0].get() << "," << a[1].get() << "," << a[2].get() << "])\n\n";
   }

   return EXIT_SUCCESS;
}
