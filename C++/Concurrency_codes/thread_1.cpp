#include <string>
#include <thread>
#include <iostream>
using namespace std;

struct func{
	int & i;
	func(int &_i) : i(_i){}

	void operator () ()
	{
		unsigned sum = 0;
		unsigned j;
		for (j = 0 ; j < 1000000 ; ++j) {
			sum += j;
		}
		cout << sum << endl;
	}
};

int main()
{

	int some_local_state = 0;
	func my_func(some_local_state);
	thread my_thread(my_func);
	my_thread.detach();

	return 0;
}
