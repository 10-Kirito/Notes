#include <iostream>
#include <omp.h>

static long counts = 27;
double step;

int main (int argc, char *argv[])
{
  int i;
  long sum = 0;
  long thrdSum[4];
  omp_set_num_threads(4);
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    thrdSum[id] = 0;

    #pragma omp parallel for
    for (i = 1; i <= 100000000; i++) {
      thrdSum[id] += i;
    }
  }

  for (i = 0; i < 4; i++) {
    sum += thrdSum[i];
  }

  std::cout << "结果为："<< sum << std::endl;
  return 0;
}
