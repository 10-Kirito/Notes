#include <iostream>
#include <chrono>

using namespace std;

static long num_step = 100000000;
double step;
int main (int argc, char *argv[])
{
  int i;
  double x, pi, sum = 0.0;
  
  step = 1.0/(double) num_step;

  
  chrono::milliseconds start_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
  for (i = 0; i < num_step; ++i) {
    x = (i + 0.5) * step;
    // x = (i + 0.4) * step;
    sum = sum + 4.0/(1.0 + x * x);
  }
  chrono::milliseconds end_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());


  pi = step * sum;
  
  std::cout <<"The result: "<< pi << std::endl;
  cout << "cost time: " <<  chrono::milliseconds(end_time).count() - chrono::milliseconds(start_time).count() << "ms" << endl;

  return 0;
}
