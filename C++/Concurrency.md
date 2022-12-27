





# 第二章 线程管理

## 2.1 线程基本操作

我们除了向线程构造函数传递函数名之外：

```c++
void do_some_work();
std::thread my_thread(do_some_work);
```

还可以通过含有函数操作符类型的实例进行构造：

```c++
class background_task
{
public:
	void operator()() const
  {
    do_something();
    do_some_thing_else();
  }
};

background_task f;

std::thread my_thread(f);
```

注意：我们所提供的函数对象会复制到新线程的存储空间中，函数对象的执行和调用全部都会在线程的内存空间中进行。

> 对于这里有一件事情需要我们注意，当我们将函数对象传入到线程构造函数的时候，需要避免“最令人头痛的语法解析”。如果你传递的是一个临时的变量，而不是一个命名之后的变量，C++编译器会将其解析为函数的声明，而不是对类型对象的定义。
>
> 比如说下面这段代码：
>
> ```c++
> #include<thread>
> #include<iostream>
> using namespace std;
> class FUNC{
> private:
> 	int test;  
> public:
>   void operator()() const
>   {
>    		cout << this_thread::get_id() <<endl;
>   }
> };
> 
> int main()
> {
>   	thread my_thread(FUNC());  
> }
> ```
>
> 在编译器看来是长下面这样的：
>
> ```c++
> #include<thread>
> #include<iostream>
> 
> using namespace std;
> class FUNC
> {
>   
>   private: 
>   int test;
>   
>   public: 
>   inline void operator()() const
>   {
>     std::operator<<(std::cout, std::this_thread::get_id()).operator<<(std::endl);
>   } 
>   // inline FUNC() noexcept = default;
> };
> 
> int main()
> {
>   std::thread my_thread(FUNC (*)());
>   return 0;
> }
> ```
>
> 我们可以看到我们传进去的临时变量被编译器识别为一个函数指针（该函数指针指向没有参数并返回FUNC对象的函数）
>
> 我们可以看到编译器将其看作了一个函数，函数的参数是一个函数指针，函数名字为`FUNC`，并且该函数返回一个`std::thread`对象的函数。
>
> ***如何避免这个问题：***
>
> 我们可以像下面这样书写：
>
> ```c++
> std::thread my_thread((FUNC()));  // 1，使用多组括号
> std::thread my_thread{FUNC()};    // 2, 使用统一的初始化语法
> ```
>
> 还有就是，我们使用`Lambda`表达式也可以避免这个问题。

## 2.2  等待线程完成

有的时候，我们需要等待线程来保证线程访问数据的有效性。因为有的时候，在主线程已经退出的情况下，线程函数仍然持有局部变量的引用或者指针。

我们等待线程，通常是使用`join()`函数。

***当我们需要对等待中的线程进行更加灵活的控制的话，***比如说看一下某一个线程是否结束，或者只等待一段时间（超过时间就会判定为超时）。想要做到这些，我们需要使用其他的机制来完成，比如说条件变量`future`。调用`join()`，还可以清理线程相关的内存，这样的话`std::thread`对象将不再与已经完成的线程有任何的关联。这意味着，***我们只可以对一个线程使用一次`join()`，一旦使用过`join()`.`std::thread`对象就不可以再次汇入了***。当对其使用`joinable()`时，将返回`false`.

## 2.3 特殊情况下的等待

所谓特殊情况也就是当主线程运行的时候产生异常的话，而我们处理异常的时候就需要考虑调用`join()`函数，以防止线程被异常处理程序所终止，常见的操作像下面所写：

```c++
struct func{
  int &i;
  func(int &i_) : i(i_) {}
  void operator ()()
  {
    for(unsigned j = 0; j < 1000000 ; ++j)
      do_something(i); // 存在访问隐患，空引用
  }
}

void f()
{
  int some_local_state=0;
  fun my_func(some_local_state);
  std::thread t(my_func);
  
  try
  {
    do_something_in_current_thread();
  }
  catch(···)
  {
    t.join(); // 1
    throw;
  }
  t.join(); //2
}
```

我们可以看到上面的程序中如果主线程抛出了异常，就会先调用`join()`，来避免线程被异常所终止。

