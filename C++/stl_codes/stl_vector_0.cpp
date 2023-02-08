#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// 第一种初始化vector容器的方式, 传入迭代器分别指向一组数据的头和尾
	int a[10] = {0,1,2,3,4,5,6,7,8,9};

	vector<int> vec0(a, a + 10);
	for(auto test : vec0)
		cout<< test << " ";
	cout << endl << "the maxest length of vec0 is " << vec0.capacity() << endl;
	// 第二种初始化vector容器的方式，
	//
	vector<int> vec1(10);
	for(auto test : a)
		vec1.push_back(test);
	for(auto test :vec1)
		cout << test <<" ";
	cout << endl << "the maxest length of vec1 is " << vec1.capacity() << endl;

	vec1.emplace_back(2);

	cout << endl << "the maxest length of vec1 is " << vec1.capacity() << endl;
	
	// 第三种初始化vector的方式，利用新特性初始化列表进行初始化
	vector<int> vec2({1,2,3,4,4,6,7});
	for(auto test : vec2)
		cout << test << " ";
	cout << endl;
	vector<int> vec3 = {1,2,3,4,5};
	for(auto test : vec3)
		cout << test << " ";
	// 第四种初始化，默认构造
	vector<int> vec4;
	cout << endl << vec4.capacity() << endl;



}
