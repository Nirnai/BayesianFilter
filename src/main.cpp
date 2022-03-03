#include <iostream>
#include <memory>
#include <random>

#include "core/distributions/gaussian.hpp"
#include "core/filters/welfords_algorithm.hpp"

using namespace distributions;
using namespace filters;

int main() {
  double mean = 0.0;
  double variance = 1.0;
  auto gaussian = Gaussian(mean, variance);
  std::cout << typeid(gaussian).name() << std::endl;
  double probability_density = gaussian.density(mean);
  std::cout << probability_density << std::endl;

  return 0;
}