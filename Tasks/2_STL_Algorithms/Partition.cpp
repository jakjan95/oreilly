/**************************************************************************************************
*
* \file Partition.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'partition()' algorithm that separates two groups of elements. The
*       algorithm should take a pair of iterators and a unary predicate that identifies the
*       elements of the first group (see https://en.cppreference.com/w/cpp/algorithm/partition).
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <utility>
#include <vector>


// Implement the 'partition()' algorithm that separates two groups of elements. The algorithm
// should take a pair of iterators and a unary predicate that identifies the elements of the
// first group. (see https://en.cppreference.com/w/cpp/algorithm/partition).
template <class ForwardIt, class UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    if (first == last) {
        return last;
    }
    --last;

    while (first != last) {
        while (first != last && p(*first)) {
            ++first;
        }

        while (first != last && !p(*last)) {
            --last;
        }

        if (first != last) {
            std::iter_swap(first, last);
        }
    }

    return first;
}

// Bonus: Implement the 'partition_point()' algorithm, that locates the end of the first
// partition, that is, the first element that does not satisfy p or last if all elements
// satisfy p (see https://en.cppreference.com/w/cpp/algorithm/partition_point).
template <class ForwardIt, class UnaryPredicate>
ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    while (first != last && p(*first)) {
        ++first;
    }

    return first;
}

[[nodiscard]] constexpr bool is_odd( int i ) noexcept { return i%2 == 1; }
[[nodiscard]] constexpr bool is_small( int i ) noexcept { return i < 10; }


int main()
{
   // Separating odd and even values in a std::vector
   {
      std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

      const auto partition_point = ::partition( begin(v), end(v), is_odd );

      std::cout << "\n The odd values:";
      for( auto pos=begin(v); pos!=partition_point; ++pos ) {
         std::cout << ' ' << *pos;
      }
      std::cout << "\n The even values:";
      for( auto pos=partition_point; pos!=end(v); ++pos ) {
         std::cout << ' ' << *pos;
      }
      auto partitionPointFromAlgorithm = ::partition_point(v.begin(), v.end(), is_odd);
      std::cout<<"\nPartition point at: "<< std::distance(v.begin(), partitionPointFromAlgorithm)<<'\n';

      std::cout << "\n\n";
   }

   // Separating small and large values in a std::list
   {
      std::list<int> l{ 3, 11, 4, 1, 12, 7, 8, 2, 5, 10, 9, 6 };

      const auto partition_point = ::partition( begin(l), end(l), is_small );

      std::cout << "\n The small values:";
      for( auto pos=begin(l); pos!=partition_point; ++pos ) {
         std::cout << ' ' << *pos;
      }
      std::cout << "\n The large values:";
      for( auto pos=partition_point; pos!=end(l); ++pos ) {
         std::cout << ' ' << *pos;
      }
      auto partitionPointFromAlgorithm = ::partition_point(l.begin(), l.end(), is_small);
      std::cout<<"\nPartition point at: "<< std::distance(l.begin(), partitionPointFromAlgorithm)<<'\n';
      std::cout << "\n\n";
   }

   return EXIT_SUCCESS;
}
