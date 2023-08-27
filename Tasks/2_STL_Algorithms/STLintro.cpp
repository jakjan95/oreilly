/**************************************************************************************************
*
* \file STLintro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Solve the following tasks on a vector of integers by means of STL algorithms:
*       - Print the contents of the vector to the screen
*       - Reverse the order of elements in the vector
*       - Find the first element with the value 5
*       - Count the elements with the value 5
*       - Replace all 5s by 2s
*       - Sort the vector
*       - Determine the range of 2s
*
**************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


using Ints = std::vector<int>;


void printToScreen( Ints const& ints )
{
    std::for_each(ints.cbegin(), ints.cend(),
        [](const auto& el) {
            std::cout << ' ' << el;
        });
    std::cout << '\n';
}

void reverseOrder(Ints& ints)
{
    std::reverse(ints.begin(), ints.end());
    std::cout << "the vector after reversing of the order: ";
    printToScreen(ints);
}

void findFirstFive(Ints const& ints)
{
    auto pos = std::find(ints.cbegin(), ints.cend(), 5);
    if (pos != ints.cend()) {
        std::cout << "Found 5 at position=" << std::distance(ints.cbegin(), pos) << '\n';
    }
}

void countNumberOfFives( Ints const& ints )
{
    auto numOfFives = std::count(ints.cbegin(), ints.cend(), 5);
    std::cout << "Number of fives in the container: " << numOfFives << '\n';
}

void replaceAllFivesWithTwos(Ints& ints)
{
    std::replace(ints.begin(), ints.end(), 5, 2);
    std::cout << "the vector after replacement of all fives with twos: ";
    printToScreen(ints);
}

void sortInts(Ints& ints)
{
    std::sort(ints.begin(), ints.end());
    std::cout << "the vector after sorting: ";
    printToScreen(ints);
}

void findAllTwos(Ints const& ints)
{
    auto first = std::lower_bound(ints.cbegin(), ints.cend(), 2);
    auto last = std::upper_bound(ints.cbegin(), ints.cend(), 2);
    std::cout << "Number of twos: " << std::distance(first, last) << '\n';
}




int main()
{
   Ints ints{ 3, 6, 27, 5, 1, 8, 5, 4 };

   printToScreen( ints );
   reverseOrder( ints );
   findFirstFive( ints );
   countNumberOfFives( ints );
   replaceAllFivesWithTwos( ints );
   sortInts( ints );
   findAllTwos( ints );
}

