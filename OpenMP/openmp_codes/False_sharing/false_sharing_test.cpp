#include <iostream>
#include <omp.h>

static long counts = 27;
double step;

int main (int argc, char *argv[])
{
  int i;
  long sum = 0;
  for (i = 1; i <= 100000000; i++) {
    sum+=i;
  }

  std::cout << "结果为："<< sum << std::endl;
  return 0;
}
