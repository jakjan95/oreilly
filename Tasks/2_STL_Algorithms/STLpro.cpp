/**************************************************************************************************
*
* \file STLpro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Solve the following tasks on a vector of integers by means of STL algorithms:
*       - Compute the product of all elements in the vector
*       - Extract all numbers <= 5 from the vector
*       - Compute the (numerical) length of the vector
*       - Compute the ratios v[i+1]/v[i] for all elements v[i] in v
*       - Move the range [v[3],v[5]] to the beginning of the vector
*
**************************************************************************************************/

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>


using Ints    = std::vector<int>;
using Doubles = std::vector<double>;

template <typename T>
void printVector(std::vector<T> const& numbers)
{
    std::copy(numbers.cbegin(), numbers.cend(), std::ostream_iterator<T>(std::cout, " "));
}

int computeProduct(Ints const& ints)
{
    const auto product = std::accumulate(ints.cbegin(), ints.cend(), 1, std::multiplies<int>());
    return product;
}

Ints extractInts(Ints const& ints)
{
    Ints intsSmallerThan5 {};
    std::copy_if(ints.cbegin(), ints.cend(), std::back_inserter(intsSmallerThan5),
        [](const auto el) { return el <= 5; });

    return intsSmallerThan5;
}

double computeLength(Ints const& ints)
{
    const auto vectorLength = std::sqrt(std::inner_product(ints.cbegin(), ints.cend(), ints.cbegin(), 0));
    return vectorLength;
}

Doubles computeRatios(Ints const& ints)
{
    Doubles vecCopy;
    std::transform(ints.cbegin(), ints.cend() - 1, ints.cbegin() + 1, std::back_inserter(vecCopy),
        [](const double lhs, const double rhs) { return rhs / lhs; });

    return vecCopy;
}

Ints moveRange(Ints const& ints)
{
    auto intsCopy(ints);
    std::rotate(intsCopy.begin(), intsCopy.begin() + 3, intsCopy.end());
    return intsCopy;
}

int main()
{
   Ints ints{ 1, 5, 2, 8, 7, 10, 4 };
   // Compute the product of all elements in v
   {
      std::cout << " Product of all elements: expected = 22400, actual = ";
      int const product = computeProduct( ints );
      std::cout << product << "\n";
   }

   // Extract all numbers <= 5 from the vector
   {
      std::cout << " All values <= 5: expected = ( 1 5 2 4 ), actual = ";
      printVector( extractInts( ints ) );
      std::cout << "\n";
   }

   // Compute the numerical length of the vector
   {
      std::cout << " Numerical length of the vector: expected = 16.0935, actual = ";
      double const length = computeLength( ints );
      std::cout << length << "\n";
   }

   // Compute the ratios v[i+1]/v[i] for all elements v[i] in v
   {
      std::cout << " Ratios: expected = ( 5 0.4 4 0.875 1.42857 0.4 ), actual = ";
      printVector( computeRatios( ints ) );
      std::cout << "\n";
   }

   // Move the range [v[3],v[5]] to the beginning of the vector
   {
      std::cout << " Moved range: expected = ( 8 7 10 4 1 5 2 ), actual = ";
      printVector( moveRange( ints ) );
      std::cout << "\n";
   }
}
