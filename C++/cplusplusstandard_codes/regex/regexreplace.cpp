#include <string>
#include <regex>
#include <iostream>
#include <iterator>

using namespace std;

int main (int argc, char *argv[])
{
  string data = "<person>\n"
                "<first>Nico</first>\n"
                "<last>Josuttis</last>\n"
                "</person>\n";

  regex reg("<(.*)>(.*)</(\\1)>");

  cout << regex_replace(data,
                        reg,
                        "<$1 value = \"$2\"/>") << endl;

  cout << regex_replace(data,
                        reg,
                        "<\\1 value = \"\\2\"/>",
                        regex_constants::format_sed) << endl;
  return 0;
} 
