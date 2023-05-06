#include <iostream>
#include <omp.h>

using namespace std;

int main (int argc, char *argv[])
{
  int nthreads, tid;

  // 指定我们所申请的线程的数目
  omp_set_num_threads(4);
  #pragma omp parallel private(nthreads, tid) 
  {
    tid = omp_get_thread_num();
    
    cout << "Hello World from OMP thread " << tid << endl;
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      cout << "Number of threads is" << nthreads << endl;
    }
  }





  return 0;
}
