#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "core/distributions/distribution.hpp"
#include "core/distributions/gaussian.hpp"

TEST(DistributionTest, GaussianDistribution) {
  using namespace distributions;
  using namespace univariate_gaussian;

  double mean = 0.0;
  double variance = 1.0;
  double probability_density = probabilityDensity(Gaussian(mean, variance), mean);
  EXPECT_DOUBLE_EQ(probability_density, 0.3989422804014327);

  auto gaussian = std::make_unique<Distribution>(Gaussian(0.0, 1.0), mahalanobisDistance<double>,
                                                 probabilityDensity<double>, welfordsUpdate<double>);
  double total_probability;
  double bound = 10.0;
  double discretization = 0.1;
  for (double x = -bound; x < bound; x += discretization) {
    total_probability += gaussian->density(x) * discretization;
  }
  EXPECT_NEAR(total_probability, 1.0, 1e-6);
}

TEST(DistributionTest, MultivariateGaussianDistribution) {
  using namespace Eigen;
  using namespace distributions;
  using namespace multivariate_gaussian;

  Vector2d mean = Vector2d::Zero();
  Matrix2d covariance = Matrix2d::Identity();
  double probability_density = probabilityDensity(Gaussian(mean, covariance), mean);
  EXPECT_DOUBLE_EQ(probability_density, std::pow(0.3989422804014327, 2));

  auto gaussian = std::make_unique<Distribution>(Gaussian(mean, covariance), mahalanobisDistance<Vector2d, Matrix2d>,
                                                 probabilityDensity<Vector2d, Matrix2d>, noOp<Vector2d, Matrix2d>);
  double total_probability;
  double bound = 10.0;
  double discretization = 0.1;
  for (double x = -bound; x < bound; x += discretization) {
    for (double y = -bound; y < bound; y += discretization) {
      Vector2d sample;
      sample << x, y;
      total_probability += gaussian->density(sample) * std::pow(discretization, 2);
    }
  }
  EXPECT_NEAR(total_probability, 1.0, 1e-6);
}