/**************************************************************************************************
*
* \file STLpro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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
    std::cout << '\n';
}

int computeProduct( Ints const& ints )
{
    // TODO: Compute the product of all elements in the vector
    return std::accumulate(ints.cbegin(), ints.cend(), 1, std::multiplies{});
}

Ints extractInts(Ints const& ints)
{
    // TODO: Extract all numbers <= 5 from the vector
    Ints intsCopy { ints };
    intsCopy.erase(std::remove_if(intsCopy.begin(), intsCopy.end(),
                       [](const auto& val) {
                           return val <= 5;
                       }),
        intsCopy.end());
    return intsCopy;
}

double computeLength(Ints const& ints)
{
    // TODO: Compute the (numerical) length of the vector
    const auto sumOfSquares = std::inner_product(ints.cbegin(), ints.cend(), ints.cbegin(), double {});
    return std::sqrt(sumOfSquares);
}

Doubles computeRatios( Ints const& ints )
{
   // TODO: Compute the ratios v[i+1]/v[i] for all elements v[i] in v
   Doubles ratios{};
   ratios.reserve(ints.size());

   // std::transform(ints.cbegin(), std::prev(ints.cend()), std::next(ints.cbegin()), std::back_inserter(ratios),
   //     [](const auto& lhs, const auto& rhs) {
   //         return rhs / static_cast<double>(lhs);
   //     });

   std::transform(std::next(ints.cbegin()), ints.cend(), ints.cbegin(), std::back_inserter(ratios),
       [](double lhs, double rhs) {
           return lhs / rhs;
       });

   return ratios;
}


Ints moveRange( Ints const& ints )
{
   // TODO: Move the range [v[3],v[5]] to the beginning of the vector
   Ints intsCopy{ints};
   std::rotate(intsCopy.begin(), std::next(intsCopy.begin(),3),intsCopy.end());

   return intsCopy;
}


int main()
{
   Ints ints{ 1, 5, 2, 8, 7, 10, 4 };

   std::cout<<"ints:";
   printVector(ints);

   // Compute the product of all elements in v
   {
      std::cout << " Product of all elements: expected = 22400, actual = ";
      int const product = computeProduct( ints );
      std::cout << product << "\n";
   }

   // Extract all numbers <= 5 from the vector
   {
      std::cout << " All values <= 5: expected = ( 8 7 10 ), actual = ";
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
