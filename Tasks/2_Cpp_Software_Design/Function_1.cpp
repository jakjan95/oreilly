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

template< typename Fn >
class Function;

// TODO: Implement a simplified std::function by means of type erasure.
template <typename R, typename... Args>
class Function<R(Args...)> {
public:
    template <typename Fn>
    Function(Fn fn)
        : pimpl_ { std::make_unique<Model<Fn>>(fn) }
    {
    }

    Function(const Function& other)
        : pimpl_ { other.pimpl_.clone() }
    {
    }

    Function& operator=(const Function& other)
    {
        Function tmp(other);
        std::swap(pimpl_, tmp.pimpl_);
        return *this;
    }

    ~Function() = default;
    Function(Function&&) = default;
    Function& operator=(Function&&) = default;

    R operator()(Args... args) const { return pimpl_->invoke(args...); }

private:
    struct Concept //External Polymorphism design pattern
    {
        virtual ~Concept() = default;
        virtual R invoke(Args... args) const = 0;
        virtual std::unique_ptr<Concept> clone() const = 0; //Prototype DP
    };

    template <typename Fn>
    struct Model : public Concept {
        explicit Model(Fn fn)
            : fn_ { fn }
        {
        }

        R invoke(Args... args) const override { return fn_(args...); }
        std::unique_ptr<Concept> clone() const final { return std::make_unique<Model>(fn_); }
        Fn fn_;
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
