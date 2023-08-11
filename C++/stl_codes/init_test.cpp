// 该程序的目的是为了测试多种初始化变量的方法
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

int main()
{
	string s{};
	string t{'a', 'b', 'c'};
	string d("abc");
	string e = "hello";
	char f[3] = {'a', 'b'};
	char &c = f[0];
	// 此处引用初始化变量，c变量就引用了f数组的第一个元素，c和f[0]里面的数值存放的地址是一样的
	// 如果我们修改c的话，f[0]也会跟着改变
	cout << s << endl;
	cout << t << endl;
	cout << d << endl;
	cout << e << endl;
	cout << f << endl;
	cout << c << endl;
	c = 'c';
	cout << f <<endl;
	return 0;
}
