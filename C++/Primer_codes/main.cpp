#include <iostream>
#include <string>
using namespace std;


int main()
{
	string s1 = "Hello, ";
	string s2 = "world! ";

	const string &s3 = s1 + s2;


	cout << s3 << endl;


	return 0;
}
