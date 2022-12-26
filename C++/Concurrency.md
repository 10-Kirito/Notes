





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