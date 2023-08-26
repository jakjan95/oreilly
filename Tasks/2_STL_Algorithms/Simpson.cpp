/**************************************************************************************************
*
* \file Simpson.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the empty functions to perform the following operations on the Simpson characters:
*       1. Print all persons to the screen
*       2. Randomize their order ('r')
*       3. Find the youngest person ('y')
*       4. Order them by first name ('f')
*       5. Order them by last name while preserving the order between equal elements ('l')
*       6. Order them by age while preserving the order between equal elements ('a')
*       7. Put all Simpsons first without affecting the general order of persons ('s')
*       8. Compute the total age of all persons ('t')
*       9. Put the last person first, moving all others by one position ('0')
*       10. Determine the fourth oldest person as quickly as possible ('4')
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <random>
#include <string>
#include <vector>

// C++20
//#include <format>
//#include <ranges>


struct Person
{
   std::string firstname;
   std::string lastname;
   int age;
};

std::ostream& operator<<( std::ostream& os, Person const& person )
{
   return os << std::setw(11) << std::left  << person.firstname
             << std::setw(11) << std::left  << person.lastname
             << std::setw(3)  << std::right << person.age;

   // C++20 format solution
   //os << std::format( "{:<11}{:<11}{:>3}", person.firstname, person.lastname, person.age );
   //return os;
}

//Not efficient when passed to an algorithms because of the function pointer
bool is_younger(const Person& lhs, const Person& rhs)
{
    return lhs.age < rhs.age;
}

// This a compiler will optimize and make it inline 
class IsYounger {
public:
    bool operator()(const Person& lhs, const Person& rhs) const // const promises that the call doesn't change this IsYounger object
    {
        return lhs.age < rhs.age;
    }
};

// Global lambda, ODR used, not a wise idea...
// auto const isYounger = [](const Person& lhs, const Person& rhs) {
//     return lhs.age < rhs.age;
// };

template< typename Table >
void print( Table const& table )
{
    for (const auto& person : table) {
        std::cout << person << '\n';
    }
}

template< typename Table >
void random_order( Table& table )
{
    // TODO: Randomize their order ('r')
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(table.begin(), table.end(), g);
}

template< typename Table >
void find_youngest( Table const& table )
{
   // TODO: Find the youngest person ('y')
   auto const pos = std::min_element(table.cbegin(), table.cend(), IsYounger{});

   std::cout << "Youngest person = " << pos->firstname << " " << (*pos).lastname << "\n";
}

template< typename Table >
void order_by_firstname( Table& table )
{
   // TODO: Order them by first name ('f')
   std::sort(table.begin(), table.end(),
       [](const auto& lhs, const auto& rhs) {
           return lhs.firstname < rhs.firstname;
       });
}

template< typename Table >
void order_by_lastname( Table& table )
{
   // TODO: Order them by last name while preserving the order between equal elements ('l')
   std::stable_sort(table.begin(), table.end(),
       [](const auto& lhs, const auto& rhs) {
           return lhs.lastname < rhs.lastname;
       });
}

template< typename Table >
void order_by_age( Table& table )
{
   // TODO: Order them by age while preserving the order between equal elements ('a')
   std::stable_sort(table.begin(), table.end(), IsYounger{});
}

template< typename Table >
void simpsons_first( Table& table )
{
   // TODO: Put all Simpsons first without affecting the general order of persons ('s')
   std::stable_partition(table.begin(), table.end(),
       [](const Person& person) {
           return "Simpson" == person.lastname;
       });
}

template< typename Table >
void compute_total_age( Table const& table )
{
   // TODO: Compute the total age of all persons ('t')
   int const age = std::accumulate(table.cbegin(), table.cend(), int{},
       [](auto accu, const auto& person) {
           return accu + person.age;
       });

   std::cout << "Total age = " << age << "\n";
}

template< typename Table >
void last_to_first( Table& table )
{
   // TODO: Put the last person first, moving all others by one position ('0')
   // std::rotate(table.rbegin(), table.rbegin() + 1, table.rend());
   std::rotate(table.begin(), std::prev(table.end()), table.end());
   //(first, new first element, last)
}

template< typename Table >
void fourth_oldest( Table& table )
{
   // TODO: Determine the fourth oldest person as quickly as possible ('4')
   //       Note that you are allowed to change the order of persons.
   std::nth_element(table.begin(), std::next(table.begin(), 3), table.end(),
       [](const auto& lhs, const auto& rhs) {
           return lhs.age > rhs.age;
       });
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

      case 'f':
         order_by_firstname( table );
         break;

      case 'l':
         order_by_lastname( table );
         break;

      case 'a':
         order_by_age( table );
         break;

      case 's':
         simpsons_first( table );
         break;

      case 't':
         compute_total_age( table );
         break;

      case '0':
         last_to_first( table );
         break;

      case '4':
         fourth_oldest( table );
         break;

      default:
         return EXIT_SUCCESS;
      }

      print( table );
   }

   return EXIT_SUCCESS;
}
