#include <iostream>
#include <unistd.h>
#include <omp.h>

int main (int argc, char *argv[])
{
  int nthreads, tid;

  omp_set_num_threads(8);
  
  #pragma omp parallel private(nthreads, tid) 
  {
    tid = omp_get_thread_num();
    sleep(tid);
    std::cout << "Hello World from thread "<< tid << std::endl;
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      sleep(nthreads);
      std::cout << "Number of threads is "<< nthreads << std::endl;
    }
  }

  return 0;
}
