#include <Eigen/LU>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <unordered_set>
#define AVG 5

typedef std::unordered_set<std::pair<int, int>,
                           boost::hash<std::pair<int, int>>>
    pairsSet;

class Model {
  class Point {
   public:
    double x = 0;
    double y = 0;
  };

  Point pointA;
  Point pointB;

 public:
  std::pair<int, int> indexes;

  double k = 0;
  double b = 0;
  double currentEpsilon = 0;

  Model();
  Model(int IdxRange, std::vector<double> x, std::vector<double> y);

  void getParams();
  void getEpsilon(std::vector<double> x, std::vector<double> y);
  bool setIndexes(int range, pairsSet &pairs, std::vector<double> x,
                  std::vector<double> y);
};
