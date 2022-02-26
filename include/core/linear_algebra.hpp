#pragma once

#include <Eigen/Dense>

namespace linear_algebra {

auto dimension(double scalar) -> size_t { return 1; }
auto transpose(double scalar) -> double { return scalar; }
auto determinant(double scalar) -> double { return scalar; }
auto inverse(double scalar) -> double { return 1.0 / scalar; }

template <typename Derived>
auto dimension(const Eigen::MatrixBase<Derived>& vector) -> auto {
  return vector.size();
}
template <typename Derived>
auto determinant(const Eigen::MatrixBase<Derived>& matrix) -> auto {
  return matrix.determinant();
}
template <typename Derived>
auto transpose(const Eigen::MatrixBase<Derived>& matrix) -> auto {
  return matrix.transpose();
}
template <typename Derived>
auto inverse(const Eigen::MatrixBase<Derived>& matrix) -> auto {
  return matrix.inverse();
}

}  // namespace linear_algebra
