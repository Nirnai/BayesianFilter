#pragma once

#include <iostream>
#include <Eigen/Dense>

#include "dimensions.hpp"

using namespace Eigen;
using namespace dimension;

template <class... Dimensions>
class State {
 public:
  State(Dimensions... dimensions)
      : data_(VectorXd::Zero(getDimension())), format_(StreamPrecision, DontAlignCols, ",", ",", "", "", "", "") {
    std::tuple<Dimensions...> dimensions_tuple{dimensions...};
    unpack(dimensions_tuple);
  }

  friend std::ostream &operator<<(std::ostream &output, const State &state) {
    output << state.data_.format(state.format_);
    return output;
  }

  friend State operator+(const State &lhs, const State &rhs) { return lhs.data_ + rhs.data_; }

  size_t getDimension() { return std::tuple_size<std::tuple<Dimensions...>>::value; }

  template <size_t I = 0>
  typename std::enable_if<I == sizeof...(Dimensions), void>::type unpack(std::tuple<Dimensions...> tuple) {
    return;
  }

  template <size_t I = 0>
      typename std::enable_if < I<sizeof...(Dimensions), void>::type unpack(std::tuple<Dimensions...> tuple) {
    data_[I] = std::get<I>(tuple).value;
    unpack<I + 1>(tuple);
  }

 private:
  VectorXd data_;
  IOFormat format_;
};
