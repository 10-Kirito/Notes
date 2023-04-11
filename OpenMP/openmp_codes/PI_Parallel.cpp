#include <iterator>
#include <omp.h>
#include <chrono>
#include <iostream>
using namespace std;
static long num_steps = 100000000;
static double step;
#define NUM_THREAD 4
int main (int argc, char *argv[])
{
  int i, nthreads;
  double pi, sum[NUM_THREAD];

  step = 1.0/(double) num_steps;
  omp_set_num_threads(NUM_THREAD);

  chrono::milliseconds start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()); 
  double test_start = omp_get_wtime();
  #pragma omp parallel
  {
    int i, id, nthrds;
    double x;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    if(id == 0) 
      nthreads = nthrds;
    for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthrds) {
      x = (i + 0.5) * step;
      sum[id] += 4.0/(1.0 + x * x);
    }
  }
  double test_end = omp_get_wtime();


  for (i = 0; i < nthreads; i++) {
    pi += sum[i]*step;
  }
  chrono::milliseconds end = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

  std::cout << "The threads number is: " << nthreads << std::endl;
  cout << "result: " << pi << endl;
  cout << "cost: " << chrono::milliseconds(end).count() - chrono::milliseconds(start).count() << "ms" << endl;
  std::cout << "parallel cost: " << test_end - test_start << std::endl;
  return 0;
}
