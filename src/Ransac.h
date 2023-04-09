#include <iomanip>

#include "Model.h"

#define MAX_ITERATIONS 500
const int N = 12;

// ln Z = k*T + ln C

class Ransac {
 public:
  std::vector<double> y;
  std::vector<double> x;

  std::vector<Model> models;
  pairsSet indexPairs;

  Ransac();

  void init(int Z[N], const int X[N]);
  void iter();
  void result();
  void printAll();
};
