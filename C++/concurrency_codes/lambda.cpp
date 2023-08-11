#include <iostream>

int main()
{
	int v1=42;
	auto f = [v1]mutable{v1 = 43; return v1;};
	f();	
	std::cout<<v1;
	

}
