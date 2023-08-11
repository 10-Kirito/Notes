// 该程序的目的是为了测试如果我们给一个已经关联线程的对象继续关联对象，系统会直接调用std::terminal来终止程序的运行
//
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>

void Fun(){
	std::cout<< "I'm Func"<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "Hello, Thread1"<<std::endl;
}

void Fun1(){
	std::cout<< "I'm Fun1"<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout<< "Hello, Thread2"<<std::endl;
}

int main()
{
	std::thread t1(Fun);

	std::thread t2(Fun1);

	t1 = std::move(t2);

	t1.join();
	t2.join();
	return 0;
}
