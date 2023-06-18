#include <iostream>
#include <omp.h>

int main (int argc, char *argv[])
{
  int sum = 100;
  #pragma omp parallel for private(sum) num_threads(4)
  for (int i = 0; i < 10; i++) {
#pragma omp critical
    std::cout << "sum:" << sum << std::endl;
    // sum += i;
  }
  std::cout << "Sum: "<< sum << std::endl;
  return 0;
} 
