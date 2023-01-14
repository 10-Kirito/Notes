# STL六大组件 功能与运用

1. 容器：各种数据结构用来存储数据。
2. 算法：从实现角度来看，STL算法是一种`function template`(即函数模板)。
3. 迭代器：就是泛型指针，就是重载了`operator *`、` operator ->` 、` operator ()`的`class template`(即模板类)。所有的容器都附带有自己专属的迭代器。
4. 仿函数，行为类似于函数，***从实现角度来看，仿函数是一种重载了`operator ()`的class或者class template。一般情况下，函数指针可以当作狭义的仿函数。***
5. 适配器（adapter）：一种用来修饰容器、仿函数、迭代器接口的东西。
6. 配置器（allocators）：负责空间配置和管理。

> 由于SGI STL希望可以具备广泛的移植的能力，SGI STL准备了一个环境组态文件`<stl_config.h>`  ,该文件中定义了许多的常量，表示着某些条件的成立与否，然后所有的STL头文件都会根据各个常量是否定义来编译执行不同的程序代码。
>
> 该文件中的19条说明，本书中将其翻译为组态？？
>
>    [stl_config.h](stl_source_code/sgi-stl-master/g++/stl_config.h)  
>
> 该文件做了什么？
>
> // What this file does.
>
> //  (1)  Defines bool, true, and false if the compiler doesn't do so already.
>
> //  如果编译器没有定义bool,true,false,就去定义他们
>
> //  (2)  Defines __STL_NO_DRAND48 if the compiler's standard library does
>
> //    not support the drand48() function.
>
> //  (3)  Defines __STL_STATIC_TEMPLATE_MEMBER_BUG if the compiler can't 
>
> //    handle static members of template classes.
>
> //  如果编译器无法处理类内的静态变量，就定义对应的常量
>
> //  (4)  Defines 'typename' as a null macro if the compiler does not support
>
> //    the typename keyword.
>
> //  (5)  Defines __STL_CLASS_PARTIAL_SPECIALIZATION if the compiler 
>
> //    supports partial specialization of class templates.
>
> //  (6)  Defines __STL_FUNCTION_TMPL_PARTIAL_ORDER if the compiler supports
>
> //    partial ordering of function templates (a.k.a partial specialization
>
> //    of function templates.
>
> //  (7)  Defines __STL_EXPLICIT_FUNCTION_TMPL_ARGS if the compiler
>
> //    supports calling a function template by providing its template
>
> //    arguments explicitly.
>
> //  (8)  Defines __STL_MEMBER_TEMPLATES if the compiler supports
>
> //    template members of classes.
>
> //  (9)  Defines 'explicit' as a null macro if the compiler does not support
>
> //    the explicit keyword.   
>
> //  (10) Defines __STL_LIMITED_DEFAULT_TEMPLATES if the compiler is
>
> //    unable to handle default template parameters that depend on
>
> //    previous template parameters.
>
> //  (11) Defines __STL_NON_TYPE_TMPL_PARAM_BUG if the compiler has 
>
> //    trouble performing function template argument deduction for
>
> //    non-type template parameters.
>
> //  (12) Defines __SGI_STL_NO_ARROW_OPERATOR if the compiler is unable
>
> //    to support the -> operator for iterators.
>
> //  (13) Defines __STL_USE_EXCEPTIONS if the compiler (in the current
>
> //    compilation mode) supports exceptions.
>
> //  (14) Define __STL_USE_NAMESPACES if we're putting the STL into a 
>
> //    namespace.  
>
> //  (15) Defines __STL_SGI_THREADS if this is being compiled on an SGI
>
> //    compiler, and if the user hasn't selected pthreads or no threads
>
> //    instead.
>
> //  (16) Defines __STL_WIN32THREADS if this is being compiled on a 
>
> //    WIN32 compiler in multithreaded mode.
>
> //  (17) Define namespace-related macros (__STD, __STL_BEGIN_NAMESPACE, etc.)
>
> //    `apropriately`.
>
> //  (18) Define exception-related macros (__STL_TRY, __STL_UNWIND, etc.)
>
> //    appropriately.
>
> //  (19) Defines __stl_assert either as a test or as a null macro,
>
> //    depending on whether or not __STL_ASSERTIONS is defined.