这种方式看起来感觉会产生代码的冗余，或者看着特别的不爽，下面还有另外一种方法：***资源获取即初始化方式（RAII，Resource Acquisition is Initialization）***,我们可以将线程封装成一个类，然后在析构函数中使用`join()`。

```c++
class thread_guard
{
  std::thread &t;
public:
  explicit thread_guard(std::thread & t_) : t(t_) {}
  // 这里加上关键字explicit是因为要告诉编译器拒绝隐式转换
  ~thread_guard(){
    if(t.joinable())  // 新的处理方案
    {
      t.join();
    }
  }
  thread_guard(thread_guard const&) = delete;
  thread_guard& operator=(thread_guard const &) = delete;
  // 直接对对象进行拷贝和赋值是很危险的
}；
  
struct func;

void f()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  // 这样的话，即使do_something_in_current_thread中抛出异常，这个线程的析构函数依旧会被调用
 	// 我们就不需要再手动的在各种情况下去调用`join`函数
  do_something_in_current_thread();
  
}
```

## 2.4 传递参数问题

```c++
#include<thread>
#include<iostream>
#include<string>
void  f(int i, std::string const & s)
{
  std::cout<< i << s;
}


int main()
{
  std::thread t(f,3,"hello");
  t.join();
}
```

像这样，我们传递参数时十分简单的，只需要将这些参数作为`std::thread`构造函数的附加参数即可。***需要注意的是，这些参数会拷贝至新线程的内存空间中，即使函数中的参数是引用的形式，拷贝操作也是会执行的.***

我们可以参看一下代码：

```c++
#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>

using namespace std;

class Test
{
public:
        Test(int val) : _val(val) { cout <<this_thread::get_id()<< "Test::Test()" << endl; }

        Test(const Test& other) : _val(other._val) { cout <<this_thread::get_id()<< "Test::Test(const Test&)" << endl; }
        ~Test() { cout <<this_thread::get_id()<< "Test::~Test()" << endl; }
        Test& operator=(const Test& other) { this->_val = other._val; cout <<this_thread::get_id()<< "Test::operator=(const Test& other)" << endl; return *this; }
private:
        int _val;
};

void fun(int c, Test t)
{
        cout <<endl<< this_thread::get_id()<<"I'm working."<<endl;
}
int main()
{
        Test test(3);
        cout<< this_thread::get_id();
        thread t(fun, 2, test);

        t.join();
}
```

上面代码的执行结果为：

```c++
1Test::Test()
11Test::Test(const Test&)
1Test::Test(const Test&)
1Test::~Test()
// 以上输出结果是因为在编译器看来，我们写的Test test(6)实际上是这样的：
// Test test = Test(3);
// 即先构造出一个临时的对象，然后利用初始拷贝构造
2Test::Test(const Test&)
2I'm working.
2Test::~Test()
2Test::~Test()
// 从以上部分我们可以看到我们往线程里面传参之后，线程的构造函数会自动进行copy构造
1Test::~Test()
```

无论我们传进去什么值，无论是引用还是什么，`std::thread`的构造函数是并不知情的，构造函数无视函数参数类型，盲目的拷贝已经提供的变量。***而且内部代码会将拷贝的参数以右值的方式进行传递***，这就会导致一个问题，如果说我们第20行的代码修改为下面的样子：

```c++
void fun(int c, Test &t)
```

即加上一个引用，那么在线程中就以一个右值来调用该函数，但是该函数的参数是引用（不是右值），***所以说这里会出现编译错误。***

解决方法其实也很简单，对于熟悉`std::bind`的开发者来讲，很简单：我们可以使用`std::ref`将参数转化为引用的形式：

```C++
std::thread t(fun, 2, std::ref(t));
// 这样的话，对应的函数就会收到t的引用，并非数据的简单拷贝
```

`std::thread`构造函数和`std::bind`的操作在标准库中是以相同的机制进行定义的，比如说我们也可以传递一个成员函数指针作为线程函数，并提供一个合适的对象指针作为第一个参数：***bind函数就是这样来绑定参数的。***

```c++
class X
{
public:
  void do_length_work();
};

X my_x;

std::thread t(&X::do_length_work, &my_x);
// 这里传递的第一个参数就是所谓的this指针，我们知道实际上对象调用成员函数就是通过传递指针来实现的
```

## 2.5 转移所有权

***`std::uniqoe_ptr`和`std::thread`都是可移动，但是其不是可以赋值的。***

