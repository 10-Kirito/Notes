#include <iostream>

using namespace std;

class A
{
public:
	A() { cout << "Parent constructor"<< endl; }
	virtual ~A() { cout << "Parent destructor"<< endl; }
};

class B : public A
{
public:
	B(){ cout << "Children constructor"<< endl; }
	~B() { cout << "Children destructor"<< endl; }
};

int main()
{
	B * b = new B;
	delete (A *)b;

	return 0;

}
