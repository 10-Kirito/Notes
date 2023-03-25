#include <iostream>

struct
{
  int i;
  char c1;
  char c2;
}x1;

struct
{
 char c1;
 int i;
 char c2;
}x2;

struct
{
  char c1;
  char c2;
  int i;
}x3;

int main (int argc, char *argv[])
{
  
  std::cout << sizeof(x1) << std::endl;
  std::cout << sizeof(x2) << std::endl;
  std::cout << sizeof(x3) << std::endl;

  return 0;
}