# 1. 可能令我们困惑的语法

> ***下面讲述的是利于我们去理解SGI STL源码中的一些特殊的语法以及他自己的规定，还有就是可以顺便跟着学习一些语法之类的。***

## 1.1 类模板中可以定义静态变量

```c++
// Defines __STL_STATIC_TEMPLATE_MEMBER_BUG if the compiler can't 
// handle static members of template classes.
// 对应的宏变量为__STL_STATIC_TEMPLATE_MEMBER_BUG
// 该宏变量是在编译器无法处理static member of template classes的时候定义的
// 对应stl_config.h文件做的第3件事情

template <typename T>
class testClass{
public:
  static int _data;
}

int testClass<int>::_data = 1;
int testClass<char>::_data = 2;
```

## 1.2 partial specialization of class templates*** 模板的偏特化

偏特化我们会在Iterator_traits部分看到明显的使用，主要是针对原生指针来讲的。

```c++
//Defines __STL_CLASS_PARTIAL_SPECIALIZATION if the compiler 
//supports partial specialization of class templates.
// 如果说编译器支持partial specialization of template classes，就定义宏常量
// _STL_CLASS_PARTIAL_SPECIALIZATION
// 对应文件中做的第5件事情

// 一般化模板
template <class T, class O>
struct testClass{
  testClass() { std::cout<< "T, O" <<endl;}
};

// 下面偏特化模板在遇到模板参数为:testClass<int *, int *> obj2的情况下就会被调用
// 模板的偏特化
template <class T>
struct testClass<T*, T*>
{
  testClass() {std::cout << "T*, O*" <<endl;}
};

// 模板的偏特化
template <class T>
struct testClass<const T*, T*>
{
  testClass() {std::cout << "const T*, T*" <<endl;}
};

```

## 1.3  模板类中允许定义模板

就是很简单的, 我们可以在模板类中另外的去定义模板函数之类的内容，当我们使用到对应的模板函数的时候，我们可以选择利用模板的自动推导来推导变量的类型，也可以具体指明

```c++
// Defines __STL_MEMBER_TEMPLATES if the compiler supports
// template members of classes.
// 如果编译器支持类中定义模板的话，就定义对应的变量
// 对应文件中做的第8件事情

template <class T, class Alloc = alloc>
class vector {
public:
  typedef T value_type;
  typedef value_type* iterator;
  
  // 注意这里模板的参数不一样
  template <class I>
  void insert(iterator position, I first, I last) {
    cout << "insert()" << endl;
  }
};

int main()
{
  int ia[5] = {0,1,2,3,4};
  
  vector<int> x;
  vector<double> y;
  vector<int> :: iterator ite;
  // 由模板自行推导参数的类型
  x.insert(ite, ia, ia+5); // insert()
}
```

> 以下代码是编译器的视角看到的源代码：

```C++
#include<iostream>

using namespace std;

class alloc
{
};

template<class T, class Alloc = alloc>
class vector
{
  
  public: 
  // 1. 在这里我们可以看到编译器将typedef翻译成了using 
  using value_type = T;
  using iterator = value_type *;
  template<class I>
  inline void insert(iterator position, I first, I last)
  {
    std::operator<<(std::cout, "insert()").operator<<(std::endl);
  }
};

/* First instantiated from: insights.cpp:24 */
// 2. 下面是我们实例化模板的时候发生的事情，编译器另外的去定义了一个模板其中参数类型改为我们实例化模板的参数
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class vector<int, alloc>
{
  
  public: 
  using value_type = int;
  using iterator = vector<int>::value_type *;
  template<class I>
  inline void insert(vector<int>::iterator position, I first, I last);
  
  /* First instantiated from: insights.cpp:28 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  // 3. 这里是我们利用模板的参数自动推导推导出insert函数模板的参数类型是什么
  inline void insert<int *>(vector<int>::iterator position, int * first, int * last)
  {
    std::operator<<(std::cout, "insert()").operator<<(std::endl);
  }
  #endif
  // inline constexpr vector() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:25 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class vector<double, alloc>
{
  
  public: 
  using value_type = double;
  using iterator = vector<double>::value_type *;
  template<class I>
  inline void insert(vector<double>::iterator position, I first, I last);
  // inline constexpr vector() noexcept = default;
  // 4. 这里有一个细节，就是我们如果没有使用到相应的模板，那么其就不会重新书写出来一个模板
};

#endif
int main()
{
  int ia[5] = {0, 1, 2, 3, 4};
  vector<int, alloc> x = vector<int, alloc>();
  vector<double, alloc> y = vector<double, alloc>();
  vector<int>::iterator ite;
  x.insert<int *>(ite, ia, ia + 5);
  return 0;
}

```

