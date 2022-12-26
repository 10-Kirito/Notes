#include<iostream>
#include<string>
int main()
{
	std::string test;
  	auto f = [&test]{ test = "test";};
  	f();
  	std::cout << test;

}
