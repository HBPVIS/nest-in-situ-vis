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

#include "niv/recorder.hpp"

namespace niv {

class Multimeter final : public Recorder {
 public:
  Multimeter(const std::string& name,
             const std::vector<std::string>& value_names, conduit::Node* node)
      : Recorder{name, node}, value_names_{value_names} {}

  void Record(std::size_t id, const std::vector<double> values) override {
    const std::string id_string{IdString(id)};
    for (std::size_t i = 0; i < value_names_.size(); ++i) {
      Record(id_string, values, i);
    }
  }

 private:
  void Record(std::string id_string, const std::vector<double> values,
              std::size_t value_index) {
    const std::string& value_name = value_names_[value_index];
    const double value = values[value_index];
    (*timestep_node_)[value_name][id_string] = value;
  }

  std::string IdString(std::size_t id) const {
    std::stringstream id_stream;
    id_stream << id;
    return id_stream.str();
  }

  std::vector<std::string> value_names_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_MULTIMETER_HPP_
