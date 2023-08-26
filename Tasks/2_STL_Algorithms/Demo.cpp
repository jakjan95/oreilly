#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<double> v { 1.1, 2.2, 3.3, 4.4 };
    const double result = std::accumulate(std::begin(v), std::end(v), double {});

    std::cout << "\nresult = " << result << "\n\n";

    return 0;
}

/*
Function object:
class Widget {
public:
    void operator()(int i) const
    {
        std::cout << "Widget::operator() for int: " << i << '\n';
    }

    void operator()(double d)
    {
        std::cout << "Widget::operator() for double: " << d << '\n';
    }
};

int main()
{

    const Widget w; // Function object

    w(42);
    w(42.1); // will not work because the operator for a double is not const


    return 0;
}


*/

/*
Loops introduction:
std::vector<int> v { 3, 1, 4, 2, 5 };

//index-based for loop
for (size_t i = 0U; i < v.size(); ++i) {
    std::cout << ' ' << v[i];
}
std::cout << '\n';

//iterator-based for loop
for (auto iter = v.begin(); iter != v.end(); ++iter) {
    std::cout << ' ' << *iter;
}
std::cout << '\n';

std::sort(v.begin(), v.end());

//range-based for loop
for (int i : v) {
    std::cout << ' ' << i;
}
std::cout << '\n';
*/
