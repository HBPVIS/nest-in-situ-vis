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

#include <memory>
#include <string>
#include <vector>

#include "niv/spike_detector.hpp"

namespace niv {

SpikeDetector::SpikeDetector(const std::string& name, conduit::Node* node)
    : Recorder{name, node} {}

void SpikeDetector::Record(std::size_t id) {
  std::vector<std::size_t> data(GetData(GetTimestepNode()));
  data.push_back(id);
  GetTimestepNode().set_uint64_vector(data);
}

std::vector<std::size_t> SpikeDetector::GetData(const conduit::Node& node) {
  if (node.total_bytes_allocated() != 0) {
    return AsVector(node.as_uint64_array());
  }
  return std::vector<std::size_t>();
}

std::vector<std::size_t> SpikeDetector::AsVector(
    const conduit::uint64_array& array) {
  const std::size_t num_elements =
      static_cast<std::size_t>(array.number_of_elements());
  const auto* begin = reinterpret_cast<std::size_t*>(array.data_ptr());
  const auto* end = begin + num_elements;
  return std::vector<std::size_t>(begin, end);
}

std::unique_ptr<SpikeDetector> SpikeDetector::New(const std::string& name,
                                                  conduit::Node* node) {
  return std::make_unique<SpikeDetector>(name, node);
}

}  // namespace niv
