#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
typedef std::vector<std::vector<int>> MATRIX_INT;

struct Error
{
  double Max;
  double average;
};
#define max 2500

void initialize(MATRIX_INT & array) {
  for (int i = 0; i < max; i++) {
    array.emplace_back();
    for (int j = 0; j < max; j++) {
      array[i].emplace_back(rand() % 100);
    }   
  }
}

void display(const MATRIX_INT & array) {
  for (auto e : array) {
    for (auto g : e) {
        std::cout << g << " "; 
    }
    std::cout << std::endl;
  }
}

MATRIX_INT calc_common(const MATRIX_INT &a, const MATRIX_INT &b) {
  MATRIX_INT result(max, std::vector<int> (max, 0));
  int i, j, k;
    for (i = 0; i < max; i++) {
      for (j = 0; j < max; j++) {
        int temp = 0;
        for (k = 0; k < max; k++) {
          temp += a[i][k]* b[k][j];
        }
        result[i][j] = temp;
      }
    }
  return result;
}


MATRIX_INT calc_parallel(const MATRIX_INT &a, const MATRIX_INT &b) {
  MATRIX_INT result(max, std::vector<int> (max, 0));
  int i, j, k;
  omp_set_num_threads(8);
  #pragma omp parallel for shared(a, b, result) private(j, k) schedule(dynamic)  
    // #pragma omp parallel for 
    for (i = 0; i < max; i++) {
      for (j = 0; j < max; j++) {
        int temp = 0;
        for (k = 0; k < max; k++) {
          temp += a[i][k]* b[k][j];
        }
        result[i][j] = temp;
      }
    }
  return result;
}

Error Checkresult(const MATRIX_INT &a, const MATRIX_INT & b) {
  Error error;
  error.Max= 0.0;
  error.average = 0.0;
  for (int i = 0; i < max; i++) {
    for (int j = 0.0; j < max; j++) {
      if (a[i][j] != b[i][j]) {
        double temp =(double) std::abs(a[i][j] - b[i][j]) / b[i][j];
        if (temp > error.Max) {
          error.Max = temp;
        }
        error.average += temp;
      }
    } 
  }

  return error;

}



int main (int argc, char *argv[])
{
  MATRIX_INT matrix_1;
  MATRIX_INT matrix_2;
  MATRIX_INT result;

  initialize(matrix_1);
  initialize(matrix_2);

  std::cout << "Initialize Matrix_1 finished" << std::endl;
  // display(matrix_1);
  std::cout << "Initialize Matrix_2 finished" << std::endl;
  // display(matrix_2);




  std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  result = calc_parallel(matrix_1, matrix_2);

  std::chrono::milliseconds end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); 

  std::cout << "Result: " << std::endl;
  // display(result);
  
  std::cout << "Cost time: " << std::chrono::milliseconds(end).count() - std::chrono::milliseconds(start).count()<<" ms" << std::endl;

  
  Error error = Checkresult(result, calc_common(matrix_1, matrix_2));
  std::cout << "The Max of error is :" << error.Max << std::endl<<"Average Error is :" << error.average<< std::endl;




}
