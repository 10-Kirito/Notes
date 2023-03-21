#include <string>
#include <regex>
#include <iostream>
#include <iomanip>
//1. 该头文件的目的是为了格式化输出，比如说将bool变量以false或者true的值进行输出

using namespace std;

int main (int argc, char *argv[])
{
  string data = "XML tag: <tag-name>the value</tag-name>.";
  cout << "data:          " << data << "\n\n"; 

  smatch m;

  bool found = regex_search(data,
                            m,
                            regex(R"(<(.*)>(.*)</(\1)>)"));

  cout << "m.empty():              " << boolalpha << m.empty() << endl;
  cout << "m.size():               " << m.size() << endl;
  
  if (found) {
    cout << "m.str():                " << m.str() << endl;
    cout << "m.length():             " << m.length() << endl;
    cout << "m.position():           " << m.position() << endl;
    cout << "m.prefix().str():       " << m.prefix().str() << endl;
    cout << "m.suffix().str():       " << m.suffix().str() << endl;
    cout << endl;

    // 2. 使用下标遍历所有匹配的字符分组
    for (int i = 0; i < m.size(); ++i) {
      cout << "m[" << i << "].str():      " << m[i].str() << endl;
      //3. 注意这里的str(i)是针对每一个分组，有一个对应的对象
      cout << "m.str(" << i << "):        " << m.str(i) << endl;
      cout << "m.position(" << i << "):   " << m.position(i) << endl;
    } 

    // 3. 使用指针遍历所有匹配字符
    cout << endl;

    cout << "matches:" << endl;
    for (auto i = m.begin(); i != m.end(); ++i) {
      cout << " " << *i << " ";
      cout << "(length:"  << i->length() << ")" <<endl;
     }

  }

  return 0;
}
