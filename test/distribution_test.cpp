
#include <random>

#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "core/distributions/gaussian.hpp"
#include "core/filters/welfords_algorithm.hpp"

TEST(DistributionTest, GaussianDistribution) {
  using namespace distributions;
  using namespace filters;

  /// Density at mean
  double mean = 0.0;
  double variance = 1.0;
  double probability_density = Gaussian(mean, variance).density(0.0);
  EXPECT_DOUBLE_EQ(probability_density, 1.0 / std::sqrt(2 * M_PI));

  /// Integral over distribution
  double total_probability;
  double bound = 10.0;
  double discretization = 0.1;
  for (double x = -bound; x < bound; x += discretization) {
    total_probability += Gaussian(mean, variance).density(x) * discretization;
  }
  EXPECT_NEAR(total_probability, 1.0, 1e-6);

  /// Estimator
  std::random_device rd{};
  std::mt19937 generator{rd()};

  mean = 5.0;
  variance = 2.0;
  std::normal_distribution<double> sampler{mean, std::sqrt(variance)};

  auto gaussian = Gaussian(0.0, 0.0);
  auto estimator = WelfordsAlgorithm();

  for (int n = 0; n < 1000; ++n) {
    double sample = sampler(generator);
    gaussian.updateMean(std::bind(&WelfordsAlgorithm::mean, std::ref(estimator), sample, std::placeholders::_1));
    gaussian.updateCovariance(
        std::bind(&WelfordsAlgorithm::variance, std::ref(estimator), sample, std::placeholders::_1));
  }

  EXPECT_NEAR(gaussian.getMean(), 5.0, 1e-1);
  EXPECT_NEAR(gaussian.getCovariance(), 2.0, 1e-1);
}

TEST(DistributionTest, MultivariateGaussianDistribution) {
  using namespace Eigen;
  using namespace distributions;

  Vector2d mean = Vector2d::Zero();
  Matrix2d covariance = Matrix2d::Identity();
  double probability_density = Gaussian(mean, covariance).density(mean);
  EXPECT_DOUBLE_EQ(probability_density, 1.0 / std::sqrt(std::pow(2 * M_PI, 2)));

  double total_probability;
  double bound = 10.0;
  double discretization = 0.1;
  for (double x = -bound; x < bound; x += discretization) {
    for (double y = -bound; y < bound; y += discretization) {
      Vector2d sample;
      sample << x, y;
      total_probability += Gaussian(mean, covariance).density(sample) * std::pow(discretization, 2);
    }
  }
  EXPECT_NEAR(total_probability, 1.0, 1e-6);
}