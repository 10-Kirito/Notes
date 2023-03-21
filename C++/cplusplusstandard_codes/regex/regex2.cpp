#include <string>
#include <regex>
#include <iostream>
using namespace std;

int main (int argc, char *argv[])
{
  string data = "<person>\n"
                " <first>Nico</first>\n"
                " <last>Jone</last>\n"
                "</person>\n";


  regex reg("<(.*)>(.*)</(\\1)>");

  smatch m;
  // 1. 这里就可以体现出regex_search 和regex_match之间的区别所在，一个regex_match 检验所有的字符串是否符合我们定义的模式
  // 另一个是检验目标字符串中是否含有符合我们定义的模式的子字符串, 如果说目标字符串中存在匹配的字符串，那么会返回第一个
  // 匹配结果的相关信息
  bool found = regex_search(data,
                          m,
                          reg);

  // 2. 使用迭代器来表明目标字符串的范围
  string::const_iterator iterStart = data.begin();
  string::const_iterator iterEnd = data.end();

  for (; regex_search(iterStart, iterEnd, m, reg); iterStart = m[0].second) {
    cout << "match:     " << m.str() << endl; 
    cout << "tag:       " << m[1] << endl;
    cout << "value:     " << m[2] << endl;
  }

  return 0;
} 
