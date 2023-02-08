// 本代码的目的是测试函数指针的一些写法

#include <iostream>
using namespace std;

typedef int(FUNC)(int, int);
typedef int(*FUNC_P)(int, int);

int fun(int a, int b)
{
	cout << "Hello, world!" << endl;
	return 0;
}

int main()
{

	// 上面的typedef只是声明了一个函数类型和一个函数指针类型
	// 第一种方式： 
	FUNC *fp = nullptr;
	fp = fun;
	fp(1,2);
	// 第二种方式：
	FUNC_P fp1 = nullptr;
	fp1 = fun;
	fp1(3,4);
	// 第三种方式：直接通过指针类型创建，不使用typedef预定义
	int(*fp2)(int, int) = nullptr;
	fp2 = fun;
	fp2(1,2);



}
