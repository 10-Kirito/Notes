// 该份代码是为了测试书上的话：
// 我们传递的函数对象都会复制到新线程的存储空间中，函数对象的执行和调用都在线程的内存空间中进行
//
#include <chrono>
#include <ostream>
#include <thread>
#include <iostream>

using namespace std;

class FUNC{
public:
	void operator()() const
	{
		this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << this_thread::get_id()<<endl;
	}

};

int main()
{
	FUNC f;
	thread my_thread((FUNC()));
	my_thread.detach();
	this_thread::sleep_for(std::chrono::milliseconds(20));
}


