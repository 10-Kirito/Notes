// 在本程序中，我们来实际使用互斥量
// 使用RAII模板类std::lock_guard来进行测试

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

int sum = 0;

mutex some_mutex;
void func()
{
	for (int i = 1 ; i <= 1000000; i++) {
		lock_guard<mutex> guard(some_mutex);
		sum++;
	}
}


int main()
{
	vector<thread> threads;

	for(unsigned i = 0; i < 20; i++){
		threads.emplace_back(func);
	}
	for (auto & entry : threads) {
		entry.join();
	}

	cout << sum <<endl;

	return 0;
}