```c++
void some_function();
void some_other_function();

std::thread t1(some_function);
std::thread t2 = std::move(t1);
t1 = std::thread(some_other_function);
std::thread t3;
t3 = std::move(t2);
t1 = std::move(t3);  // 此处会报错，因为t1已经有一个关联的线程了，这里系统会直接调用std::terminal终止程序运行
```

![image-20221227134358817](./pictures/37.png)

# 第三章 共享数据

## 3.2 使用互斥量

保护共享数据最基本的方式，是使用C++标准库提供的互斥量。

***关键就是访问共享数据之前，将数据锁住，在访问结束之后，再将数据解锁。线程库需要保证，当线程使用互斥量锁住共享数据的时候，其他的线程都必须等到之前的那个线程对数据进行解锁之后，才能进行访问数据。***

我们可以通过实例化`std::mutex`创建互斥量实例，其成员函数`lock()`可以对互斥量上锁，`unlock()`为解锁。不过我们一般不推荐直接去调用成员函数，调用成员函数意味着，我们必须在每一个函数的出口都去调用`unlock()`（包含异常的情况）。这就有可能导致我们程序员忘记去调用，程序员的记忆一般都是”很短暂的“。

所以说C++标准库为互斥量提供了RAII模板类`std::lock_guard`，在构造函数的时候，就可以提供已锁的互斥量，并且在析构的时候进行解锁的操作，即将`lock()`和`unlock()`封装到了这个类当中。

下面看一下实例：

```c++
// 在本程序中，我们创建20个进程，每一个进程都对sum累加100万次，最后将结果输出

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;
int sum = 0;
void func()
{
        for (int i = 1 ; i <= 1000000; i++) {

                sum++;
        }
}
int main()
{
        vector<thread> threads;
        for(unsigned i = 0; i < 20; i++){
                threads.emplace_back(func);
        }
        for (auto & entry : threads) {
                entry.join();
        }
        cout << sum <<endl;
        return 0;
}
```

我们运行之后，结果如下图所示：

<img src=".\pictures\34.png" alt="34" style="zoom:80%;" />

***我们可以看到明显出现了竞争的现象，而且每一次竞争的结果还不一样。***

下面我们使用互斥量重复上面过程：

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

int sum = 0;

mutex some_mutex;
void func()
{
        for (int i = 1 ; i <= 1000000; i++) {
                some_mutex.lock();
                sum++;
                some_mutex.unlock();
        }
}
int main()
{
        vector<thread> threads;
        for(unsigned i = 0; i < 20; i++){
                threads.emplace_back(func);
        }
        for (auto & entry : threads) {
                entry.join();
        }
        cout << sum <<endl;
        return 0;
}
```

执行结果如下图所示：

<img src=".\pictures\35.png" alt="34" style="zoom:80%;" />

接下来我们使用标准库中封装好的模板类`std::lock_guard`.

```C++
// 在本程序中，我们来实际使用互斥量
// 使用RAII模板类std::lock_guard来进行测试

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;
int sum = 0;
mutex some_mutex;
void func()
{
        for (int i = 1 ; i <= 1000000; i++) {
                lock_guard<mutex> guard(some_mutex);
                sum++;
        }
}
int main()
{
        vector<thread> threads;
        for(unsigned i = 0; i < 20; i++){
                threads.emplace_back(func);
        }
        for (auto & entry : threads) {
                entry.join();
        }
        cout << sum <<endl;
        return 0;
}
```

执行结果如下：

<img src=".\pictures\36.png" alt="34" style="zoom:80%;" />

很明显，后者使用起来更加的方便，因为我们不需要考虑各种情况如何调用`unlock()`的情况，我们比较省心。

> C++17中，添加了一种新特性，称为模板参数推导，就是我们在实例化模板的时候，不需要指定变量类型，我们只需要传进去值即可，其会自动推导出变量的类型，所以说上述的锁的代码可以简化为：
>
> `lock_guard guard(some_mutex);`
>
> 具体的模板参数推导我们可以直接交给C++17的编译器完成。

***注意：***在上述的代码中，我们是直接使用全局变量，这没有问题，但是大部分情况下，我们一般是将互斥量和需要保护的数据封装在同一个类当中，而不是定义为全局变量，遵循面向对象设计的准则。

# 第四章 同步操作