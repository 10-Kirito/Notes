// 该程序用来测试容器list的一些特性
#include <exception>
#include <iostream>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	list<string> lis;
	char buf[10];
	clock_t timestart = clock();
	for (long i = 0; i < 1000000; i++) {
		try {
			snprintf(buf, 10, "%d", rand());
			lis.push_back(string(buf));
		} catch (exception& p) {
			cout << "i="<< i << " " << p.what() << endl;
			abort();
		}
	}
	cout << "the initiation cost time : "<< (clock() - timestart)<<"ms"<<endl;
	cout << "the max-size of list is: " << lis.max_size() <<endl;
	timestart = clock();
	lis.sort();
	cout << "sort() cost time : " << (clock() - timestart) <<"ms"<<endl;

	return 0;
}
