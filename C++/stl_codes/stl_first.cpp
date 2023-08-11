#include <memory>
#include <ostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main()
{
	int ia[6] = {27, 210, 12, 47, 109, 83};
	vector<int,allocator<int>> vi(ia,ia+6);
	cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));
	cout << endl << vi.size();
	cout << endl << sizeof(ia);
	vi.push_back(4);
	cout <<endl;
	cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));
	cout << endl << sizeof(vi);

	cout <<endl;
	for (int i = 0; i < vi.size(); i++) {
		cout << vi[i]<<endl;
	}
	return 0;
}
