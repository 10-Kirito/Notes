#include <iostream>
#include <utility>

int main()
{
	typedef std::pair<int, double> IntDoublePair;

	IntDoublePair p(1,2.0);

	int a = std::get<0>(p);
	double b = std::get<1>(p);

	int size = std::tuple_size<IntDoublePair>::value;

	std::tuple_element<0, IntDoublePair>::type c = 0;
	
	std::cout << "pair的第一个元素的值为：" << a << "pair的第二个元素的值为：" << b << std::endl;

	std::cout << "pair的size为：" << size << std::endl;
	std::cout << "测试获得pair的元素类型：" << c << std::endl;
}
