#include <iostream>
#include <omp.h>

int main (int argc, char *argv[])
{
  int sum = 100;
  #pragma omp parallel for reduction(+:sum) num_threads(4)
  for (int i = 0; i < 10; i++) {
    sum += i;
    sum = 1;
  }
  std::cout << "Sum: "<< sum << std::endl;
  return 0;
} 
