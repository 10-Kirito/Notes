// 测试nullptr和NULL之间的区别，并且推荐使用nullptr

#include <iostream>
#include <cstdio>
using namespace std;

void func(int a)
{
	cout << "Hello, world!"<<endl;
}

void func(int *p)
{
	cout << "This is pointer" << endl;
}

int main()
{
	func(nullptr);
}
