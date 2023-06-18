#include <iostream>
#include <omp.h>

int main (int argc, char *argv[])
{
  int sum = 0;

  #pragma omp parallel for num_threads(4) reduction(+:sum)
  for (int i = 0; i <= 100; i++) {
    sum +=i; 
  }

  std::cout << "result:" << sum << std::endl;
  omp_set_num_threads(4);
  #pragma omp parallel 
  {
    #pragma omp for 
    for (int i = 0; i < 10; i++) {
      #pragma omp critical
      std::cout << "Hello, " << omp_get_thread_num() << std::endl;
    }
    #pragma omp critical 
    std::cout << "This is " << omp_get_thread_num() << std::endl;
  }
  
  #pragma omp parallel num_threads(4)
  {
    #pragma omp for
    for (int i = 0; i < 10; i++) {
      #pragma omp critical
      std::cout << "World " << omp_get_thread_num() << std::endl;
    }
    #pragma omp critical
    std::cout << "For " << omp_get_thread_num() << std::endl;
  }



  return 0;
}
