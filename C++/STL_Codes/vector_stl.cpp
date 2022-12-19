// 该程序的目的是为了测试容器vector的特性
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm> // include sort（）
using namespace std;

template <typename T>
int compare(const void *a,const void *b) {
	const auto &arg1 = *(static_cast<const T*>(a));
    const auto &arg2 = *(static_cast<const T*>(b));
    const auto cmp = arg1 - arg2;
    return cmp < 0 ? -1
        :  cmp > 0 ? +1
        :  0;
}


int main()
{
vector<int> vec;
clock_t timestart = clock();
	for (int i = 0; i < 500000; i++) {
		vec.push_back(rand());
	}
	// 这里需要注意我们需要注意内存是否足够使用，如果空间不足使用的话，我们需要进行捕捉异常并且退出

	cout << "milli-seconds: "<< (clock() - timestart) <<endl;
	cout << "vector.size(): "<< vec.size() << endl;
	cout << "vector.front(): "<< vec.front() <<endl;
	cout << "vector.back(): "<< vec.back() <<endl;
	cout << "vector.data(): "<< vec.data() <<endl;
	cout << "vector.capacity(): "<< vec.capacity() <<endl;
	
int a = 23412;
	// 此处find函数为全局函数，我们使用nvim编写的时候，先写入：：可以看到后面是有提示的
	timestart = clock();
auto pItem = ::find(vec.begin(), vec.end(), a);
	cout << "::find() cost time " << (clock() - timestart) << "ms" <<endl;	
	if(pItem == vec.end())
		cout << "failed to find!!!" <<endl;
	else
		cout << "sucessfully to find target!!!" <<endl;
	timestart = clock();
	sort(vec.begin(),vec.end());
const int*p = static_cast<int*>(bsearch(&a, vec.data(), vec.size(), sizeof(int), compare<int>));
	
	cout << "value " << a;
	(p) ? cout << " found at position " << (p - vec.data()) << '\n'
        : cout << " not found\n";
	cout << "container vector located at the position is "<< vec[p - vec.data()] << endl;
	
	cout << "bsearch() cost "<< (clock() - timestart) << "ms"<<endl;
	return 0;
}
