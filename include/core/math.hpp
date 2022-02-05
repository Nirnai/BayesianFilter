#include <Eigen/Dense>

namespace math {

/// Dimension
template <typename Derived>
auto dimension(const Eigen::MatrixBase<Derived> &matrix) {
  return matrix.rows();
}
float dimension(float scalar) { return 1; }
double dimension(double scalar) { return 1; }

/// Transpose
template <typename Derived>
auto transpose(const Eigen::MatrixBase<Derived> &matrix) {
  return matrix.transpose();
}
float transpose(float scalar) { return scalar; }
double transpose(double scalar) { return scalar; }

/// Determinant
template <typename Derived>
auto determinant(const Eigen::MatrixBase<Derived> &matrix) {
  return matrix.determinant();
}
float determinant(float scalar) { return scalar; }
double determinant(double scalar) { return scalar; }

/// Inverse
template <typename Derived>
auto inverse(const Eigen::MatrixBase<Derived> &matrix) {
  return matrix.inverse();
}
float inverse(float scalar) { return 1.f / scalar; }
double inverse(double scalar) { return 1.0 / scalar; }

}  // namespace math
