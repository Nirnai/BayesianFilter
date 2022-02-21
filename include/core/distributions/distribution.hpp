#pragma once

#include <memory>

namespace distributions {

class Distribution {
 public:
  template <typename DistributionType, typename DistanceStrategy, typename DensityStrategy, typename UpdateStrategy>
  Distribution(DistributionType const& distribution, DistanceStrategy distance_strategy,
               DensityStrategy density_strategy, UpdateStrategy update_strategy)
      : pimpl_(new DistributionModel<DistributionType, DistanceStrategy, DensityStrategy, UpdateStrategy>(
            distribution, distance_strategy, density_strategy, update_strategy)) {}
  Distribution(Distribution const& d);
  Distribution& operator=(Distribution const& d);
  Distribution(Distribution&& d) = default;
  Distribution& operator=(Distribution&& d) = default;

  template <typename SampleType>
  auto distance(SampleType const& sample) -> double {
    return static_cast<DistributionInterface<SampleType>*>(pimpl_.get())->distance(sample);
  }
  template <typename SampleType>
  auto density(SampleType const& sample) -> double {
    return static_cast<DistributionInterface<SampleType>*>(pimpl_.get())->density(sample);
  }
  template <typename SampleType>
  auto update(SampleType const& sample) -> void {
    static_cast<DistributionInterface<SampleType>*>(pimpl_.get())->update(sample);
  }

 private:
  struct DistributionConcept {
    virtual ~DistributionConcept() {}
    virtual auto clone() const -> std::unique_ptr<DistributionConcept> = 0;
  };

  template <typename SampleType>
  struct DistributionInterface : DistributionConcept {
    virtual auto distance(SampleType const& sample) const -> double = 0;
    virtual auto density(SampleType const& sample) const -> double = 0;
    virtual auto update(SampleType const& sample) -> void = 0;
  };

  template <typename DistributionType, typename DistanceStrategy, typename DensityStrategy, typename UpdateStrategy>
  struct DistributionModel : DistributionInterface<typename DistributionType::SampleType> {
    using SampleType = typename DistributionType::SampleType;
    DistributionModel(DistributionType const& distribution, DistanceStrategy distance_strategy,
                      DensityStrategy density_strategy, UpdateStrategy update_strategy)
        : distribution_{distribution},
          distance_strategy_{distance_strategy},
          density_strategy_{density_strategy},
          update_strategy_{update_strategy} {}

    auto clone() const -> std::unique_ptr<DistributionConcept> override {
      return std::make_unique<DistributionModel>(*this);
    }

    auto distance(SampleType const& sample) const -> double override {
      return distance_strategy_(distribution_, sample);
    }

    auto density(SampleType const& sample) const -> double { return density_strategy_(distribution_, sample); }

    auto update(SampleType const& sample) -> void { update_strategy_(distribution_, sample); }

    DistributionType distribution_;
    DistanceStrategy distance_strategy_;
    DensityStrategy density_strategy_;
    UpdateStrategy update_strategy_;
  };

  std::unique_ptr<DistributionConcept> pimpl_;
};

}  // namespace distributions
