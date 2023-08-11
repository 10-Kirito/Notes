#include <iostream>
#include <cstddef>	//for size_t

using namespace std;

class alloc{
};

template <class T,class Alloc = alloc,size_t BufSiz = 0>
class deque{
public:
	deque() {cout << "deque" << ' ';}
};

template <class T,class Sequence>
class stack;

template <class T,class Sequence>
bool operator== (const stack<T,Sequence> &x , const stack<T,Sequence> &y);

template <class T,class Sequence>
bool operator< (const stack<T,Sequence> &x , const stack<T,Sequence> &y);


template <class T,class Sequence = deque<T> >
class stack{
	//写成这样是可以的
	friend bool operator== <T> (const stack<T> & , const stack<T> &);
	friend bool operator< <T> (const stack<T> & , const stack<T> &);

	//写成这样也是可以的
	friend bool operator== <T> (const stack & , const stack &);
	friend bool operator< <T> (const stack & , const stack &);

	//写成这样也是可以的
	friend bool operator== <> (const stack & , const stack &);
	friend bool operator< <> (const stack & , const stack &);

	//写成这样不可以
	//friend bool operator== (const stack & , const stack &);
	//friend bool operator< (const stack & , const stack &);
public:
	stack() {cout << "stack" << endl;}
private:
	Sequence c;
};

template <class T,class Sequence>
bool operator== (const stack<T,Sequence> &x , const stack<T,Sequence> &y)
{
	cout << "operator==" << '\t';
	return true;
}

template <class T,class Sequence>
bool operator< (const stack<T,Sequence> &x , const stack<T,Sequence> &y)
{
	cout << "operator<" << '\t';
	return true;
}


int main()
{
	stack<int> x;				//deque stack
	stack<int> y;				//deque stack

	cout << (x == y) << endl;	//operator==	1
	cout << (x < y) << endl;	//operator==	1

	stack<char> y1;				//deque stack
	//cout << (x == y1) << endl;
	//cout << (x < y1) << endl;
}
