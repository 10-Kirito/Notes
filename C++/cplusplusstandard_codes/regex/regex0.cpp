#include <regex>
#include <iostream>

using namespace std;

void out(bool b){
  cout << (b ? "found" : "not found") << endl;
}

int main (int argc, char *argv[])
{
  //1. find XML/HTML-tagged value(using default syntax);
  regex reg1("<.*>.*</.*>");
  bool found = regex_match("<tag>value</tag>",
                          reg1);
  out(found);
  
  //2. find XML/HTML-tagged value(tags before and after the value must match);
  regex reg2("<(.*)>.*</\\1>");
  out(regex_match("<tag>value</head>>", reg2));

  //3. C++11 new : RAW STRING
  regex reg3(R"(<(.*)>.*</\1>)");
  out(regex_match("<tag><value</head>>", reg3));

  //4. 
  //
  regex reg4("<\\(.*\\)>.*</\\1>", regex_constants::grep);

  out(regex_match("<tag><value</head>>", reg4));
  return 0;
}
