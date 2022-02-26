#pragma once

namespace dimensions {
template <typename T, typename Parameter>
class NamedType {
 public:
  explicit NamedType(T const& value) : value_(value) {}
  explicit NamedType(T&& value) : value_(std::move(value)) {}
  T& get() { return value_; }
  T const& get() const { return value_; }

 private:
  T value_;
};

using Meter = NamedType<double, struct MeterTag>;
using X = NamedType<Meter, struct Xposition>;

}  // namespace dimensions

// namespace dimension {

// struct Dimension {
//   Dimension(int val) : value(val) {}
//   Dimension(float val) : value(val) {}
//   Dimension(double val) : value(val) {}

//   friend std::ostream &operator<<(std::ostream &output, const Dimension &dimension) {
//     output << dimension.value;
//     return output;
//   }

//   double value;
// };

// struct Time : public Dimension {
//   using Dimension::Dimension;
// };

// struct TimeSquared : public Dimension {
//   using Dimension::Dimension;
// };

// struct Position : public Dimension {
//   using Dimension::Dimension;
//   Position(const Position &position) : Dimension(position.value) {}
// };

// struct Orientation : public Dimension {
//   Orientation(double angle) : Dimension(angle) { normalize(); }
//   void normalize() { value = value - (std::floor((value + M_PI) / (2 * M_PI))) * 2 * M_PI; }
// };

// struct LinearVelocity : public Dimension {
//   using Dimension::Dimension;
// };

// struct AngularVelocity : public Dimension {
//   using Dimension::Dimension;
// };

// struct LinearAcceleration : public Dimension {
//   using Dimension::Dimension;
// };

// struct X : public Position {
//   using Position::Position;
//   X(const Position &position) : Position(position){};
// };

// struct Y : public Position {
//   using Position::Position;
//   Y(const Position &position) : Position(position){};
// };

// struct Z : public Position {
//   using Position::Position;
//   Z(const Position &position) : Position(position){};
// };

// struct Roll : public Orientation {
//   using Orientation::Orientation;
// };

// struct Pitch : public Orientation {
//   using Orientation::Orientation;
// };

// struct Yaw : public Orientation {
//   using Orientation::Orientation;
// };

// struct VelocityX : public LinearVelocity {
//   using LinearVelocity::LinearVelocity;
// };

// struct VelocityY : public LinearVelocity {
//   using LinearVelocity::LinearVelocity;
// };

// struct VelocityZ : public LinearVelocity {
//   using LinearVelocity::LinearVelocity;
// };

// struct AccelerationX : public LinearAcceleration {
//   using LinearAcceleration::LinearAcceleration;
// };

// struct AccelerationY : public LinearAcceleration {
//   using LinearAcceleration::LinearAcceleration;
// };

// struct AccelerationZ : public LinearAcceleration {
//   using LinearAcceleration::LinearAcceleration;
// };

// struct RollRate : public AngularVelocity {
//   using AngularVelocity::AngularVelocity;
// };

// struct PitchRate : public AngularVelocity {
//   using AngularVelocity::AngularVelocity;
// };

// struct YawRate : public AngularVelocity {
//   using AngularVelocity::AngularVelocity;
// };

// /**
//  * @brief Addition Operators
//  */

// X operator+(const X &lhs, const X &rhs) { return X(lhs.value + rhs.value); }

// Y operator+(const Y &lhs, const Y &rhs) { return Y(lhs.value + rhs.value); }

// Z operator+(const Z &lhs, const Z &rhs) { return Z(lhs.value + rhs.value); }

// Roll operator+(const Roll &lhs, const Roll &rhs) { return Roll(lhs.value + rhs.value); }

// Pitch operator+(const Pitch &lhs, const Pitch &rhs) { return Pitch(lhs.value + rhs.value); }

// Yaw operator+(const Yaw &lhs, const Yaw &rhs) { return Yaw(lhs.value + rhs.value); }

