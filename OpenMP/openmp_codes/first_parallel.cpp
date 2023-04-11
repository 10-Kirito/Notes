#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;

static long num_step = 10000000;
double step;
int main (int argc, char *argv[])
{
  int i;
  double x, pi, sum = 0.0;
  
  step = 1.0/(double) num_step;

  double results[8];
  double start_time = omp_get_wtime();
  #pragma omp parallel for
  for (i = 0; i < num_step; ++i) {
    x = (i + 0.5) * step;
    results[omp_get_thread_num()] = 4.0/(1.0 + x * x);
  }

  for (auto e : results) {
    sum = sum + e;
  }

  double end_time = omp_get_wtime();
  pi = step * sum;
  
  std::cout <<"The result: "<< pi << std::endl;
  cout << "Parallel cost: " << end_time - start_time << endl;
  return 0;
}
