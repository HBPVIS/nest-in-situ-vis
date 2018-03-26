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

#include <cassert>

#include <memory>
#include <string>
#include <vector>

#include "niv/producer/nest_multimeter.hpp"

namespace niv {
namespace producer {

NestMultimeter::NestMultimeter(const std::string& name,
                               const std::vector<std::string>& value_names,
                               conduit::Node* node)
    : Device{name, node}, value_names_{value_names} {}

void NestMultimeter::Record(const Datum& datum) {
  assert(datum.values.size() == value_names_.size());

  for (std::size_t i = 0u; i < datum.values.size(); ++i) {
    const std::string path{ConstructPath(datum, i)};
    GetNode(path) = datum.values[i];
  }
}

std::string NestMultimeter::IdString(std::size_t id) {
  std::stringstream id_stream;
  id_stream << id;
  return id_stream.str();
}

std::string NestMultimeter::ConstructPath(const NestMultimeter::Datum& datum,
                                          std::size_t attribute_index) {
  std::stringstream path;
  path << GetName() << '/';
  path << datum.time << '/';
  path << value_names_[attribute_index] << '/';
  path << datum.neuron_id;
  return path.str();
}

}  // namespace producer
}  // namespace niv
