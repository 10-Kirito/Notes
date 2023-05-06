#include <iostream>
#include <iterator>
#include <omp.h>

void test()
{
  for (int i = 0; i < 80000; i++) {
  
  }
}


int main (int argc, char *argv[])
{
  float startTime = omp_get_wtime();

  #pragma omp parallel for num_threads(2)
    for (int i = 0; i < 80000; i++) {
      test(); 
    }

  float endTime = omp_get_wtime();
  std::cout << "指定两个线程，执行时间为：" << endTime - startTime << "s" << std::endl;
  startTime = endTime;

  #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 80000; i++) {
      test();
    }
  endTime = omp_get_wtime();

  std::cout << "指定四个线程，执行时间为："<< endTime - startTime <<"s"<< std::endl;
  startTime = endTime;

  #pragma omp parallel for num_threads(8)
    for (int i = 0; i < 80000; i++) {
    
    test();
    }
  endTime = omp_get_wtime();

  std::cout << "指定八个进程，执行时间为："<<endTime - startTime <<"s"<< std::endl;
  startTime = endTime;

  #pragma omp parallel for num_threads(12)
    for (int i = 0; i < 80000; i++) {
    
    test();
    }
  endTime = omp_get_wtime();

  std::cout << "指定12个进程，执行时间为："<<endTime - startTime <<"s"<< std::endl;
  return 0;
}
