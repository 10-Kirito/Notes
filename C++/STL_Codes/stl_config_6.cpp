#include <iostream>
#include <utility>

using namespace std;

class alloc{};

template<class T, class Alloc = alloc>
class vector {
public:
	void swap(vector<T, Alloc> &) {cout << "swap()" << endl;}
};


int main()
{
	vector<int> x,y;
	x.swap(y);
}
