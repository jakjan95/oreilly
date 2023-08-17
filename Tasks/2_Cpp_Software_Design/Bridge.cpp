/**************************************************************************************************
*
* \file Bridge.cpp
* \brief C++ Training - Example for the Bridge Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: In the conceptual header file <X.h>, which #include directives could be immediately
*         removed without ill effect? You may not make any changes other than removing or
*         rewriting #include directives.
*
* Step 2: What further #includes could be removed if we made some suitable changes, and how?
*         This time, you may make changes to 'X' as long as 'X''s base classes and its public
*         interface remain unchanged; and current code that already uses 'X' should not be
*         affected beyond requiring a simple recompilation.
*
* Step 3: What further #includes could be removed if we made further changes to 'X', and how?
*         Now you may make any changes to 'X' as long as they don't change its public interface
*         so that existing code that uses 'X' is unaffected beyond requiring a simple
*         recompilation. Again, note that the comments are important.
*
* Inspired by Herb Sutter's "Exceptional C++", Items 26-29
*
**************************************************************************************************/


//---- <A.h> ---------------------------------------------------------------------------------------

#include <iosfwd>

class A
{
 public:
   virtual ~A() = default;

   virtual std::ostream& print( std::ostream& ) const = 0;
};

inline std::ostream& operator<<( std::ostream& os, const A& a )
{
   return a.print( os );
}


//---- <B.h> --------------------------------------------------------------------------------------

#include <string>
#include <utility>

class B
{
 public:
   explicit B( std::string s )
      : s_{ std::move(s) }
   {}

   const std::string& getString() noexcept { return s_; }

 private:
   std::string s_;
};


//---- <C.h> --------------------------------------------------------------------------------------

class C
{
 public:
   virtual ~C() = default;

   int getInt() const noexcept { return i_; }
   double getDouble() const noexcept { return d_; }

 private:
   int i_;
   double d_;
};


//---- <D.h> --------------------------------------------------------------------------------------

//#include <C.h>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class D : public C
{
 public:
   template< typename... Args >
   explicit D( Args... args )
      : strings_{ std::move(args)... }
   {}

   const std::string& getString( std::size_t index ) noexcept { return strings_[index]; }

 private:
   std::vector<std::string> strings_;
};


//---- <E.h> --------------------------------------------------------------------------------------

#include <string>
#include <utility>

class E
{
 public:
   explicit E( int i, std::string s )
      : i_{ i }
      , s_{ std::move(s) }
   {}

   int getInt() const noexcept { return i_; }
   const std::string& getString() const noexcept { return s_; }

 private:
   int i_;
   std::string s_;
};

//---- <Fwd.h> --------------------------------------------------------------------------------------

class C;
class E;


//---- <X.h> --------------------------------------------------------------------------------------

//#include <A.h>
//#include <B.h>

//#include <Fwd.h>


// library includes after header includes
#include <iosfwd> // iostream at least 50k lines of the code, iosfwd - only forward declarations
#include <memory>

// Inheritance introduces tight coupling(strong dependency)
class X : public A, private B
{
 public:
   X( const C& );

   ~X(); //solve problem with the unique_ptr but breaks The Rule of 5
   // The Rule of 5 - TODO:
   X(const X&);
   X& operator=(const X&);
   X(X&&);
   X& operator=(X&&);

   B  f( int, char* );
   C  f( int, C );
   C& g( B );
   E  h( E ); // Function declaration -> definition of type is not needed
   std::ostream& print( std::ostream& ) const override;

 private:
   // If you don't write destructor for X, the compiller generate it for you in the header file
   // The destructor of Impl is missing for the unique_ptr in the header file(as it is implemented in the cpp)
   struct Impl;
   std::unique_ptr<Impl> pimpl_; // Pointer to implementation (PIMPL idiom) -> the simplest form of the bridge
   //it introduces overhead of approximately 10%
};


//---- <X.cpp> ------------------------------------------------------------------------------------

//Include order:

//#include <X.h> // Self-containment(my own header file)

//#include <D.h>
//#include <E.h> // include before the standard includes (my own library)

// Third-party library(like boost)

#include <cassert>  // after X.h -> headers self contained
#include <list>
#include <iostream>

struct X::Impl
{
   Impl(const C& c)
      : clist_{ c, c, c }
      , d_{ "1", "2", "3" } 
   {}

   std::list<C> clist_;
   D            d_;
};

X::X( const C& c )
   : A{}
   , B{ "B" }
   , pimpl_{std::make_unique<Impl>(c)}
{}

X::~X() = default;

B X::f( int, char* )
{
   return B{ "B" };
}

C X::f( int, C )
{
   assert( !pimpl_->clist_.empty() );
   return *begin(pimpl_->clist_);
}

C& X::g( B )
{
   return pimpl_->d_;
}

E X::h( E )
{
   return E{ 42, "E" };
}

std::ostream& X::print( std::ostream& os ) const
{
   return os << "\nPrinting X\n\n";
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <X.h>

#include <cstdlib>
#include <iostream>

int main()
{
   X x{ C{} };

   std::cout << x;

   return EXIT_SUCCESS;
}
