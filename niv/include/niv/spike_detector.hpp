//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017 RWTH Aachen University, Germany,
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

#ifndef NIV_INCLUDE_NIV_SPIKE_DETECTOR_HPP_
#define NIV_INCLUDE_NIV_SPIKE_DETECTOR_HPP_

#include <sstream>
#include <string>

#include "niv/recorder.hpp"

namespace niv {

class SpikeDetector final : public Recorder {
 public:
  SpikeDetector(const std::string& name, conduit::Node* node)
      : Recorder{name, node} {}

  void Record(std::size_t id) override {
    conduit::Node& leaf_node = (*node_)[name_][recording_time_];
    std::vector<std::size_t> data(GetDataFromLeaf(leaf_node));
    data.push_back(id);
    leaf_node.set_uint64_vector(data);
  }

 private:
  std::vector<std::size_t> GetDataFromLeaf(const conduit::Node& node) {
    if (node.total_bytes_allocated() != 0) {
      const auto& node_data(node.as_uint64_array());
      return AsVector(node_data);
    }
    return std::vector<std::size_t>();
  }

  std::vector<std::size_t> AsVector(const conduit::uint64_array& array) {
    const std::size_t num_elements = array.number_of_elements();
    const auto* begin = reinterpret_cast<std::size_t*>(array.data_ptr());
    const auto* end = begin + num_elements;
    return std::vector<std::size_t>(begin, end);
  }
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_SPIKE_DETECTOR_HPP_
