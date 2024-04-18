# Never Stop Learning

# 一.IO

## 1. `class stringstream`

Include library:

```C++
#include<sstream>
```

class `stringstream`是C++标准类当中的一个类，它允许我们在内存当中创建一个类似于`std::cin`和`std::cout`的流对象，这个对于我们处理字符串的时候非常有用，通常用来从字符串当中提取出相应的数据。

在实际的使用当中，还有另外的两个字符串流类：

1. `std::istringstream`:用于从字符串当中提取数据，常用于解析字符串；
2. `std::ostringstream`:用于将数据输出到字符串当中，常用于将数据格式化为字符串；

但是一般都是使用`stringstream`来进行处理的，我们只需要在每次处理之前调用相应的`clear`函数来清空相应的缓冲区，防止残留数据对我们的程序造成影响。

***Member functions(该类自己的成员函数):***

1. `str`, gets or sets the contents of underlying string device object;

***Inherited from std::basic_istream(继承自别的类的函数):***

1. `get`, extracts characters;
2. `std::stringstream& sgetline(std::stringstream& is, std::string & str, char delim = '\n')`, extracts character until the given character is found;

*示例程序：*

```C++
#include <iostream>
#include <sstream>
#include <string>
int main() {
    // test `str()`:
    std::stringstream ss;
    ss.str("hello, world\ntest\n");
    std::cout << ss.str();
    // test `get()` and `std::getline(ss, line, '\\n')`
    std::string line;
    std::cout << (char)ss.get() << std::endl;
    std::cout << "Test `std::getline(ss, line, '\\n')`" << std::endl;
    while (std::getline(ss, line)) {
        std::cout << "Line: " << line << std::endl;
    }
    return 0;
}
```

3. `clear()`, 重置其输入流的错误状态码。

> Sets the stream error state flags by assigning them the value of state. By default, assigns std::ios_base::goodbit which has the effect of clearing all error state flags.
> If rdbuf() is a null pointer (i.e. there is no associated stream buffer), then state | std::ios_base::badbit is assigned.

### 1.1 example 

題目：输入的第一行有一个数字 N 代表接下來有 N 行資料，每一行資料里有不固定個數的整數(最多 20 個，每行最大 200 個字元)，請你寫一個程式將每行的总和印出來。

輸入：

```input
3
1 2 3
20 17 23 54 77 60
111 222 333 444 555 666 777 888 999
```

输出：

```input
6
251
4995
```

```C++
#include <iostream>
#include <sstream>
#include <string>

int main(int, char**) {
    std::string s;
    std::stringstream ss;
    int n, sum, temp;
    std::cin >> n;
    std::cin.get();
    while (n--) {
        // get the input data
        std::getline(std::cin, s);
        // put the input data into stringstream
        ss.clear();
        ss.str(s);
        sum = 0;
        while (ss >> temp) {
            sum += temp;
        }
        std::cout << sum << std::endl;
    }
    return 0;
}
```













## 2. `basic_ios::clear`

```C++
#include <iostream>
#include <string>
int main()
{
    for (char c : {'\n', '4', '1', '.', '3', '\n', 'Z', 'Y', 'X'})
        std::cin.putback(c); // emulate user's input (not portable: see ungetc Notes)
    double n;
    while (std::cout << "Please, enter a number: " && !(std::cin >> n))
    {
        std::cin.clear();
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << "\nI am sorry, but '" << line << "' is not a number\n";
    }
    std::cout << n << "\nThank you for entering the number " << n << '\n';
}
```

这里我们首先模拟用户的输入:`std::cin.putback(c)`, 用户输入:`XYZ\n3.14\n`。

这里的`putback(c)`函数：Puts the character c back to the input stream so the next extracted character will be c.也就是说当我调用该函数添加字符的时候，是放在缓冲区的最前面。

接着，由于`std::cin >> n `这里输入的时候一定会出错的，所以说我们为了不影响接下来的操作会`clear()`，这样之前的错误就不会影响我们的输入。

## 3. `std::getline(std::cin, str)`

*函数声明：*

```C++
template< class CharT, class Traits, class Allocator >
std::basic_istream<CharT, Traits>&
getline( std::basic_istream<CharT, Traits>& input,
         std::basic_string<CharT, Traits, Allocator>& str, 
         CharT delim );
```

返回值类型为`std::basic_istream<CharT, Traits>&`, 该类的内部重载了`operator bool()`，即类型转换符号，所以说当我们这样写：

```C++
while(std::getline(std::cin, str)) {}
```

如果`std::getline`读取数据的时候发生错误的话或者数据读取完毕的时候，返回的输入流对象会设置错误标志位，会导致该流的状态异常。而`operator bool()`重载的函数内部就是根据流的状态返回的，所以如果`std::getline`函数遇到错误的话或者数据读取完毕的时候，其当做条件的时候会隐式转换为布尔值为false,从而while循环结束。
