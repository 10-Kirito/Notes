#include <iostream>

using namespace std;

int main()
{
	int temp[10] = {0,0,0,0,0,0,0,0,0,0};

	int i = 0;

	while (cin.good()) {
		cin >> temp[i];
		i++;
	}

	for (int a : temp) {
		cout << a << " ";
	}


	return 0;
}
