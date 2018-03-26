//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017-2018 RWTH Aachen University, Germany,
// Virtual Reality & Immersive Visualisation Group.
//------------------------------------------------------------------------------
//                                 License
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

#ifndef NIV_INCLUDE_NIV_PRODUCER_SPIKE_DETECTOR_HPP_
#define NIV_INCLUDE_NIV_PRODUCER_SPIKE_DETECTOR_HPP_

#include <memory>
#include <string>
#include <vector>

#include "niv/producer/device.hpp"

namespace niv {
namespace producer {

class SpikeDetector final : public Device {
 public:
  struct Datum : public Device::Datum {
    using Device_t = SpikeDetector;

    Datum(double time, std::size_t neuron_id)
        : Device::Datum{time}, neuron_id{neuron_id} {}

    std::size_t neuron_id;
  };

  SpikeDetector() = delete;
  SpikeDetector(const std::string& name, conduit::Node* node);
  SpikeDetector(const SpikeDetector&) = default;
  SpikeDetector(SpikeDetector&&) = default;
  ~SpikeDetector() override = default;

  SpikeDetector& operator=(const SpikeDetector&) = default;
  SpikeDetector& operator=(SpikeDetector&&) = default;

  void Record(const Datum& datum);

 private:
  std::vector<std::size_t> GetData(const conduit::Node& node);
  std::vector<std::size_t> AsVector(const conduit::uint64_array& array);
};

}  // namespace producer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_PRODUCER_SPIKE_DETECTOR_HPP_
