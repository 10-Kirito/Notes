#include <utility>
#include <tuple>
#include <iostream>

int main (int argc, char *argv[])
{
  std::pair<char, char> p = std::make_pair('x', 'y');

  char c;

  std::tie(std::ignore,c) = p;
  return 0;
}
