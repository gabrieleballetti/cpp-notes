// compile with gcc -std=c++2a -O3

#include <utility>
#include <string>
#include <type_traits>

// THE OLD WAY: inherit with conditional 
/* 
template<typename Type>
struct Optional_nontrivial
{
	~Optional_nontrivial()
	{
		static_cast<Type *>(this)->data.~Contained();
	}
};

struct Optional_trivial {

};

template<typename Contained>
struct Optional : std::conditional<std::is_trivially_destructible_v<Contained>, Optional_trivial, Optional_nontrivial<Optional<Contained>>>
{
	union { Contained data; };
	bool initialized = false;

	constexpr Optional &operator=(Contained &&data)
	{
		this->data = std::move(data);
		initialized = true;
		return *this;
	}
};
*/

// THE C++20 WAY: multiple destructors
template<typename Contained>
struct Optional
{
	union { Contained data; };
	bool initialized = false;

	constexpr Optional &operator=(Contained &&data)
	{
		this->data = std::move(data);
		initialized = true;
		return *this;
	}

	constexpr ~Optional() requires(!std::is_trivially_destructible_v<Contained>)
	{
		if (initialized)
		{
			data.~Contained();
		}
	}

	constexpr ~Optional() = default;
};


int main()
{
	Optional<int> obj;
	obj = 5;

	static_assert(std::is_trivially_destructible_v<Optional<int>>);
	static_assert(!std::is_trivially_destructible_v<Optional<std::string>>);
}



