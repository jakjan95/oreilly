/**************************************************************************************************
*
* \file Accumulate.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
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

#include <functional>
#include <iostream>
#include <list>
#include <vector>


// Step 1: Implement the 'accumulate()' algorithm. The algorithm should take a pair of iterators,
//         an initial value for the reduction operation, and a binary operation that performs the
//         elementwise reduction (see https://en.cppreference.com/w/cpp/algorithm/accumulate,
//         overload (2)).
template <typename IterType, typename T, typename Operation>
T accumulate(IterType first, IterType last, T init, Operation op)
{
    for (; first != last; ++first) {
        init = op(std::move(init), *first);
    }
    return init;
}

// Step 2: Implement an overload of the 'accumulate()' algorithm that uses 'std::plus' as the
//         default binary operation.
template <typename IterType, typename T>
T accumulate(IterType first, IterType last, T init)
{
    return accumulate(first, last, init, std::plus<> {});
}

// Step 3: Implement an overload of the 'accumulate()' algorithm that uses the default of the
//         underlying data type as initial value and 'std::plus' as the default binary operation.
template <typename IterType>
auto accumulate(IterType first, IterType last)
{
    using typeForInitialValue = decltype(*first + *last);
    return accumulate(first, last, typeForInitialValue {});
}

// Step 4: Test your implementation with a custom binary operation (e.g. 'Times').
struct Times {
    template <typename T1, typename T2>
    auto operator()(T1&& lhs, T2&& rhs)
    {
        return std::forward<T1>(lhs) * std::forward<T2>(rhs);
    }
};

int main()
{
   
   // Sum of values in a vector of integral values
   {
      const std::vector<int> v{ 1, 3, 5, 7 };
      const auto sum = accumulate( begin(v), end(v), 0, std::plus<>{} );
      std::cout << "\n sum = " << sum << "\n\n";
   }

   // Product of values in a list of floating-point values
   {
      const std::list<double> l{ 1.1, 3.3, 5.5, 7.7 };
      const auto sum = accumulate( begin(l), end(l), 1.0, Times{} );
      std::cout << "\n sum = " << sum << "\n\n";
   }
   

   return EXIT_SUCCESS;
}
