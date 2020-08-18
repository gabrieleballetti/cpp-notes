#include <string>

enum struct Values
{
    value1 = 1,
    value2 = 2
};

// The C++11 way 
/*
std::string to_string(const Values v)
{
    switch (v)
    {
        case Values::value1:
            return "value1";
        case Values::value2:
            return "value2";
    }

    return "unknown value";
}
*/

// The C++20 way
// with the gpp 10.2.0 command 'cc -std=c++2a -O3' does not seem to compile yet
std::string to_string(const Values v)
{
    using enum Values;

    switch (v)
    {
        case value1:
            return "value1";
        case value2:
            return "value2";
    }

    return "unknown value";
}

// it can also be used in namespaces or classes/structs
namespace NS
{
    using enum Values;
}

struct S
{
    using enum Values;
    Values current_value = value1;
};

int main()
{
    auto val = NS::value1;
}