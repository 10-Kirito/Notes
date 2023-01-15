// 程序的目的是为了测试移动构造函数加上noexcept声明和不加上有什么区别
// 结论：
// 如果你不加上noexcept声明的话，在移动构造函数不能被调用，此时程序会去调用拷贝构造函数
// 这是为什么呢？
// 1. 因为移动构造函数执行的是Strong Exception Guarantee, 发生异常的时候需要还原，也就是说你调用它之前是什么样子，抛出异常之后你就得恢复成什么样子。
// 2. 但是对于移动构造函数来讲发生异常的话是很难恢复到原来的样子的，如果在恢复移动的时候发生异常了呢？鉴于这些原因编译器只会执行那些声明为不会发生异常的移动构造函数
//3. 但是复制构造函数就不一样了，其发生异常的时候直接去调用它的析构函数就行了
#include <iostream>

#include <ostream>
#include <vector>

using namespace std;

class A{
	public:
		A(int value){
		}

		A(const A &other){
			cout << "copy constructor"<<endl;
		}

		A(A && other) noexcept {
			cout << "move constructor"<<endl;
		}
};

int main()
{
	std::vector<A> a;
	a.emplace_back(1);
	a.emplace_back(2);

	return 0;

}
