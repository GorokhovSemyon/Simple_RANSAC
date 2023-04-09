#include <fstream>
#include <iostream>

#include "Ransac.h"

void fillArrays(int Z[], int T[]) {
  // Path to file can be different
  std::ifstream infile("input.txt");
  if (!infile) {
    std::cout << "Error opening file!" << std::endl;
    return;
  }

  int Zi, Ti;
  int num_values = 0;
  while (infile >> Zi >> Ti && num_values < N) {
    Z[num_values] = Zi;
    T[num_values] = Ti;
    num_values++;
  }

  infile.close();
}

int main() {
  int Z[N];
  int T[N];

  fillArrays(Z, T);

  Ransac r;
  r.init(Z, T);
  r.iter();
  r.result();
  //  r.printAll();

  return 0;
}
