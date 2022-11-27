/**************************************************************************************************
*
* \file STLintro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
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
    std::copy(std::cbegin(ints), std::cend(ints), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}


void reverseOrder( Ints& ints )
{
    std::reverse(std::begin(ints), std::end(ints));
    std::cout << "After reversing: ";
    printToScreen(ints);
}


void findFirstFive( Ints const& ints )
{
    auto it = std::find(std::cbegin(ints), std::cend(ints), 5);
    if (it != std::cend(ints)) {
        std::cout << "First 5 found at position: " << std::distance(std::cbegin(ints), it) << "\n";
    }
}


void countNumberOfFives( Ints const& ints )
{
    auto numberOfFives = std::count_if(std::cbegin(ints), std::cend(ints),
        [](const auto& el) { return el == 5; });
    std::cout << "Number of Fives in container: " << numberOfFives << "\n";
}


void replaceAllFivesWithTwos( Ints& ints )
{
    std::replace(std::begin(ints), std::end(ints), 5, 2);
    std::cout << "After replacing Fives with Twos: ";
    printToScreen(ints);
}


void sortInts( Ints& ints )
{
    std::sort(std::begin(ints), std::end(ints));
    std::cout << "After sorting: ";
    printToScreen(ints);
}


void findAllTwos( Ints const& ints )
{
   //or as it is sorted we can use lower_bound and upper_bound or equal_range
    auto it = std::find(std::cbegin(ints), std::cend(ints), 2);
    while (it != std::cend(ints)) {
        std::cout << "Found 2 at position: " << std::distance(std::cbegin(ints), it) << "\n";
        it = std::find(std::next(it), std::cend(ints), 2);
    }
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

