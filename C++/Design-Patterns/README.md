# Design-Patterns Learning

# 1. Singleton

## 1.1 Introduction

单例模式是设计模式的一种，其特点是只提供唯一一个类的实例，具有全局变量的特点，在任何位置都可以通过接口获取到那个唯一的实例。

运用的场景有：

- **资源管理类**：例如数据库连接池、线程池等，这些资源通常只需要一个实例来管理，使用单例模式可以确保全局只有一个资源管理实例，并提供全局访问点；
- **配置信息类**：例如全局配置信息、日志配置信息等，这些配置信息通常只需要在程序启动时加载一次，并在整个程序中共享使用，适合使用单例模式；
- **日志类**：日志记录是大多数应用程序的常见需求，为了确保日志的一致性和避免多个日志实例造成的冲突，通常会使用单例模式来创建日志类；
- **计数器类**：例如全局计数器、唯一编号生成器等，这些计数器类需要确保在整个程序中只有一个实例，并且能够提供全局唯一的计数功能；
- **缓存类**：例如全局缓存、数据缓存等，这些缓存通常需要全局唯一的实例来管理缓存数据，使用单例模式可以很方便地实现；
- **GUI应用程序中的控制类**：例如全局窗口管理器、对话框管理器等，这些控制类需要全局唯一的实例来管理 GUI 元素，使用单例模式可以确保全局的 GUI 元素管理一致性；

## 1.2 Implement

### 1.2.1 懒汉模式(Implement_1)(最帅)

***Points:***

- 全局只有一个实例：`static`特性，同时禁止用户自己声明并定义实例（将构造函数以及复制构造函数，赋值函数设置为`private`或者`delete`）;
- 线程安全;
- 禁止赋值与拷贝；
- 用户通过实例接口获取实例，使用`static`类成员变量；

***Codes:***

```C++
#include<iostream>

// version1:
class Singleton {
private:
    Singleton(){
        std::cout << "constructor called" << std::endl;
    }
    // ban copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // the only instance
    static Singleton* instance;
public:
    ~Singleton() {
        std::cout << "destrcutor called" << std::endl;
    }

    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
}
```

但是这样写的话会导致一些问题：

- ***线程安全的问题：***当多线程获取单例的时候有可能发生竞态条件：第一个线程在if当中判断`instance`是`nullptr`,于是开始实例化单例；同时第二个线程也尝试获取单例，这个时候判断`instance`也是`nullptr`，这样就会导致实例化出来两个对象，***解决办法：加锁***。
- ***内存泄漏：***注意到类当中只负责`new`出对象，却没有负责`delete`对象，因此只有构造函数可以被调用，析构函数却没有调用，因此会导致内存泄漏，***解决办法：共享指针。***

***Codes:***

```C++
class Singleton {
private:
  typedef std::shared_ptr<Singleton> SingletonPtr;
  Singleton() { std::cout << "constructor called" << std::endl; }
  // ban copy constructor and assignment operator
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;
  // the only instance
  static SingletonPtr instance;
  static std::once_flag flag;

public:
  ~Singleton() { std::cout << "destrcutor called" << std::endl; }

  static SingletonPtr getInstance() {
    std::call_once(
        flag, []() { instance = std::shared_ptr<Singleton>(new Singleton); });
    return instance;
  }
};

// initialize static member
Singleton::SingletonPtr Singleton::instance = nullptr;
std::once_flag Singleton::flag;

int main() {
  Singleton *s1 = Singleton::getInstance().get();
  Singleton *s2 = Singleton::getInstance().get();
}
```

我这里没有采用锁来保证同一时间只会有一个线程执行相应的代码，而是利用C++当中的一个新的特性：`std::call_once`.

```C++
template< class Callable, class... Args >
void call_once( std::once_flag& flag, Callable&& f, Args&&... args );
```

该函数会保证可调用对象f只会被调用一次，即使该函数被多个线程同时调用。

### 1.2.2 懒汉模式(Implement_2)(最优雅)

> If control enters the declaration concurrently while the variable is being initialized, the concurrent execution shall wait for completion of the initialization.
> 如果当变量在初始化的时候，并发同时进入声明语句，并发线程将会阻塞等待初始化结束。

```C++
class Singleton2 {
public:
  ~Singleton2() {}
  Singleton2(const Singleton2 &) = delete;
  Singleton2 &operator=(const Singleton2 &) = delete;
  
  static Singleton2 &get_instance() {
    static Singleton2 instance;
    return instance;
  }

private:
  Singleton2() {}
};
```

### 1.2.3 恶汉模式(Implement_3)(还行一般)

指的是单例实例在程序运行的时候被立即执行初始化。

***Codes:***

```C++
class Singleton
{
private:
	static Singleton instance;
private:
	Singleton();
	~Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
public:
	static Singleton& getInstance() {
		return instance;
	}
}

// initialize defaultly
Singleton Singleton::instance;
```

由于在`main`函数之前初始化，所以说没有线程安全的问题。

## 1.3 Using template to implement many Singleton

在某些情况下，我们的系统当中可能会有多个单例，如果都按照该种方法的话，实际上是一种重复，所以我们可以采用模板技术或者继承的方法来实例话对应的单例。

```C++
#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
template <typename T> class SingletonTemplte {
public:
  static T &get_instance() {
    static T instance;
    return instance;
  }

  virtual ~SingletonTemplte() {
    std::cout << "basic destructor called" << std::endl;
  }

  SingletonTemplte(const SingletonTemplte &) = delete;
  SingletonTemplte &operator=(const SingletonTemplte &) = delete;

// Attention!!!!!
protected:
  SingletonTemplte() { std::cout << "contructor called" << std::endl; }
};

#endif // TEMPLATE_H
```

这里的模版采用的是懒汉模式实现当中最优雅的版本，该版本简洁而且还避免了潜在的问题。

当我们在代码当中使用的时候：

```C++
/********************************************/
// Example:
// 1.friend class declaration is requiered!
// 2.constructor should be private

class DerivedSingleton : public SingletonTemplte<DerivedSingleton> {
  //Attention!!!!
  friend class SingletonTemplte<DerivedSingleton>;
public:
  DerivedSingleton(const DerivedSingleton &) = delete;
  DerivedSingleton &operator=(const DerivedSingleton &) = delete;

private:
  DerivedSingleton() = default;
};

int main() {
  DerivedSingleton& instance1 = DerivedSingleton::get_instance();
  DerivedSingleton& instance2 = DerivedSingleton::get_instance();
}
```

> 注意，这里使用到了**奇异递归模板模式**（curiously recurring template pattern，**CRTP**），一种C++模版编程时候的一种惯用法：***将派生类作为基类的模版参数。***