## 1.4 模板参数可以可以根据前面的template参数来设定自己的设定默认值

```c++
// Defines __STL_LIMITED_DEFAULT_TEMPLATES if the compiler is
// unable to handle default template parameters that depend on
// previous template parameters.
// 如果编译器不支持下面的操作的话，就去定义上面的宏变量

// 这里就是根据前面参数T来设定自己的默认值
template <class T, class Sequence = deque<T>>
class stack{
public :
  stack() { cout << "stack" <<endl;}
private:
  Sequence c;
};
```

我们可以在SGI源码中看到这样的写法：

```c++
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class T, class Sequence = deque<T> >
#else
template <class T, class Sequence>
#endif
class stack {}
```

这一段代码是定义stack类的模板声明的时候，如果编译器不支持这样的写法会怎么办？这一点可以感受到STL的移植性。

 [stl_stack.h](stl_source_code/sgi-stl-master/g++/stl_stack.h) 

我又去找了我使用的c++中的STL中的源码，发现是这样写的：

```c++
template<typename _Tp, typename _Sequence = deque<_Tp> >
class stack{}
```

我们可以看到不同版本的定义是不一样的，应该是后面的代码更新吧。

 [stl_stack.h](stl_source_code/Source0/stl_stack.h) 

## 1.5  ***_STL_NULL_TMPL_ARGS***

```c++
# ifdef _STL_EXPLICIT_FUNCTION_TEML_ARGS
# 	define _STL_NULL_TMPL_ARGS <>
# else
# 	define _STL_NULL_TMPL_ARGS
# endif
// 就是在STL的某些地方使用了一些宏，如果我们不知道这些的话，可能会感到迷茫

// in <stl_stack.h>文件中，有下面的书写方式
template <class T, class Sequence = deque<T>>
class stack {
  friend bool operator== __STL_NULL_TMPL_ARGS (const stack&, const stack&);
  friend bool operator< __STL_NULL_TMPL_ARGS (const stack&, const stack&);
}

// 我们将其进行宏替换之后就变成了下面源代码：
template <class T, class Sequence = deque<T>>
class stack{
  friend bool operator == <> (const stack&, const stack&);
  friend bool operator< <> (const stack&, const stack&);
}
```

该语法是为了实现所谓的***bound friend template***实现的。

> 知识点补充：
>
> ```c++
> /* 在类定义前，先声明友元类Blobptr和友元函数operator== */
> template <typename> class Blobptr;
> template <typename> class Blob;
> // 1. 首先声明了两个模板类
> 
> // 2. 接着声明了一个模板函数
> template <typename T>
> 	bool operator==(const Blob<T>&, const Blob<T>&)
> 
> // 在一个类中将另外的一个类和一个模板函数声明为友元
> // 这里注意一下我们如果说是声明一个类为友元类的话，我们就不可以省略尖括号中的参数，以为这是我们实例化该类的时候传进去的唯一参数，编译器只能通过尖括号中的参数来推断将该模板实例化为什么样子
> // 但是模板函数就不一样了，我们可以省略所有的参数T，因为我们有强大的模板实参推断机制
> // 也就是说我们可以这样声明下面的友元函数:
> // friend bool operator == <> (const Blob &, const Blob &);
> template <typename T> class Blob {
> 	friend class BlobPtr<T>;
> 	friend bool operator==<T>
> 		(const Blob<T>&, const Blob<T>&);
> };
> ```

