# OpenMP 并行编程示例代码

本文件夹包含 OpenMP 并行编程相关的示例代码和实验资料。

## 📁 文件列表

### 📝 基础示例

| 文件名 | 描述 |
|--------|------|
| [HelloOMP.cpp](./HelloOMP.cpp) | OpenMP 入门示例 - Hello World |
| [first.cpp](./first.cpp) | 第一个 OpenMP 示例 |
| [first_parallel.cpp](./first_parallel.cpp) | 第一个并行示例 |
| [testfor.cpp](./testfor.cpp) | for 循环并行化测试 |

### 📝 π 值计算示例 (并行算法典型示例)

| 文件名 | 描述 |
|--------|------|
| [PI_Parallel.cpp](./PI_Parallel.cpp) | π 值并行计算 |
| [PI_Parallel_v1.cpp](./PI_Parallel_v1.cpp) | π 值并行计算 (版本 1) |
| [PI_Parallel_v2.cpp](./PI_Parallel_v2.cpp) | π 值并行计算 (版本 2) |

### 📝 数据作用域示例

| 文件名 | 描述 |
|--------|------|
| [private.cpp](./private.cpp) | private 子句示例 |
| [firstprivate.cpp](./firstprivate.cpp) | firstprivate 子句示例 |
| [reduction.cpp](./reduction.cpp) | reduction 子句示例 |

### 📂 子文件夹

| 文件夹名 | 描述 |
|----------|------|
| [course](./course/) | 课程实验相关资料 |
| [False_sharing](./False_sharing/) | 伪共享问题示例 |

### ⚙️ 编译产物

| 文件名 | 描述 |
|--------|------|
| HelloOMP | 可执行文件 |
| PI_Parallel | 可执行文件 |
| PI_Parallel_v1 | 可执行文件 |
| PI_Parallel_v2 | 可执行文件 |
| first | 可执行文件 |
| firstprivate | 可执行文件 |
| private | 可执行文件 |
| reduction | 可执行文件 |
| a.out | 编译输出 |

---

## 📁 course 文件夹

课程实验相关资料：

| 文件名 | 描述 |
|--------|------|
| [HelloOMP.cpp](./course/HelloOMP.cpp) | 课程 Hello OpenMP 示例 |
| [matrix_multi.cpp](./course/matrix_multi.cpp) | 矩阵乘法 (串行版本) |
| [matrix_multi_parallel.cpp](./course/matrix_multi_parallel.cpp) | 矩阵乘法 (并行版本) |
| [matrix_multi_parallel_v1.cpp](./course/matrix_multi_parallel_v1.cpp) | 矩阵乘法 (并行优化版本) |
| [实验二 20121333-周鹏飞.md](./course/实验二%2020121333-周鹏飞.md) | 实验二报告 (Markdown) |
| [实验二 20121333-周鹏飞.pdf](./course/实验二%2020121333-周鹏飞.pdf) | 实验二报告 (PDF) |

---

## 📋 文件类型统计

- **C++ 源代码**: 10+ 个
- **实验报告**: 2 个
- **子文件夹**: 2 个
- **可执行文件**: 若干

## 🔗 相关文档

- [OpenMP 笔记](../OpenMP.md)
