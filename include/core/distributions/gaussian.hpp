#pragma once

#include <functional>
#include <numbers>
#include <type_traits>

namespace distributions {

/* Concepts */
template <typename T>
concept VectorType = requires(T v) {
  {v.transpose()};
  {v.size()};
};

template <typename T>
concept MatrixType = requires(T m) {
  {m.transpose()};
  {m.determinant()};
  {m.inverse()};
};

/* Scalar Wrapper */
template <typename ScalarType>
class Scalar {
 public:
  Scalar() = default;
  Scalar(ScalarType value) : value_(value) {}
  auto transpose() -> ScalarType { return value_; }
  auto determinant() -> ScalarType { return value_; }
  auto inverse() -> ScalarType { return 1.0 / value_; }
  auto size() -> size_t { return 1; }
  /* Implicit Conversion */
  operator ScalarType() const { return value_; }
  /* Operators */
  auto operator[](int i) -> ScalarType & { return value_; }
  auto operator+(const Scalar &other) const -> Scalar {
    return Scalar(value_ + other.value_);
  }
  auto operator-(const Scalar &other) const -> Scalar {
    return Scalar(value_ - other.value_);
  }
  auto operator*(const Scalar &other) const -> Scalar {
    return Scalar(value_ * other.value_);
  }

 private:
  ScalarType value_;
};

template <VectorType MeanType, MatrixType CovarianceType>
class Gaussian {
  using ScalarType = typename std::decay<decltype(MeanType()[0])>::type;

 public:
  Gaussian(const MeanType &mean, const CovarianceType &covariance)
      : mean_(mean), covariance_(covariance) {}
  auto getMean() const -> MeanType const & { return mean_; }
  auto getCovariance() const -> CovarianceType const & { return covariance_; }

  auto distance(MeanType sample) -> ScalarType {
    return (sample - mean_).transpose() * covariance_.inverse() *
           (sample - mean_);
  }
  auto density(MeanType sample) -> ScalarType {
    return std::exp(-0.5 * distance(sample)) /
           (std::sqrt(std::pow(2 * std::numbers::pi, sample.size())) *
            covariance_.determinant());
  }
  auto updateMean(std::function<MeanType(MeanType const &mean)> estimator)
      -> void {
    mean_ = estimator(mean_);
  }
  auto updateCovariance(
      std::function<CovarianceType(CovarianceType mean)> estimator) {
    covariance_ = estimator(covariance_);
  }

 private:
  MeanType mean_;
  CovarianceType covariance_;
};

/* Deduction Guides */
Gaussian(double, double)->Gaussian<Scalar<double>, Scalar<double>>;
Gaussian(float, float)->Gaussian<Scalar<float>, Scalar<float>>;

}  // namespace distributions