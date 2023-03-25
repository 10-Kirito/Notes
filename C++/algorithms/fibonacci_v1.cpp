#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

int fibonacci(int i) {
  if (i <= 0) return 0;
  if (i == 1) return 1;
  
  return fibonacci(i - 1) + fibonacci(i - 2);
}

int fibonacci(int first, int second, int n) {
  if (n <= 0) return 0;
  if (n < 3)
    return 1;
  else if (n == 3)
    return first + second;
  else
    return fibonacci(second, first + second, n - 1);
}

void time_consumption() {
  int n;
  cout << "Please input n: ";
  cin >> n;
  while (n) {
    milliseconds start_time = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );

    // fibonacci(n);
    fibonacci(1, 1, n);
    milliseconds end_time = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );

    cout << "start_time: " << milliseconds(start_time).count() << "ms" << endl; 

    cout << "end_time: " << milliseconds(end_time).count() << "ms" << endl; 

    cout << milliseconds(end_time).count() - milliseconds(start_time).count() << "ms" << endl;

    cout << endl << "Please input n: ";
    cin >> n;
  }
}


int main (int argc, char *argv[])
{
  time_consumption();
  return 0;
}
