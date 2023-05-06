#include <iostream>
#include <omp.h>

using namespace std;

int main (int argc, char *argv[])
{
  
  // 指定我们所申请的线程的数目
  // omp_set_num_threads(4);
  #pragma omp parallel num_threads(16) 
  {
    int ID = omp_get_thread_num();
    printf("hello(%d)", ID);
    printf("world(%d)\n", ID);
  }





  return 0;
}
