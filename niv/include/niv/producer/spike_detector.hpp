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

#include "niv/producer/recorder.hpp"

namespace niv {

class SpikeDetector final : public Recorder {
 public:
  SpikeDetector(const std::string& name, conduit::Node* node);
  SpikeDetector(const SpikeDetector&) = default;
  SpikeDetector(SpikeDetector&&) = default;
  virtual ~SpikeDetector() = default;

  void Record(std::size_t id) override;

  SpikeDetector& operator=(const SpikeDetector&) = default;
  SpikeDetector& operator=(SpikeDetector&&) = default;

  static std::unique_ptr<SpikeDetector> New(const std::string& name,
                                            conduit::Node* node);

 private:
  std::vector<std::size_t> GetData(const conduit::Node& node);
  std::vector<std::size_t> AsVector(const conduit::uint64_array& array);
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_PRODUCER_SPIKE_DETECTOR_HPP_
