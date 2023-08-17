/**************************************************************************************************
*
* \file Function_1.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a simplified std::function to demonstrate the type erasure design pattern.
*       Use the inheritance-based approach.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


//---- <Function.h> -------------------------------------------------------------------------------

template< typename Fn > // int(void), double(double)
class Function;

// TODO: Implement a simplified std::function by means of type erasure.

// R(Args...) -> the most generic function type
template< typename R, typename... Args>
class Function<R(Args...)>
{
   public:
      template<typename Callable>
      Function(Callable callable)
      : pimpl_{std::make_unique<Model<Callable>>(callable)}
      {}

      R operator()(Args... args) const {return pimpl_->invoke(args...);}

   private:
      struct Concept //External Polymorphism design pattern
      {
         virtual ~Concept() = default;
         virtual R invoke(Args... args) const = 0; 
      };

      template <typename Callable>
      struct Model : public Concept
      {
         explicit Model(Callable callable) : callable_{callable}{}
         R invoke(Args... args) const override{return callable_(args...); }
         Callable callable_;
      };

      std::unique_ptr<Concept> pimpl_; // Bridge design pattern
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename Fn, typename... Args >
void test( Function<Fn> const& f, Args&&... args )
{
   auto const res = f( std::forward<Args>(args)... );
   std::cout << "\n res = " << res << "\n\n";
}


int foo()
{
   return 1;
}

struct Foo {
   double operator()( double d ) const {
      return 2.0*d;
   }
};


int main()
{
   {
      auto const fp = foo;  // Function pointer
      test<int(void)>( fp );
   }

   {
      auto const fo = Foo{};  // Function object
      test<double(double)>( fo, 1.0 );
   }

   {
      auto const lambda = [](){ return "three"; };  // Lambda
      test<std::string(void)>( lambda );
   }

   return EXIT_SUCCESS;
}
