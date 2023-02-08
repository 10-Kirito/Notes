#include <iostream>
#include <iterator>
#include <utility>
#include <tuple>

class Foo{
	public:
		Foo(std::tuple<int, float>) {
			std::cout << "Foo::Foo(tuple)" << std::endl;
		}
		template<typename... Args>
			Foo(Args... args){
				std::cout << "Foo::Foo(args...)" << std::endl;
			}
};

int main()
{
	std:: tuple<int, float> t(1, 2.22);

	std:: pair<int, Foo> p1(42, t);

	std::pair<int, Foo> p2(std::piecewise_construct, std::make_tuple(42), t);

}
