#include "Ransac.h"

Ransac::Ransac() {
  x.resize(N);
  y.resize(N);
}

void Ransac::init(int Z[N], const int T[N]) {
  for (int i = 0; i < N; i++) {
    this->x[i] = T[i] - 25;
    this->y[i] = log10(Z[i]);
  }
}

void Ransac::iter() {
  // RANSAC iterates begin
  std::cout << "Calculation RANSAC...\n\n";

  for (int i = 1; i <= MAX_ITERATIONS; i++) {
    // Model m(12, x,  y);
    Model m;
    bool success = m.setIndexes(12, indexPairs, x, y);

    if (!success) {
      break;
    }

    m.getParams();
    m.getEpsilon(x, y);

    models.push_back(m);
  }
}

bool isIndLess(Model a, Model b) { return (a.indexes.first < b.indexes.first); }

void Ransac::printAll() {
  // Debug method
  sort(models.begin(), models.end(), isIndLess);

  for (int i = 0; i < models.size(); i++) {
    std::cout << std::setw(3) << i + 1 << std::setw(8) << "("
              << models[i].indexes.first << ", ";
    std::cout << models[i].indexes.second << ")"
              << "\n";
  }
}

bool isEpsLess(Model a, Model b) { return (a.currentEpsilon < b.currentEpsilon); }

void Ransac::result() {
  sort(models.begin(), models.end(), isEpsLess);

  Model m = models[0];

  std::cout << "RANSAC parameters: \n";
  std::cout << "k = " << m.k << " b = " << m.b << " eps = " << m.currentEpsilon
            << "\n\n";

  double R0 = pow(10, m.b);

  std::cout << "RANSAC result: \n";
  std::cout << "Z = R0 * 10 ^ (k * (T - T0))\n";

  std::cout << "Z = " << R0 << " * 10^(" << m.k << " * (T - T0) \n\n";
}
