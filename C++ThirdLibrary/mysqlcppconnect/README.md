# MYSQL Connect Learning

# 1. Use which tools to help us?

There have two choices:

1. **libmysqlclient-dev**:
   - `libmysqlclient-dev` 是 MySQL 客户端库的开发包。它提供了开发 MySQL 客户端应用程序所需的头文件和静态库。
   - 这个库主要用于使用 C 或者 C++ 来开发与 MySQL 服务器进行通信的应用程序。它提供了一系列的函数和接口，用于连接、查询、获取结果等操作。
2. **libmysqlcppconn-dev**:
   - `libmysqlcppconn-dev` 提供了 MySQL C++ 连接器的开发包。它是 MySQL 官方提供的 C++ 连接器库。
   - 这个库主要用于使用 C++ 来开发与 MySQL 服务器进行通信的应用程序。与 `libmysqlclient-dev` 不同，`libmysqlcppconn-dev` 提供了更加面向对象的 C++ 接口，使得在 C++ 中连接和操作 MySQL 数据库更加方便。

因此，主要区别在于它们提供的接口和开发风格。`libmysqlclient-dev` 提供了传统的 C 风格接口，而 `libmysqlcppconn-dev` 提供了更为现代化、面向对象的 C++ 接口。选择使用哪个库取决于你的项目需求和个人偏好。

I prefer the `libmysqlcppconn-dev`.

# 2. How to connect MYSQL?





***Codes:***

```C++
#include <cppconn/connection.h>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(int argc, char **argv) {
  cout << endl;
  cout << "Running 'SELECT * FROM USER'----->" << endl;
  cout << endl;

  try {
    sql::Driver *driver;
    sql::Connection *connection;
    sql::Statement *stmt;
    sql::ResultSet *res;

    // Create a connection:
    driver = get_driver_instance();
    connection =
        driver->connect("tcp://127.0.0.1:3306", "kirito", "Zpf.123456");
    // Connect to the MySQL database:
    connection->setSchema("chatserver");

    stmt = connection->createStatement();	
    res = stmt->executeQuery("select * from User");
    while (res->next()) {
      cout << "\t... MySQL replies: ";
      cout << res->getString("name") << endl;
      cout << "\t... MYSQL says it again: ";
      cout << res->getString("id") << endl;
    }
    delete res;
    delete stmt;
    delete connection;
  } catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;

  return EXIT_SUCCESS;
}
```

这里其实和Java当中连接数据库有些类似：

1. 先创建一个获取MySQL的实例；
2. 调用`driver->connect()`函数来连接到指定的数据库；
3. 选择要查询的数据库：`connection->setSchema()`, 也就是我们在数据库软件当中经常见到的架构；
4. 创建一个用于执行SQL语句的对象`Statement`;
5. 创建一个`ResultSet`对象来存储执行的结果，其中可以使用`ResultSet::next()`函数来遍历结果集当中的每一行数据；
6. `ResultSet::getString()`方法用于查询结果当中指定列的值；
7. 最后释放资源；