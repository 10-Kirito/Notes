#include <iostream>
#include <utility>

// 如果我们想要将pair按照执行格式输出，并且实现泛型的话，我们就需要类似于下面的书写方式
template<typename T1, typename T2>
std::ostream& operator << (std::ostream & strm, const std::pair<T1, T2> &p)
{
	return strm << "[" << p.first << ", " << p.second << "]";
}

int main()
{
	std::pair<int, double> p(1,1.0);

	std:: cout << p << std::endl; 
}
