/**************************************************************************************************
*
* \file SimpsonPro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the empty functions to perform the following operations on the Simpson characters:
*       1. Print all characters to the screen
*       2. Randomize the order of characters ('r')
*       3. Find the youngest character ('y')
*       4. Order them by last name while preserving the order between equal elements ('l')
*       5. Highlight/capitalize the last name of all persons with the given name ('h')
*       6. Put all children first ('c')
*       7. Compute the total length of all last names ('t')
*       8. Check if two adjacent characters have the same age ('s')
*       9. Compute the maximum age difference between two adjacent characters ('d')
*       10. Determine the median age of all characters ('m')
*
**************************************************************************************************/

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <limits>
#include <numeric>
#include <random>
#include <string>
#include <vector>


struct Person
{
   std::string firstname;
   std::string lastname;
   int age;
};

bool isChildren( const Person& p )
{
   return p.age < 21;
}

std::ostream& operator<<( std::ostream& os, Person const& person )
{
   return os << std::setw(11) << std::left  << person.firstname
             << std::setw(11) << std::left  << person.lastname
             << std::setw(3)  << std::right << person.age;
}

void toupper( std::string& s )
{
   for( auto& c : s ) {
      c = std::toupper( c );
   }
}

template <typename Table>
void print(const Table& table)
{
    std::for_each(table.cbegin(), table.cend(),
        [](const auto el) { std::cout << el << '\n'; });
}

template <typename Table>
void random_order(Table& table)
{
    std::mt19937 gen(std::random_device {}());
    std::shuffle(table.begin(), table.end(), gen);
}

template <typename Table>
void find_youngest(const Table& table)
{
    const auto pos = std::min_element(table.cbegin(), table.end(),
        [](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; });
    std::cout << "Youngest person = " << pos->firstname << " " << pos->lastname << "\n";
}

template <typename Table>
void order_by_lastname(Table& table)
{
    std::sort(table.begin(), table.end(),
        [](const Person& lhs, const Person& rhs) { return lhs.lastname < rhs.lastname; });
}

template <typename Table>
void highlight_lastname(Table& table)
{
    std::string lastname {};

    std::cout << "Enter last name: ";
    std::cin >> lastname;

    std::for_each(table.begin(), table.end(),
        [&lastname](auto& el) {
            if (el.lastname == lastname) {
                toupper(el.lastname);
            }
        });
}

template <typename Table>
void children_first(Table& table)
{
    std::stable_partition(table.begin(), table.end(), isChildren);
}

template <typename Table>
void compute_total_lastname_length(const Table& table)
{
    auto totalLastNameLength = std::accumulate(table.cbegin(), table.cend(), 0,
        [](auto total, const Person& per) {
            return total + per.lastname.length();
        });
    std::cout << "The total length of all lastnames is equal to " << totalLastNameLength << '\n';
}

template <typename Table>
void same_age(const Table& table)
{
    const auto pos = std::adjacent_find(table.cbegin(), table.cend(),
        [](const Person& lhs, const Person& rhs) { return lhs.age == rhs.age; });

    if (pos != table.end()) {
        std::cout << pos->firstname << " and " << (pos + 1)->firstname << " have the same age!\n";
    } else {
        std::cout << "No consecutive persons with the same age found!\n";
    }
}

template <typename Table>
void maximum_age_difference(const Table& table)
{
    auto max_diff = std::numeric_limits<int>::min();
    for (auto left = table.begin(), right = table.begin() + 1; right != table.end(); ++left, ++right) {
        max_diff = std::max(max_diff, std::abs((*left).age - (*right).age));
    }
    std::cout << " Maximum age different = " << max_diff << "\n";
}

template <typename Table>
void median_age(Table& table)
{
    std::nth_element(table.begin(), table.begin() + table.size() / 2, table.end(),
        [](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; });
    const auto medina = table[table.size() / 2];
    std::cout << " Median age = " << medina << "\n";
}

int main()
{
   std::vector<Person> table =
      { Person{ "Homer",      "Simpson",    38 }
      , Person{ "Marge",      "Simpson",    34 }
      , Person{ "Bart",       "Simpson",    10 }
      , Person{ "Lisa",       "Simpson",     8 }
      , Person{ "Maggie",     "Simpson",     1 }
      , Person{ "Hans",       "Moleman",    33 }
      , Person{ "Ralph",      "Wiggum",      8 }
      , Person{ "Milhouse",   "Van Houten", 10 }
      , Person{ "Ned",        "Flanders",   60 }
      , Person{ "Jeff",       "Albertson",  45 }
      , Person{ "Montgomery", "Burns",     104 } };

   char command;

   while( std::cout << "Enter command: " && std::cin >> command )
   {
      switch( command )
      {
      case 'r':
         random_order( table );
         break;

      case 'y':
         find_youngest( table );
         break;

      case 'l':
         order_by_lastname( table );
         break;

      case 'h':
         highlight_lastname( table );
         break;

      case 'c':
         children_first( table );
         break;

      case 't':
         compute_total_lastname_length( table );
         break;

      case 's':
         same_age( table );
         break;

      case 'd':
         maximum_age_difference( table );
         break;

      case 'm':
         median_age( table );
         break;

      default:
         return EXIT_SUCCESS;
      }

      print( table );
   }
}
