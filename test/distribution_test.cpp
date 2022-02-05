#include <gtest/gtest.h>

#include "core/distributions/gaussian.hpp"

TEST(DistributionTest, GaussianDistribution) {
  double mean = 0.0;
  double variance = 1.0;
  distributions::Gaussian gaussian(mean, variance);
  EXPECT_DOUBLE_EQ(gaussian.probabilityDensity(mean), 0.3989422804014327);

  double total_probability;
  double bound = 10.0;
  double discretization = 0.1;
  for (double x = -bound; x < bound; x += discretization) {
    total_probability += gaussian.probabilityDensity(x) * discretization;
  }
  EXPECT_NEAR(total_probability, 1.0, 1e-6);
}

TEST(DistributionTest, MultivariateGaussianDistribution) {
  Eigen::Vector2d mean = Eigen::Vector2d::Zero();
  Eigen::Matrix2d covariance = Eigen::Matrix2d::Identity();
  distributions::Gaussian gaussian(mean, covariance);
  EXPECT_DOUBLE_EQ(gaussian.probabilityDensity(mean), std::pow(0.3989422804014327, 2));

  double total_probability;
  double bound = 10.0;
  double discretization = 0.1;
  for (double x = -bound; x < bound; x += discretization) {
    for (double y = -bound; y < bound; y += discretization) {
      Eigen::Vector2d sample;
      sample << x, y;
      total_probability += gaussian.probabilityDensity(sample) * std::pow(discretization, 2);
    }
  }
  EXPECT_NEAR(total_probability, 1.0, 1e-6);
}