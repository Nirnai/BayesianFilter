#include <gtest/gtest.h>

#include "core/distributions/gaussian.hpp"

TEST(DistributionTest, GaussianDistribution) {
  double mean = 0.0;
  double variance = 1.0;
  double probability_density;
  probability_density = distributions::Gaussian<double, double>::probabilityDensity(mean, mean, variance);
  EXPECT_DOUBLE_EQ(probability_density, 0.3989422804014327);
  distributions::Gaussian gaussian(mean, variance);
  probability_density = gaussian.probabilityDensity(mean);
  EXPECT_DOUBLE_EQ(probability_density, 0.3989422804014327);
  probability_density = gaussian.probabilityDensity(mean, mean, variance);
  EXPECT_DOUBLE_EQ(probability_density, 0.3989422804014327);

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
  double probability_density;
  probability_density =
      distributions::Gaussian<Eigen::Vector2d, Eigen::Matrix2d>::probabilityDensity(mean, mean, covariance);
  EXPECT_DOUBLE_EQ(probability_density, std::pow(0.3989422804014327, 2));
  distributions::Gaussian gaussian(mean, covariance);
  probability_density = gaussian.probabilityDensity(mean);
  EXPECT_DOUBLE_EQ(probability_density, std::pow(0.3989422804014327, 2));
  probability_density = gaussian.probabilityDensity(mean, mean, covariance);
  EXPECT_DOUBLE_EQ(probability_density, std::pow(0.3989422804014327, 2));

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