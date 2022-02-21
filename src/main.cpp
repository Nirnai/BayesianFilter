#include <iostream>
#include <memory>
#include <random>

#include "core/distributions/distribution.hpp"
#include "core/distributions/gaussian.hpp"

using namespace distributions;

int main() {
  auto gaussian = std::make_unique<Distribution>(Gaussian(0.0, 1.0), univariate_gaussian::mahalanobisDistance<double>,
                                                 univariate_gaussian::probabilityDensity<double>,
                                                 univariate_gaussian::welfordsUpdate<double>);

  std::random_device rd{};
  std::mt19937 generator{rd()};

  double mean = 5.0;
  double variance = 2.0;
  double standard_deviation = std::sqrt(variance);

  std::normal_distribution<double> sampler{mean, standard_deviation};

  for (int n = 0; n < 10000; ++n) {
    double sample = sampler(generator);
    gaussian->update(sample);
  }

  // for (auto& d : ds) {
  //   std::cout << d.distance(0.0) << std::endl;
  //   std::cout << d.density(0.0) << std::endl;
  //   d.update(5.0);
  // }

  return 0;
}