# STL 源代码

本文件夹包含 STL (Standard Template Library) 标准模板库的源代码，用于学习和分析 STL 的内部实现。

## 📁 目录结构

### 📂 子文件夹

| 文件夹名 | 描述 |
|----------|------|
| [Source0](./Source0/) | GCC STL 源代码头文件 |
| [sgi-stl-master](./sgi-stl-master/) | SGI STL 实现源代码 |

---

## 📁 Source0 文件夹

包含 GCC/libstdc++ 的 STL 实现源代码头文件，主要包括：

### 容器相关

| 文件名 | 描述 |
|--------|------|
| stl_vector.h | `std::vector` 实现 |
| stl_list.h | `std::list` 实现 |
| stl_deque.h | `std::deque` 实现 |
| stl_set.h | `std::set` 实现 |
| stl_multiset.h | `std::multiset` 实现 |
| stl_map.h | `std::map` 实现 |
| stl_multimap.h | `std::multimap` 实现 |
| stl_tree.h | 红黑树实现 (set/map 底层) |
| stl_stack.h | `std::stack` 实现 |
| stl_queue.h | `std::queue` 实现 |
| forward_list.h | `std::forward_list` 实现 |
| unordered_map.h | `std::unordered_map` 实现 |
| unordered_set.h | `std::unordered_set` 实现 |
| hashtable.h | 哈希表实现 |

### 算法相关

| 文件名 | 描述 |
|--------|------|
| stl_algo.h | STL 算法实现 |
| stl_algobase.h | 基础算法实现 |
| stl_numeric.h | 数值算法实现 |
| stl_heap.h | 堆算法实现 |

### 迭代器相关

| 文件名 | 描述 |
|--------|------|
| stl_iterator.h | 迭代器实现 |
| stl_iterator_base_types.h | 迭代器基础类型 |
| stl_iterator_base_funcs.h | 迭代器基础函数 |
| stream_iterator.h | 流迭代器实现 |

### 内存管理相关

| 文件名 | 描述 |
|--------|------|
| allocator.h | 分配器实现 |
| alloc_traits.h | 分配器特性 |
| stl_construct.h | 对象构造/析构 |
| stl_uninitialized.h | 未初始化内存操作 |
| shared_ptr.h | 智能指针实现 |
| unique_ptr.h | 独占智能指针实现 |

### 函数对象相关

| 文件名 | 描述 |
|--------|------|
| stl_function.h | 函数对象实现 |
| std_function.h | `std::function` 实现 |
| functional_hash.h | 哈希函数对象 |

### 其他

| 文件名 | 描述 |
|--------|------|
| stl_pair.h | `std::pair` 实现 |
| basic_string.h | `std::string` 实现 |
| regex.h | 正则表达式实现 |
| random.h | 随机数实现 |

---

## 📁 sgi-stl-master 文件夹

包含经典的 SGI STL 实现源代码，SGI STL 是最早期的高质量 STL 实现之一，很多现代 STL 实现都参考了它的设计。

---

## 📋 文件类型统计

- **头文件 (.h/.tcc)**: 100+ 个
- **子文件夹**: 2 个

## 🔗 相关文档

- [STL 源码剖析 - 语法基础](../1.STL源码剖析--一些我们可能不知道的语法.md)
- [STL 源码剖析 - 空间配置器](../2.STL源码剖析--空间配置器(allocator).md)
- [STL 源码剖析 - 迭代器与 traits](../3.STL源码剖析--迭代器概念和traits编程技法.md)
- [STL 源码剖析 - 序列式容器](../4.STL源码剖析--序列式容器.md)
