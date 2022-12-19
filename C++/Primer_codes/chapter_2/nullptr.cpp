#include <iostream>
#include <cstdlib>
using namespace std;

class Myclass
{
public:
	void printf(char *)
	{
		cout << "This is char\n" << endl;
	}
	void printf(int)
	{
		cout << "This is int\n" << endl;
	}

};

int main(int argc,char **argv)
{
	Myclass a;
	a.printf(NULL);
	a.printf(nullptr);
	return 0;
}
