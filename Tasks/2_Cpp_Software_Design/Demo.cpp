#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <variant>
#include <vector>
#include <algorithm>
#include <memory>

namespace std {
template <typename T>
class allocator;

//ODR : One Definition Rule -> we introduced violation of ODR
template <typename T, typename Allocator = std::allocator<T>>
class vector;
}

int main()
{
    return EXIT_SUCCESS;
}

/*
Prototype example, with covariant return type...
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <variant>
#include <vector>
#include <algorithm>
#include <memory>

class Animal {
public:
    virtual ~Animal() = default;

    // virtual Animal* clone() const = 0;
    // virtual std::unique_ptr<Animal> clone() const=0;
    std::unique_ptr<Animal> clone() const { std::cout<<1<<'\n'; return std::unique_ptr<Animal>(do_clone()); }

private:
    virtual Animal* do_clone() const = 0;
};

class Sheep : public Animal {
public:
    // virtual Sheep* clone() const override { return new Sheep(*this); } // Covariant return type -> we fulfill the interface :) (do not do that->cpp98)
    // virtual std::unique_ptr<Animal> clone() const override { return std::make_unique<Sheep>(*this); } // For unique_ptr covariant return type doesn't work need to use the base type
    std::unique_ptr<Sheep> clone() const { std::cout<<2<<'\n'; return std::unique_ptr<Sheep>(do_clone()); } //This one is not working... invalid covariant return type.....

private:
    Sheep* do_clone() const override { return new Sheep(*this); }
};

int main()
{
    std::unique_ptr<Animal> const dolly = std::make_unique<Sheep>();
    auto dolly2 = dolly->clone();

    std::unique_ptr<Sheep> const lolly = std::make_unique<Sheep>();
    auto lolly2 = lolly->clone();


    return EXIT_SUCCESS;
}
*/


/*
Function ptrs:
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <variant>
#include <vector>

// typedef void (*FunctionPointer)(int); // old syntax much more messy than using an alias
using FunctionPointer = void (*)(int); // a function pointer to a function that takes an int and returns a void
//Virtual functions are functions pointers stored in a vtable
void foo(int i)
{
    std::cout << "foo: " << i << "\n";
}

void bar(int);

int main()
{
    std::function<void(int)> f; // C++11 it is like a function poitner but can hold anything that is callable like a lambda

    f = [](int i) { std::cout << "lambda: " << i << "\n"; };
    f(1);

    auto g = f;

    f = foo;
    f(2);
    g(3);

    return EXIT_SUCCESS;
}

*/

/*
Strategy example:
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <variant>
#include <vector>

int main()
{
    std::vector<int> v { 1, 2, 3, 4, 5 };

    const int result = std::accumulate(begin(v), end(v), 1, std::multiplies {}); //Strategy -> dependency injection :) static polimorphism, strategy is one of the most centralized pattern we have :)
    std::cout << "\n result = " << result << "\n\n";

    return EXIT_SUCCESS;
}
*/

/*
visitor demo:

#include <cstdlib>
#include <iostream>
#include <string>
#include <variant>

struct Print {
    void operator()(int value) const { std::cout << "int: " << value << '\n'; }
    void operator()(double value) const { std::cout << "double: " << value << '\n'; }
    void operator()(const std::string& value) const { std::cout << "std::string: " << value << '\n'; }
};

int main()
{
    std::variant<int, double, std::string> v {}; // C++17 -> runtime dynamic polymorphism
    v = 42;
    v = 3.14;
    v = "O'Reilly";
    // v=43;

    // int i=std::get<int>(v); // if not storing int then execption
    // int* pi = std::get_if<int>(&v);

    std::cout << "Using of Print class:\n";
    std::visit(Print {}, v);

    std::cout << "Using of lambda:\n";
    std::visit([](const auto& value) {
        std::cout << value << '\n';
    },
        v);

    return EXIT_SUCCESS;
}
*/
