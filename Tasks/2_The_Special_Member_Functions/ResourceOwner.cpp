/**************************************************************************************************
*
* \file ResourceOwner.cpp
* \brief C++ Training - Example for Copy and Move Operations
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Implement the copy operations of class 'ResourceOwner'.
*
* Step 2: Implement the move operations of class 'ResourceOwner'.
*
* Step 3: Refactor the 'ResourceOwner' to remove as many of the special member functions as
*         possible without changing the interface or behavior.
*
* Step 4: Assume the invariant that the 'm_resource' pointer must never be a nullptr. What
*         changes to the implementation of the special member functions are necessary?
*
**************************************************************************************************/

#include <cstdlib>
#include <iomanip>  // For the C++14 'std::quoted'
#include <iostream>
#include <pthread.h>
#include <string>
#include <utility>


class Resource
{
 public:
   explicit Resource( int i )
      : i_{ i }
   {}

   // Copy constructor (explicit definition as reference for the programming task)
   Resource( Resource const& other )
      : i_{ other.i_ }
   {}

   ~Resource() = default;

   // Copy assignment operator (explicit definition as reference for the programming task)
   Resource& operator=( Resource const& other )
   {
      i_ = other.i_;
      return *this;
   }

   // Move constructor (explicit definition as reference for the programming task)
   Resource( Resource&& other ) noexcept
      : i_{ std::move(other.i_) }
   {}

   // Move assignment operator (explicit definition as reference for the programming task)
   Resource& operator=( Resource&& other ) noexcept
   {
      i_ = std::move(other.i_);
      return *this;
   }

   int get() const { return i_; }
   void set( int i ) { i_ = i; }

 private:
   int i_{};
};


class ResourceOwner
{
 public:
   ResourceOwner( int id, std::string const& name, Resource* resource )
      : m_id      { id }
      , m_name    { name }
      , m_resource{ resource }
   {}

   ~ResourceOwner()
   {
      delete m_resource;
   }

   // Step 1: Implement the copy constructor of class 'ResourceOwner'.
   ResourceOwner(ResourceOwner const& other)
       : m_id { other.m_id }
       , m_name { other.m_name }
       , m_resource { other.m_resource ? new Resource(*other.m_resource) : nullptr }
   {
   }

   // Step 1: Implement the copy assignment operator of class 'ResourceOwner'.
   ResourceOwner& operator=(ResourceOwner const& other)
   {
       // SOLUTION 1: copy-and-swap idiom(not the fastes)
       if (this != &other) {
           ResourceOwner tmp { other };
           swap(tmp);
       }

       return *this;

      /*
       // SOLUTION 2
        if (this == &other) {
            return *this;
        }

        delete m_resource;

        m_id = other.m_id;
        m_name = other.m_name;
        m_resource = other.m_resource ? new Resource(*other.m_resource) : nullptr;

        return *this;
      */
   }

   void swap(ResourceOwner& other)
   {
       std::swap(m_id, other.m_id);
       std::swap(m_name, other.m_name);
       std::swap(m_resource, other.m_resource);
   }

   // Step 2: Implement the move constructor of class 'ResourceOwner'.
   ResourceOwner(ResourceOwner&& other) noexcept
       : m_id { other.m_id }
       , m_name { std::move(other.m_name) }
       //  , m_resource { std::exchange(other.m_resource, nullptr) }
       , m_resource { other.m_resource }
   {
       other.m_resource = nullptr;
   }

   // Step 2: Implement the move assignment operator of class 'ResourceOwner'.
   ResourceOwner& operator=(ResourceOwner&& other) noexcept
   {
       // SOLUTION 1
       if (this != &other) {
           delete m_resource;
           m_id = other.m_id;
           m_name = std::move(other.m_name);
           m_resource = other.m_resource;
           other.m_resource = nullptr;
       }

       return *this;

       /*
       // SOLUTION 2 move and swap idiom
       if (this != &other) {
           ResourceOwner tmp(std::move(other));
           std::swap(m_id, tmp.m_id);
           std::swap(m_name, tmp.m_name);
           std::swap(m_resource, tmp.m_resource);
       }
       return *this;
      */
   }

   int                id()       const { return m_id;       }
   std::string const& name()     const { return m_name;     }
   Resource*          resource()       { return m_resource; }
   Resource const*    resource() const { return m_resource; }

 private:
   int m_id{ 0 };
   std::string m_name{};
   Resource* m_resource{ nullptr };
};


int main()
{
   ResourceOwner owner1( 1, "id1", new Resource(101) );
   std::cout << "\n"
             << " owner1: id=" << owner1.id() << ", name=" << std::quoted(owner1.name())
             << ", resource=" << owner1.resource()->get() << ", &resource = " << owner1.resource() << "\n\n";

   ResourceOwner owner2( owner1 );
   std::cout << " owner2: id=" << owner2.id() << ", name=" << std::quoted(owner2.name())
             << ", resource=" << owner2.resource()->get() << ", &resource = " << owner2.resource() << "\n\n";

   owner1.resource()->set(202);
   owner2 = owner1;
   std::cout << " owner2: id=" << owner2.id() << ", name=" << std::quoted(owner2.name())
             << ", resource=" << owner2.resource()->get() << ", &resource = " << owner2.resource() << "\n\n";

   owner1.resource()->set(303);
   ResourceOwner owner3( std::move(owner1) );
   std::cout << " owner3: id=" << owner3.id() << ", name=" << std::quoted(owner3.name())
            << ", resource=" << owner3.resource()->get() << ", &resource = " << owner3.resource() << "\n\n";

   owner2.resource()->set(404);
   owner1 = std::move(owner2);
   std::cout << " owner1: id=" << owner1.id() << ", name=" << std::quoted(owner1.name())
            << ", resource=" << owner1.resource()->get() << ", &resource = " << owner1.resource() << "\n\n";

   return EXIT_SUCCESS;
}
