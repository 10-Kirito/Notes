#include <iostream>
#include <chrono>
#include <iterator>
#include <thread>

using namespace std;
using namespace chrono;

// O(n)
//
void function1(long long n) {
  long long k = 0;
  for (long long  i = 0; i < n; i++) {
    k++;
  }
}

// O(n^2)
//
void function2(long long n) {
  long long k = 0;
  for (long long  i = 0; i < n; i++) {
    for (long long  i = 0; i < n; i++) {
      k++;
    }
  }
}

// O(nlogn)
//
void function3(long long n) {
  long long k = 0;
  for (long long  i = 0; i < n; i++) {
    for (long long  j = 1; j < n; j = j*2) {
      k++;
    }
  }
}


int main (int argc, char *argv[])
{
  long long n;
  cout << "Inout n:";
  cin >> n;
  while (n) {
    milliseconds start_time = duration_cast<milliseconds >(
        system_clock::now().time_since_epoch()
        );
    function1(n);
    // function2(n);
    // function3(n);
    //
    milliseconds end_time = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );
    cout << "cost:" << milliseconds(end_time).count() - milliseconds(start_time).count() << "ms" << endl;
    cout << "Input n:";
    cin >> n;
  }

  return 0;
}
