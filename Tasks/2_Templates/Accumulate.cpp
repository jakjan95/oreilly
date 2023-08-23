/**************************************************************************************************
*
* \file Accumulate.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Implement the 'accumulate()' algorithm. The algorithm should take a pair of iterators,
*         an initial value for the reduction operation, and a binary operation that performs the
*         elementwise reduction (see https://en.cppreference.com/w/cpp/algorithm/accumulate,
*         overload (2)).
*
* Step 2: Implement an overload of the 'accumulate()' algorithm that uses 'std::plus' as the
*         default binary operation.
*
* Step 3: Implement an overload of the 'accumulate()' algorithm that uses the default of the
*         underlying data type as initial value and 'std::plus' as the default binary operation.
*
* Step 4: Test your implementation with a custom binary operation (e.g. 'Times').
*
**************************************************************************************************/

#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <vector>


// Step 1: Implement the 'accumulate()' algorithm. The algorithm should take a pair of iterators,
//         an initial value for the reduction operation, and a binary operation that performs the
//         elementwise reduction (see https://en.cppreference.com/w/cpp/algorithm/accumulate,
//         overload (2)).
template <typename Iterator, typename T, typename Operation>
constexpr T accumulate(Iterator first, Iterator last, T init, Operation op)
{
    while (first != last) {
        init = op(std::move(init), *first++);
    }

    return init;
}

// Step 2: Implement an overload of the 'accumulate()' algorithm that uses 'std::plus' as the
//         default binary operation.
template <typename Iterator, typename T>
constexpr T accumulate(Iterator first, Iterator last, T init)
{
    return accumulate(first, last, init, std::plus<> {});
}

// Step 3: Implement an overload of the 'accumulate()' algorithm that uses the default of the
//         underlying data type as initial value and 'std::plus' as the default binary operation.
template <typename Iterator>
constexpr auto accumulate(Iterator first, Iterator last)
{
    //  using IterType = decltype(*first);
    using ValueType = typename std::iterator_traits<Iterator>::value_type;
    using ReturnType = decltype(std::declval<ValueType>() + std::declval<ValueType>());
    return accumulate(first, last, ReturnType {});
}

// Step 4: Test your implementation with a custom binary operation (e.g. 'Times').
struct Times {

    template <typename T1, typename T2>
    constexpr auto operator()(const T1& lhs, const T2& rhs)
    {
        return lhs * rhs;
    }
};

int main()
{
   // Sum of values in a vector of integral values
   {
      const std::vector<int> v{ 1, 3, 5, 7 };
      const auto sum1 = accumulate( begin(v), end(v), int{0}, std::plus<>{} );
      std::cout << "\n sum1 = " << sum1 << "\n\n";
      const auto sum2 = accumulate( begin(v), end(v) );
      std::cout << "\n sum2 = " << sum2 << "\n\n";

   }

   // Product of values in a list of floating-point values
   {
      const std::list<double> l{ 1.1, 3.3, 5.5, 7.7 };
      const auto sum = accumulate( begin(l), end(l), double{1}, Times{} );
      std::cout << "\n sum = " << sum << "\n\n";
   }

   return EXIT_SUCCESS;
}
