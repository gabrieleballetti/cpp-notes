#include <iostream>
#include <string>
#include <map>

// needs >=C++11

int main ()
{
	std::map<std::string,int> mymap = {
				{ "alpha", 0 },
				{ "beta", 0 },
				{ "gamma", 0 } };

	mymap.at("alpha") = 30;
	mymap.at("beta") = 20;
	mymap.at("gamma") = 10;

	// this returns error
	//std::cout << mymap.at("delta") << std::endl;

	// this inserts a new element with that key and returns a reference to its mapped value (uses default constructor)
	std::cout << mymap["delta"] << std::endl;

	for (auto& x: mymap) {
		std::cout << x.first << ": " << x.second << std::endl;
	}

	return 0;
}