#pragma once

namespace filters {

class WelfordsAlgorithm {
 public:
  auto mean(double sample, double mean) -> double {
    sample_size_++;
    mean_old = mean;
    mean_new = mean + (sample - mean) / sample_size_;
    return mean_new;
  }
  auto variance(double sample, double mean) -> double {
    sum_squared_differences_ = sum_squared_differences_ + (sample - mean_old) * (sample - mean_new);
    return sum_squared_differences_ / sample_size_;
  }

 private:
  double mean_old;
  double mean_new;
  double sum_squared_differences_;
  size_t sample_size_;
};

}  // namespace filters
