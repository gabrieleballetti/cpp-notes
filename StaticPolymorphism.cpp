#include <chrono>
#include <iostream>
  
typedef std::chrono::high_resolution_clock Clock;

struct Dimension {
	Dimension(int _X, int _Y)
	{ 
		mX = _X;
		mY = _Y;
	}

	int mX, mY;
};

// Polymorphism is a common standard programming facility where derived objects
// can be used as instances of their base object but where the derived objects
// methods will be invoked, as in this code
class Rectangle {
public:
	virtual void Draw() = 0;
	virtual Dimension GetDimension() = 0; // pure virtual function, makes Rectangle abstract

protected:
	int dimensionX;
	int dimensionY;
};

class Square : public Rectangle {
public:
	void Draw() {}
	Dimension GetDimension()
	{ 
		return Dimension(dimensionX, dimensionY); 
	} 
}; 
  
void staticPolymorphism() 
{ 
	Rectangle* pRectangle = new Square; 
  
	auto then = Clock::now(); 
	for (int i = 0; i < 1000; ++i) 
		pRectangle->Draw(); 
	auto now = Clock::now(); 
  
	std::cout << "Dynamic polymorphism: "
		 << std::chrono::duration_cast<std::chrono::nanoseconds>(now - then).count() 
		 << " nanoseconds" << std::endl; 
} 

// However, in many cases the polymorphic behaviour needed is invariant and can
// be determined at compile time. Then the Curiously Recurring Template Pattern
// (CRTP) can be used to achieve static polymorphism, which is an imitation of
// polymorphism in programming code but which is resolved at compile time and
// thus does away with run-time virtual-table lookups
template <class T>
class Rectangle2 {
public:
	void Draw2()
	{
		// Dispatch call to exact type
		static_cast<T*>(this)->Draw2(); 
	} 
	Dimension GetDimension2() 
	{ 
		// Dispatch call to exact type 
		static_cast<T*>(this)->GetDimension2(); 
	}

protected: 
	int dimensionX, dimensionY; 
}; 
  
class Square2 : public Rectangle2<Square2> { 
public: 
	void Draw2()
	{ 
		// std::cout << "Square2::Draw2() called" << std::endl; 
	} 
	Dimension GetDimension2() 
	{ 
		return Dimension(dimensionX, dimensionY); 
	} 
}; 

void dynamicPolymorphism()
{
    Rectangle2<Square2>* pRectangle = new Square2; 
  
    auto then = Clock::now(); 
    for (int i = 0; i < 1000; ++i) 
        pRectangle->Draw2(); 
    auto now = Clock::now(); 
  
    std::cout << "Static polymorphism: "
         << std::chrono::duration_cast<std::chrono::nanoseconds>(now - then).count() 
         << " nanoseconds" << std::endl; 
}

int main()
{
	staticPolymorphism();
	dynamicPolymorphism();
	return 0;
}

// compiled with 'g++ -std=c++11 StaticPolymorphism.cpp -O3'
// output:
// Time taken: 1842 nanoseconds
// Time taken: 59 nanoseconds
