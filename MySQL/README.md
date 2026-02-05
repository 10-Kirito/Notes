# MySQL 学习笔记与资料

本文件夹包含MySQL数据库相关的学习笔记、实践代码和参考书籍。

## 📚 目录结构

```
MySQL/
├── 📖 参考书籍与PDF
├── 📝 学习笔记
├── 💻 代码与脚本
├── 📸 图片资源
├── 🎓 课程资料
└── 🔗 数据库连接示例
```

---

## 📖 参考书籍与PDF

| 文件名 | 描述 |
|--------|------|
| [MySQL必知必会.pdf](./MySQL必知必会.pdf) | 经典入门书籍，涵盖MySQL基础操作 |
| [MySQL是怎样运行的(小孩子4919).pdf](./MySQL是怎样运行的(小孩子4919).pdf) | 深入讲解MySQL内部运行原理 |
| [高性能MySQL(第3版).pdf](./高性能MySQL(第3版).pdf) | MySQL性能优化权威指南 |
| [数据库系统概论（第5版）.pdf](./数据库系统概论（第5版）.pdf) | 数据库理论基础教材 |

---

## 📝 学习笔记

### 核心笔记

| 文件名 | 描述 |
|--------|------|
| [MYSQL必知必会.md](./MYSQL必知必会.md) | 《MySQL必知必会》读书笔记，包含第4-22章SQL示例 |
| [MYSQL必知必会4-15.sql](./MYSQL必知必会4-15.sql) | 《MySQL必知必会》第4-15章SQL实践代码 |
| [Mysql_study.md](./Mysql_study.md) | MySQL学习笔记，涵盖数据库基础、InnoDB存储结构、索引等 |
| [Mysql_others.md](./Mysql_others.md) | 其他MySQL相关笔记，包含存储引擎、索引使用等进阶内容 |
| [索引.md](./索引.md) | 数据库索引专题笔记，包含ER图、数据模型等内容 |
| [随记.md](./随记.md) | 日常学习随记 |

### 笔记主要内容概览

#### MYSQL必知必会.md
- 第4章：检索数据 (SELECT)
- 第5章：排序数据 (ORDER BY)
- 第6-7章：过滤数据 (WHERE, AND, OR, IN)
- 第8章：通配符过滤 (LIKE, %)
- 第9章：正则表达式搜索
- 第10章：计算字段 (CONCAT, 别名)
- 第11章：数据处理函数
- 第12章：汇总数据 (聚集函数)
- 第13章：分组数据 (GROUP BY, HAVING)
- 第14章：子查询
- 第15章：联结表 (JOIN)
- 第22章：视图 (VIEW)

#### Mysql_study.md
- 数据库基础概念
- RDBMS与非RDBMS比较
- 关系型数据库设计规则
- 表的关联关系
- InnoDB记录存储结构
- 索引原理（B+树索引）

---

## 💻 代码与脚本

### 根目录脚本
| 文件名 | 描述 |
|--------|------|
| [MYSQL必知必会4-15.sql](./MYSQL必知必会4-15.sql) | 《MySQL必知必会》实践SQL代码 |

### codes/ 目录
| 文件名 | 描述 |
|--------|------|
| [begin.sql](./codes/begin.sql) | 基础SQL脚本 |
| [create_school.sql](./codes/create_school.sql) | 学校数据库创建脚本 |
| [Populate.sql](./codes/Populate.sql) | 数据填充脚本 |
| [实验四.sql](./codes/实验四.sql) | 第四次实验SQL代码 |
| [实验5.sql](./codes/实验5.sql) | 第五次实验SQL代码 |

### mysql_scripts/ 目录
| 文件名 | 描述 |
|--------|------|
| [create.sql](./mysql_scripts/create.sql) | 《MySQL必知必会》示例表创建脚本 |
| [populate.sql](./mysql_scripts/populate.sql) | 《MySQL必知必会》示例数据填充脚本 |

---

## 📸 图片资源

[pictures/](./pictures/) 目录包含笔记中使用的图片资源：
- 数据库结构图
- ER图示例
- 关系模型说明图

---

## 🎓 课程资料

[Course/](./Course/) 目录包含数据库课程的周进度资料：

| 目录 | 内容 |
|------|------|
| 1. 第一周 | 数据库原理研讨 |
| 2. 第二周 | 实验二 + 原理讲解 |
| 3. 第三周 | 第三周实验 |
| 4. 第四周 | 第四周实验 |
| 5. 第五周 | 研讨 + 实验 |
| 6. 第六周 | 上机实验 + 作业 |
| 7. 第七周 | 研讨内容 + 连接 |

参考教材：[数据库实用教程.pdf](./Course/数据库实用教程.pdf)

---

## 🔗 数据库连接示例

[Connection/](./Connection/) 目录包含数据库连接的代码示例：
- **FirstConnect**: Visual Studio C++ 数据库连接项目

---

## 🚀 快速开始

### 1. 创建示例数据库

```bash
# 进入mysql命令行
mysql -u root -p

# 创建数据库
CREATE DATABASE study;
USE study;

# 运行建表脚本
source mysql_scripts/create.sql;

# 填充示例数据
source mysql_scripts/populate.sql;
```

### 2. 学习路线建议

1. **入门阶段**：阅读 [MySQL必知必会.pdf](./MySQL必知必会.pdf) + 配套笔记 [MYSQL必知必会.md](./MYSQL必知必会.md)
2. **基础巩固**：学习 [Mysql_study.md](./Mysql_study.md) 了解数据库设计原理
3. **深入理解**：阅读 [MySQL是怎样运行的](./MySQL是怎样运行的(小孩子4919).pdf) 理解底层原理
4. **性能优化**：参考 [高性能MySQL](./高性能MySQL(第3版).pdf) 学习优化技巧
5. **实践练习**：完成 [Course/](./Course/) 中的各周实验

---

## 📋 TODO

- [ ] 整理更多索引相关笔记
- [ ] 添加事务与锁机制笔记
- [ ] 补充MySQL优化实践案例
- [ ] 添加常见面试题总结

---

## 📌 注意事项

1. SQL脚本基于MySQL 5.7+版本
2. 部分笔记中的图片路径使用相对路径，请在本地查看
3. 课程资料为学校教学内容，仅供学习参考