补充完知识点，我们再看下面的代码：

```C++
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
}
// 这里我们可以看到很多种写法，为什么有的参数T是可以省略的，就是因为我们强大的模板实参推断机制
// 上面的所有的代码，编译器看到的样子是这样的:
template<class T, class Sequence = deque<T>>
class stack
{
  public: 
  // 注意还有一点就是我们下面的参数是由我们的类来实例化的
  friend bool operator==(const stack<T> &, const stack<T> &);
  friend bool operator<(const stack<T> &, const stack<T> &);
  friend bool operator==(const stack<T, Sequence> &, const stack<T, Sequence> &);
  friend bool operator<(const stack<T, Sequence> &, const stack<T, Sequence> &);
  friend bool operator==(const stack<T, Sequence> &, const stack<T, Sequence> &);
  friend bool operator<(const stack<T, Sequence> &, const stack<T, Sequence> &);
}
// 我们可以看到除了前面的两个模板函数之外，下面的所有的模板函数全部都是根据实参的类型来判断的
```

## 1.6 _STL_TEMPLATE_NULL, 模板的特化

此处是和另一篇笔记中的模板的特化是挂上钩的。

```C++
// <stl_config.h>定义__STL_TEMPLATE_NULL如下：
 
# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
# define __STL_TEMPLATE_NULL template<>
# else
# define __STL_TEMPLATE_NULL
# endif
```

这样的宏常量经常出现在类似于这样的场合：

```C++
// in <type_traits.h>
template <class type> struct __type_traits { ...};
__STL_TEMPLATE_NULL struct __type_traits<char> { ...};

// in <stl_hash_fun.h>
template <class key> struct hash { ...};
__STL_TEMPLATE_NULL struct hash<char> { ...};
__STL_TEMPLATE_NULL struct hash<unsigned char> { ...};


// 我们将其展开之后就是下面的模样
template <class type> struct __type_traits { ...};
template<> struct __type_traits<char> { ...};

template <class key> struct hash { ...};
template<> struct hash<char> { ...};
template<> struct hash<unsigned char> { ...};
```

这里就是我们在另外的一篇笔记中所讲述的特化。 [STL_Containers.md](STL_Containers.md) 

## 1.7 临时对象的产生运用

我们有的时候难免使用到一些临时的变量，这样可以使得我们的程序干净清爽。我们制造临时变量的方法是，在型别名称后面直接加上一对小括号，并且可以指定其初始值，比如说`int(8)`，就相当于仅仅调用相应的`constructor`但是不指定对象的名称，***这里需要我们注意的是这里产生的是右值。***

比如说：

```c++
#include<vector>
#include<algorithm>
using namespace std;

// 下面的书写方式和我们在C++多线程中往线程构造函数中传递一样
template <typename T>
class print
{
  public:
  void operator()(const T& elem)
  { cout << elem << ' ';}
}

int main()
{
  int ia[6] = {0,1,2,3,4,5};
  vector<int> iv(ia, ia+6);
  
  for_each(iv,begin(), iv.end(), print<int>());
}
// 需要我们注意的是我们仅仅是创建了一个print类的临时对象，其模板参数为int，由于这里是传入右值，所以说当该函数结束的时候，这个临时对象也就结束了他的生命。
```

## 1.8 静态常量整数成员可以在类内直接初始化

## 1.9 前开后闭区间表示法

## 2.0 function call 操作符重载

这里就是我们重载`()`这个符号，从而使得一个类可以变成***在STL里面被称为仿函数。***所谓仿函数就是使用起来像函数一样的东西。

```C++
// 示例

// 这里由于我们将operator() 重载了，所以说plus变成了一个仿函数
template <class T>
struct plus{
  T operator()(const T& x, const T& y) const {return x+y;}
};
```

> ***这里的函数plus<T>已经十分接近STL的实现了，唯一的差别在于它缺乏“可配接能力”。***