#include "Model.h"

Model::Model() = default;

Model::Model(int range, std::vector<double> x, std::vector<double> y) {
  int first_index = rand() % range;
  int second_index = 0;
  do {
    second_index = rand() % range;
  } while (first_index == second_index);

  indexes = std::make_pair(first_index, second_index);

  pointA.x = x[indexes.first];
  pointA.y = y[indexes.first];
  pointB.x = x[indexes.second];
  pointB.y = y[indexes.second];
}

void Model::getParams() {
  // y = k*x + b
  Eigen::Matrix2d A;
  Eigen::Vector2d B;
  Eigen::Vector2d X;

  A.row(0) << pointA.x, 1;
  A.row(1) << pointB.x, 1;

  B << pointA.y, pointB.y;

  // std::cout << A << "\n\n";
  // std::cout << B << "\n\n";

  X = A.lu().solve(B);

  this->k = X[0];
  this->b = X[1];
}

void Model::getEpsilon(std::vector<double> x, std::vector<double> y) {
  double max_distance = -1;
  double tmp = 0;
  std::vector<double> distances;

  assert(x.size() == y.size());

  for (int j = 0; j < x.size(); j++) {
    if (j == indexes.first || j == indexes.second) continue;

    double A = y[indexes.first] - y[indexes.second];
    double B = x[indexes.first] - x[indexes.second];
    double C = y[indexes.first] * x[indexes.second] -
               y[indexes.second] * x[indexes.first];

    double H = abs((A * x[j] + B * y[j] + C) / sqrt(A * A + B * B));
    // Distance between point and line
    // std::cout << "H = " << H << "\n";

    max_distance = std::max(max_distance, H);
    distances.push_back(max_distance);
  }
  sort(distances.begin(), distances.end());
  for (int i = distances.size() - AVG; i < distances.size(); i++)
    tmp += distances[i];
  currentEpsilon = tmp / AVG;
}

bool Model::setIndexes(int range, pairsSet &pairs, std::vector<double> x,
                       std::vector<double> y) {
  int first_index = 0, second_index = 0;
  int counter = 1000;

  while (counter) {
    first_index = rand() % range;

    do {
      second_index = rand() % range;
    } while (first_index == second_index);

    if (pairs.find(std::make_pair(first_index, second_index)) != pairs.end())
      counter--;
    else
      break;
  }

  if (counter == 0) return false;

  indexes = std::make_pair(first_index, second_index);
  pairs.insert(indexes);

  pointA.x = x[indexes.first];
  pointA.y = y[indexes.first];
  pointB.x = x[indexes.second];
  pointB.y = y[indexes.second];

  return true;
}
