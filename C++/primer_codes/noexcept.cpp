#include <iostream>

using namespace std;

void func_not_throw() noexcept(false){
	throw 1;
}

int main()
{
	try{
		func_not_throw();
	}catch(int){
		cout << "catch int"<<endl;
	}
	return 0;
}
