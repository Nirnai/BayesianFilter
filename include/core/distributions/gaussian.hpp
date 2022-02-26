#pragma once

#include <cmath>
#include <functional>

#include "core/linear_algebra.hpp"

namespace distributions {

template <typename MeanType, typename CovarianceType>
class Gaussian {
 public:
  explicit Gaussian(const MeanType &mean, const CovarianceType &covariance) : mean_(mean), covariance_(covariance) {}
  auto getMean() const -> MeanType const & { return mean_; }
  auto getCovariance() const -> CovarianceType const & { return covariance_; }
  auto distance(MeanType sample) -> double {
    return linear_algebra::transpose(sample - mean_) * linear_algebra::inverse(covariance_) * (sample - mean_);
  }
  auto density(MeanType sample) -> double {
    return std::exp(-0.5 * distance(sample)) / (std::sqrt(std::pow(2 * M_PI, linear_algebra::dimension(sample))) *
                                                linear_algebra::determinant(covariance_));
  }
  auto updateMean(std::function<MeanType(MeanType const &mean)> estimator) -> void { mean_ = estimator(mean_); }
  auto updateCovariance(std::function<CovarianceType(CovarianceType mean)> estimator) {
    covariance_ = estimator(covariance_);
  }

 private:
  MeanType mean_;
  CovarianceType covariance_;
};

}  // namespace distributions