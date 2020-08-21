#include <iostream>
#include <vector>
#include <unordered_map>

// compiles with g++ -std=c++17 Iterators.cpp 
// basic examples of iterators

int main()
{
    std::vector<int> values = { 1, 2, 3, 4, 5 };

    // the basic way
    for (int i = 0; i < values.size(); i++)
    {
        std::cout << values[i] << std::endl;
    }

    // ranged-base for look >=C++11
    for (int value : values)
    {
        std::cout << value << std::endl;
    }

    // using std::vector<int>::iterator
    for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++)
    {
        std::cout << *it << std::endl; // the iterator is dereferenced as if it was a pointer (already implemented, in this case)
    }

    // a more interesting setting: unordered maps
    using ScoreMap = std::unordered_map<std::string, int>;
    ScoreMap map;
    map["Ananas"] = 5;
    map["Banana"] = 2;

    // in this case 
    for (ScoreMap::const_iterator it = map.begin(); it != map.end(); it++)
    {
        auto& key = it->first;
        auto& value = it-> second;

        std::cout << key << " = " << value << std::endl;
    }

    for (auto kv : map)
    {
        auto& key = kv.first;
        auto& value = kv.second;

        std::cout << key << " = " << value << std::endl;
    }

    // ... or with structure binding >=C++17
    for (auto [key, value] : map)
    {
        std::cout << key << " = " << value << std::endl;
    } 
}