#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>


using namespace std;

class Test
{
public:
        Test(int val) : _val(val) { cout <<this_thread::get_id()<< "Test::Test()" << endl; }

        Test(const Test& other) : _val(other._val) { cout <<this_thread::get_id()<< "Test::Test(const Test&)" << endl; }
        ~Test() { cout <<this_thread::get_id()<< "Test::~Test()" << endl; }
        Test& operator=(const Test& other) { this->_val = other._val; cout <<this_thread::get_id()<< "Test::operator=(const Test& other)" << endl; return *this; }
private:
        int _val;
};

void fun(int c, Test t)
{
        cout <<endl<< this_thread::get_id()<<"I'm working."<<endl;
}
int main()
{
        Test test(3);
        cout<< this_thread::get_id();
        thread t(fun, 2, test);

        t.join();
}
