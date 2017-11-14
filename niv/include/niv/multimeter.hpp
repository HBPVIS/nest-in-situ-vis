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

#ifndef NIV_INCLUDE_NIV_MULTIMETER_HPP_
#define NIV_INCLUDE_NIV_MULTIMETER_HPP_

#include <sstream>
#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

namespace niv {

class Multimeter {
 public:
  Multimeter(const std::string& name,
             const std::vector<std::string>& value_names, conduit::Node* node)
      : node_{node}, name_{name}, value_names_{value_names} {}

  void SetRecordingTime(double time) {
    std::stringstream time_stream;
    time_stream << time;
    recording_time_ = time_stream.str();
  }

  void Record(std::size_t id, const std::vector<double> values) {
    const std::string id_string{IdString(id)};
    for (std::size_t i = 0; i < value_names_.size(); ++i) {
      const std::string& value_name = value_names_[i];
      const double value = values[i];
      (*node_)[name_][recording_time_][value_name][id_string] = value;
    }
  }

 private:
  std::string IdString(std::size_t id) const {
    std::stringstream id_stream;
    id_stream << id;
    return id_stream.str();
  }
  conduit::Node* node_{nullptr};
  std::string name_{"multimeter"};
  std::vector<std::string> value_names_;
  std::string recording_time_{"0"};
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_MULTIMETER_HPP_
