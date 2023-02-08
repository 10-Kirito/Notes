#include <array>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ASIZE 500000
using namespace std;

long get_a_target_long()
{
	long target = 0;
	cout << "target (0 ~ "<< RAND_MAX <<"): ";
	cout << target;
	return target;
}

string get_a_target_string()
{
	long target = 0;
	char buf[10];

	cout << "target (0~" << RAND_MAX <<"): ";
	cin >> target;
	snprintf(buf, 10, "%d", target);
	return string(buf);
}

int compareLongs(const void* a,const void* b)
{
	return (*(long *)a - *(long *)b);
}

int compareStrings(const void *a,const void *b)
{
	if(*(string *)a > *(string *)b)
		return 1;
	else if (*(string*)a < *(string *)b)
		return -1;
	else
		return 0;
}

int main()
{
	cout << "test_array()\n";
	array<long,ASIZE> c;
	clock_t timestart = clock();
	for(auto &elem : c)
		elem = rand();
	cout << "milli-seconds : "<< (clock() - timestart) <<endl;
	cout << "array-size() : "<< c.size() <<endl;
	cout << "array-front() : "<< c.front() <<endl;
	cout << "array-back() : "<< c.back() <<endl;
	cout << "array-data's address : "<< c.data() <<endl;


	return 0;
}
