/**************************************************************************************************
*
* \file STLintro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
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

void printToScreen(Ints const& ints)
{
    std::for_each(ints.cbegin(), ints.cend(),
        [](const auto& el) { std::cout << el << '\t'; });
    std::cout << '\n';
}

void reverseOrder(Ints& ints)
{
    std::reverse(ints.begin(), ints.end());
    printToScreen(ints);
}

void findFirstFive(Ints const& ints)
{
    auto firstFiveInVector = std::find(ints.cbegin(), ints.cend(), 5);
    if (firstFiveInVector != ints.cend()) {
        std::cout << "found first 5 at position: " << std::distance(ints.begin(), firstFiveInVector) << '\n';
    }
}

void countNumberOfFives(Ints const& ints)
{
    const auto fivesCounter = std::count(ints.cbegin(), ints.cend(), 5);
    std::cout << "This cointainer contains " << fivesCounter << " fives\n";
}

void replaceAllFivesWithTwos(Ints& ints)
{
    const auto oldValue = 5;
    const auto newValue = 2;
    std::replace(ints.begin(), ints.end(), oldValue, newValue);
    printToScreen(ints);
}

void sortInts(Ints& ints)
{
    std::sort(ints.begin(), ints.end());
    printToScreen(ints);
}

void findAllTwos(Ints const& ints)
{
    auto firstTwo = std::lower_bound(ints.begin(), ints.end(), 2);
    auto lastTwo = std::upper_bound(ints.begin(), ints.end(), 2);
    std::cout << "Distance between twos is " << std::distance(firstTwo, lastTwo) << '\n';
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