// VelocityX operator+(const VelocityX &lhs, const VelocityX &rhs) { return VelocityX(lhs.value + rhs.value); }

// VelocityY operator+(const VelocityY &lhs, const VelocityY &rhs) { return VelocityY(lhs.value + rhs.value); }

// VelocityZ operator+(const VelocityZ &lhs, const VelocityZ &rhs) { return VelocityZ(lhs.value + rhs.value); }

// RollRate operator+(const RollRate &lhs, const RollRate &rhs) { return RollRate(lhs.value + rhs.value); }

// PitchRate operator+(const PitchRate &lhs, const PitchRate &rhs) { return PitchRate(lhs.value + rhs.value); }

// YawRate operator+(const YawRate &lhs, const YawRate &rhs) { return YawRate(lhs.value + rhs.value); }

// AccelerationX operator+(const AccelerationX &lhs, const AccelerationX &rhs) {
//   return AccelerationX(lhs.value + rhs.value);
// }

// AccelerationY operator+(const AccelerationY &lhs, const AccelerationY &rhs) {
//   return AccelerationY(lhs.value + rhs.value);
// }

// AccelerationZ operator+(const AccelerationZ &lhs, const AccelerationZ &rhs) {
//   return AccelerationZ(lhs.value + rhs.value);
// }

// /**
//  * @brief Multiplication Operators
//  */

// TimeSquared operator*(const Time &lhs, const Time &rhs) { return TimeSquared(lhs.value * rhs.value); }

// Position operator*(const LinearVelocity &lhs, const Time &rhs) { return Position(lhs.value * rhs.value); }

// Position operator*(const Time &lhs, const LinearVelocity &rhs) { return Position(lhs.value * rhs.value); }

// Orientation operator*(const AngularVelocity &lhs, const Time &rhs) { return Orientation(lhs.value * rhs.value); }

// Orientation operator*(const Time &lhs, const AngularVelocity &rhs) { return Orientation(lhs.value * rhs.value); }

// Position operator*(const LinearAcceleration &lhs, const TimeSquared &rhs) { return Position(lhs.value *
// rhs.value); }

// Position operator*(const TimeSquared &lhs, const LinearAcceleration &rhs) { return Position(lhs.value *
// rhs.value); }

// X operator*(const Time &lhs, const VelocityX &rhs) { return lhs * static_cast<LinearVelocity>(rhs); }

// X operator*(const VelocityX &lhs, const Time &rhs) { return rhs * static_cast<LinearVelocity>(lhs); }

// X operator*(const TimeSquared &lhs, const AccelerationX &rhs) { return lhs *
// static_cast<LinearAcceleration>(rhs); }

// X operator*(const AccelerationX &lhs, const TimeSquared &rhs) { return rhs *
// static_cast<LinearAcceleration>(lhs); }

// Y operator*(const Time &lhs, const VelocityY &rhs) { return lhs * static_cast<LinearVelocity>(rhs); }

// Y operator*(const VelocityY &lhs, const Time &rhs) { return rhs * static_cast<LinearVelocity>(lhs); }

// Y operator*(const TimeSquared &lhs, const AccelerationY &rhs) { return lhs *
// static_cast<LinearAcceleration>(rhs); }

// Y operator*(const AccelerationY &lhs, const TimeSquared &rhs) { return rhs *
// static_cast<LinearAcceleration>(lhs); }

// Z operator*(const Time &lhs, const VelocityZ &rhs) { return lhs * static_cast<LinearVelocity>(rhs); }

// Z operator*(const VelocityZ &lhs, const Time &rhs) { return rhs * static_cast<LinearVelocity>(lhs); }

// Z operator*(const TimeSquared &lhs, const AccelerationZ &rhs) { return lhs *
// static_cast<LinearAcceleration>(rhs); }

// Z operator*(const AccelerationZ &lhs, const TimeSquared &rhs) { return rhs *
// static_cast<LinearAcceleration>(lhs); }

// }  // namespace dimension