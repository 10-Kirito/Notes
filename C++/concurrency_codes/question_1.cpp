#include <iostream>

using namespace std;

class Test
{
public:
	Test(int val) : _val(val) { cout << "Test::Test()" << endl; }
	Test(const Test& other) : _val(other._val) { cout << "Test::Test(const Test&)" << endl; }
	~Test() { cout << "Test::~Test()" << endl; }
	Test& operator=(const Test& other) { this->_val = other._val; cout << "Test::operator=(const Test& other)" << endl; return *this; }
private:
	int _val;
};

int main()
{
	Test test(5);

	auto func_value = [=]() mutable { test = Test(6); };
	auto func_reference = [&]() mutable { test = Test(6); };

	func_value();
	func_reference();
}
