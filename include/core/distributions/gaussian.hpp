#pragma once

#include <cmath>

#include "core/math.hpp"

namespace distributions {

template <typename MeanType, typename CovarianceType>
class Gaussian {
 public:
  Gaussian(const MeanType &mean, const CovarianceType &covariance) : mean_(mean), covariance_(covariance) {}
  const MeanType &getMean() { return mean_; }
  const CovarianceType &getCovariance() { return covariance_; }
  void setMean(const MeanType &mean) { mean_ = mean; }
  void setCovariance(const CovarianceType &covariance) { covariance_ = covariance; }
  /// HINT: Not static because type deduction for static member functions is not possible
  double mahalanobisDistance(MeanType sample, MeanType mean, CovarianceType covariance) {
    /// HINT: c++20: add concept of transposable and invertable
    return math::transpose(sample - mean) * math::inverse(covariance) * (sample - mean);
  }
  /// HINT: Not static because type deduction for static member functions is not possible
  double probabilityDensity(MeanType sample, MeanType mean, CovarianceType covariance) {
    /// HINT: c++20: add concept of matrix determinant
    return std::exp(-0.5 * mahalanobisDistance(sample, mean, covariance)) /
           std::sqrt(std::pow((2 * M_PI), math::dimension(mean)) * math::determinant(covariance));
  }
  double mahalanobisDistance(MeanType sample) { return mahalanobisDistance(sample, mean_, covariance_); }
  double probabilityDensity(MeanType sample) { return probabilityDensity(sample, mean_, covariance_); }

 private:
  MeanType mean_;
  CovarianceType covariance_;
};

/// HINT: Work in progress
class GaussianMixtureModel {};

class Bernoulli {};

class MultiBernoulli {};

class Poisson {};

}  // namespace distributions