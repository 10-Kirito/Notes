# JDBC

# 1.0 JDBC简介

- JDBC就是使用Java语言操作关系型数据库的一套API，我们通过其提供的一些类和接口从而实现访问数据库的目的，我们通过该套API可以访问多种数据库；
- 全程： ***Java DataBase Connectivity***;
- 需要注意的是JDBC其中仅仅是单纯的一套标准接口，并没有具体的实现类，***实现类是由各种数据库自己去负责实现的***各个厂商其写出来的实现类，其有一个很特别的名字叫做***驱动***，一般都会提供一个jar包，里面就是我们所需要的实现类；

> 这就是所谓的面向接口编程。

# 2.0 使用JDBC连接数据库的步骤

0. 创建工程，将我们的驱动jar包导入我们的工程当中，里面有对应接口的实现类；

> MYSQL的jar包路径位置是在 C:\Program Files (x86)\MySQL\Connector J 8.0

1. 注册驱动

```java
Class.forName("com.mysql.jdbc.Driver");
```

> 最新的Java版本是不需要我们手动注册驱动了，因为采用了SPI机制，注册驱动任务交由别人来完成。

2. 获取连接对象

```java
Connection connection = DriverManager.getConnection(url,username,password);
// 示例代码:
connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/school","root","123456");
```

3. 定义SQL语句

```java
String sql = "update...";
```

4. 获取执行SQL对象

```java
Statement statement = connection.createStatement();
```

5. 执行SQL,并将返回结果进行保存

```java
ResultSet resultSet = statement.executeUpdate(sql);
```

6. 处理返回结果
7. 释放资源 

# 3.0 JDBC-API详解-DriverManager

- DriverManager(驱动管理类)作用：

  1. 注册驱动；
  2. 获取数据库连接；

  ![JDBC0](.\pictures\JDBC0.png)

# 4.0 JDBC-API详解-Connection

1. 获取执行SQL的对象

- 普通执行SQL对象

```java
Statement createStatement();
```

- 预编译SQL的执行SQL对象：防止SQL注入（***很重要***）

```java
PreparedStatement prepareStatement(sql);
```

- 执行存储的对象(不常用)

```java
CallableStatement prepareCall(sql);
```

2. 事务管理

- MYSQL事务管理

> 开启事务：BEGIN;/ START TRANSACTION;
>
> 提交事务：COMMIT;
>
> 回滚事务：ROLLBACK;
>
> MYSQL默认为自动提交事务
>
> 事务就是将某几个操作当作一个事件来看待，如果该事件中出现任何问题，都不会对数据库造成影响，所做出的修改也都会被恢复。

- JDBC事务管理，Connection接口中定义了3个对应的方法

> 开启事务：`setAutoCommit(bollean	autoCommit)`, true为自动提交事务，false为手动提交事务，即开启事务；
>
> 提交事务：`commit()`;
>
> 回滚事务：`rollback()`;

```java
import java.sql.*;

public class JDBC_Demo {
    public static void main(String[] args) throws Exception {
        // 1. 注册驱动，该步骤可以省略
        // Class.forName("com.mysql.jdbc.Driver");
        
        // 2. 获取连接对象
        String url = "jdbc:mysql://127.0.0.1:3306/test";
        String username = "root";
        String passwd = "123456";
        Connection connection = DriverManager.getConnection(url, username, passwd);

        // 3. 定义SQL语句
        String sql = "select * from test";

        // 4. 获取执行SQL对象
        Statement statement = connection.createStatement();

        // 5. 执行SQL，并且将结果进行保存
        ResultSet resultSet = statement.executeQuery(sql);

        // 6. 对获得的数据进行处理
        // 处理获得的数据的时候需要注意一点的是数据的下标是从1开始的，并不是从0开始的
        while (resultSet.next()){
            System.out.println(resultSet.getString(1) + " ");
            //System.out.print(resultSet.getString(2) + " ");
        }
        // 8.补充开启事务和关闭事务
        String sql1 = "update test set id = 1000 where id = 2";
        String sql2 = "update test set id = 2000 where id = 3";

        try {
            // 8.1 开启事务
            connection.setAutoCommit(false);
            int result1 = statement.executeUpdate(sql1);

            int bk = 1/0;
            // 这里会抛出异常，就相当于我们事实当中执行某一段程序的时候发生异常，那么开启事务之后的所有的内容
            // 都不算数，对数据库做出的所有的影响全部都作废

            int result2 = statement.executeUpdate(sql2);
            // 8.2 提交事务
            connection.commit();

        } catch (SQLException e) {
            // 8.3 回滚事务
            connection.rollback();
            throw new RuntimeException(e);
        }

        // 7. 释放资源
        resultSet.close();
        statement.close();
        connection.close();
    }
}
```

# 5.0 JDBC-API详解-Statement

1. 执行各种SQL语句

```java
statement.executeQuery(sql);
```

# 6.0 JDBC-API详解-ResultSet

1. 封装了我们的DQL查询语句的查询结果

- 获取查询结果：

```java
boolean next(); // 将当前光标从当前位置向前移动一行，就是获取下一组数据，并且返回值可以判断当前行是否为有效行
								// - true, 有效行，当前行含有数据
								// - false, 无效行，当前行没有数据

xxx getxxx(参数，比如说下标，从1开始); int getint(参数); String getString(参数);
```

# 7.0 JDBC-API详解-PreparedStatement

- 作用：

1. 预编译SQL语句并且执行：预防SQL注入问题

- 使用：

  1. 获取PreparedStatement对象

  ```java
  // SQL语句中的参数值，使用？作为占位符进行替代
  String sql = "select * from user where username = ? and password = ?";
  
  // 通过Connection对象获取，并且传入对应的sql语句
  PreparedStatement pstmt = connection.prepareStatement(sql);
  ```

  2. 设置参数值

  ```java
  PreparedStatement对象: setXX(参数1， 参数2): 给参数？进行赋值
  ```

  3. 执行SQL

  ```java
  preparedStatement.executeUpdate(); / executeQuery(); 不需要再次传递sql
  ```

  > 注释：
  >
  > 这样的话，根本没有拼接字符串的那一个步骤，所以说SQL注入在这里会失败。
  >
  > 其实现原理为：
  >
  > - 预编译SQL，性能更高；
  > - 防止SQL注入：将敏感字符进行一个转义；

  

# 8.0 数据库连接池 Druid

> 管理数据连接的一个容器

![JDBC1](.\pictures\JDBC1.png)

- 数据库连接池的实现

1. 标准接口：DataSource

​		1.1 官方提供连接池接口，有第三方组织进行实现；

​		1.2 功能： 获取连接

```java
Connection getConnection();
```

>  	常见的数据库连接池：
>
> - DBCP；
> - C3P0；
> - Druid(Java语言最好的数据库连接池之一)；

Druid使用步骤：

> 1. 导入jar包  druid-1.1.12jar;
> 2. 定义配置文件；
> 3. 加载配置文件；
> 4. 获取数据库连接池对象；
> 5. 获取连接；