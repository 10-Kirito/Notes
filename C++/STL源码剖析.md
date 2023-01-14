# STL六大组件 功能与运用

1. 容器：各种数据结构用来存储数据。
2. 算法：从实现角度来看，STL算法是一种`function template`(即函数模板)。
3. 迭代器：就是泛型指针，就是重载了`operator *`、` operator ->` 、` operator ()`的`class template`(即模板类)。所有的容器都附带有自己专属的迭代器。
4. 仿函数，行为类似于函数，***从实现角度来看，仿函数是一种重载了`operator ()`的class或者class template。一般情况下，函数指针可以当作狭义的仿函数。***
5. 适配器（adapter）：一种用来修饰容器、仿函数、迭代器接口的东西。
6. 配置器（allocators）：负责空间配置和管理。