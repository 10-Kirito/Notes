#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>

typedef std::vector<std::vector<int>> MATRIX_INT;
#define max 2000

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

MATRIX_INT calc(const MATRIX_INT &a, const MATRIX_INT &b) {
  MATRIX_INT result(max, std::vector<int> (max, 0));
  for (int i = 0; i < max; i++) {
    for (int j = 0; j < max; j++) {
      for (int k = 0; k < max; k++) {
        result[i][j] += a[i][k]* b[k][j];
      }
    }
  }
  return result;
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
  result = calc(matrix_1, matrix_2);

  std::chrono::milliseconds end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); 

  std::cout << "Result: " << std::endl;
  // display(result);
  
  std::cout << "Cost time: " << std::chrono::milliseconds(end).count() - std::chrono::milliseconds(start).count()<<" ms" << std::endl;




}
