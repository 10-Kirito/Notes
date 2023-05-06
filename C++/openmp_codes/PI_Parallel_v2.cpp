#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;

static long num_step = 100000000;
double step;
#define NUM_THREADS 8
int main (int argc, char *argv[])
{
  
  double pi = 0.0;
  step = 1.0/(double) num_step;
  int number;

  
  chrono::milliseconds start_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {
    int i, id, nthreads;
    double x, sum;
    id = omp_get_thread_num();
    nthreads = omp_get_num_threads();
    if (id == 0) {
      number = nthreads;
    }
    #pragma omp for
    for (i = 0; i < num_step; ++i) {
      x = (i + 0.5) * step;
      // x = (i + 0.4) * step;
      sum = sum + 4.0/(1.0 + x * x);
    }
    #pragma omp critical
    pi += step * sum;
  }
  chrono::milliseconds end_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());


  
  std::cout <<"The result: "<< pi << std::endl;
  cout << "cost time: " <<  chrono::milliseconds(end_time).count() - chrono::milliseconds(start_time).count() << "ms" << endl;

  return 0;
}
