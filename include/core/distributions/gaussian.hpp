#pragma once

#include <cmath>

namespace distributions {

template <typename MeanType, typename CovarianceType>
class Gaussian {
 public:
  using SampleType = MeanType;
  explicit Gaussian(const MeanType &mean, const CovarianceType &covariance)
      : mean_(mean), covariance_(covariance), sample_size_(0) {}
  auto getMean() const -> MeanType { return mean_; }
  auto getCovariance() const -> CovarianceType { return covariance_; }
  auto getSampleSize() const -> size_t { return sample_size_; }

  auto setMean(const MeanType &mean) -> void { mean_ = mean; }
  auto setCovariance(const CovarianceType &covariance) -> void { covariance_ = covariance; }
  /// TODO: Add overflow handling
  auto setSampleSize(int i) -> void { sample_size_ = i; }

 private:
  MeanType mean_;
  CovarianceType covariance_;
  size_t sample_size_;
};

namespace univariate_gaussian {

template <typename Scalar>
Scalar mahalanobisDistance(Gaussian<Scalar, Scalar> const &g, Scalar const &sample) {
  return std::pow(sample - g.getMean(), 2) / g.getCovariance();
}

template <typename Scalar>
Scalar probabilityDensity(Gaussian<Scalar, Scalar> const &g, Scalar const &sample) {
  return std::exp(-0.5 * mahalanobisDistance(g, sample)) / (std::sqrt(2.0 * M_PI * g.getCovariance()));
}

template <typename Scalar>
void welfordsUpdate(Gaussian<Scalar, Scalar> &g, Scalar const &sample) {
  size_t n_old = g.getSampleSize();
  size_t n_new = n_old + 1;
  g.setSampleSize(n_new);

  auto mean_old = g.getMean();
  auto mean_new = mean_old + (sample - mean_old) / n_new;
  g.setMean(mean_new);

  auto var_old = g.getCovariance();

  /// HINT: Update Squared Sum of differences for numerical stability
  auto M_old = var_old * n_old;
  auto M_new = M_old + (sample - mean_old) * (sample - mean_new);
  auto var_new = M_new / n_new;
  g.setCovariance(var_new);
  std::cout << "mean: " << g.getMean() << " var: " << g.getCovariance() << " n: " << g.getSampleSize() << std::endl;
}

}  // namespace univariate_gaussian

namespace multivariate_gaussian {
template <typename MeanType, typename CovarianceType>
double mahalanobisDistance(Gaussian<MeanType, CovarianceType> const &g, MeanType const &sample) {
  return (sample - g.getMean()).transpose() * g.getCovariance().inverse() * (sample - g.getMean());
}

template <typename MeanType, typename CovarianceType>
double probabilityDensity(Gaussian<MeanType, CovarianceType> const &g, MeanType const &sample) {
  return std::exp(-0.5 * mahalanobisDistance(g, sample)) / std::sqrt(std::pow(2 * M_PI, sample.rows())) *
         g.getCovariance().determinant();
}

template <typename MeanType, typename CovarianceType>
void noOp(Gaussian<MeanType, CovarianceType> const &g, MeanType const &sample) {}

}  // namespace multivariate_gaussian

// constexpr static double mahalanobisDistance(MeanType sample, MeanType mean, CovarianceType covariance) {
//   return math::transpose(sample - mean) * math::inverse(covariance) * (sample - mean);
// }
// constexpr static double probabilityDensity(MeanType sample, MeanType mean, CovarianceType covariance) {
//   return std::exp(-0.5 * mahalanobisDistance(sample, mean, covariance)) /
//          std::sqrt(std::pow((2 * M_PI), math::dimension(mean)) * math::determinant(covariance));
// }
// double mahalanobisDistance(MeanType sample) { return mahalanobisDistance(sample, mean_, covariance_); }
// double probabilityDensity(MeanType sample) { return probabilityDensity(sample, mean_, covariance_); }

}  // namespace distributions