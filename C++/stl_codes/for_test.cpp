// 测试C++11 for循环新型写法
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec{1,2,3,4,5,6};

	for(auto elem : vec)
		cout << elem << " ";

	cout << endl;
	vector<int>::iterator ite = vec.begin();
	for(;ite != vec.end();++ite)
		cout << *ite << " ";
	return 0;
}
