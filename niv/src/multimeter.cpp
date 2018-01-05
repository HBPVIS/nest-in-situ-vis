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

#include "niv/multimeter.hpp"

namespace niv {

Multimeter::Multimeter(const std::string& name,
                       const std::vector<std::string>& value_names,
                       conduit::Node* node)
    : Recorder{name, node}, value_names_{value_names} {}

void Multimeter::Record(std::size_t id, const std::vector<double>& values) {
  const std::string id_string{IdString(id)};
  for (std::size_t i = 0; i < value_names_.size(); ++i) {
    RecordValue(id_string, values, i);
  }
}

void Multimeter::RecordValue(std::string id_string,
                             const std::vector<double> values,
                             std::size_t value_index) {
  const std::string& value_name = value_names_[value_index];
  const double value = values[value_index];
  GetTimestepNode()[value_name][id_string] = value;
}

std::string Multimeter::IdString(std::size_t id) const {
  std::stringstream id_stream;
  id_stream << id;
  return id_stream.str();
}

std::unique_ptr<Multimeter> Multimeter::New(
    const std::string& name, const std::vector<std::string>& value_names,
    conduit::Node* node) {
  return std::make_unique<Multimeter>(name, value_names, node);
}

}  // namespace niv
