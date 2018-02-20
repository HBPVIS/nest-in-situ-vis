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

#include <cmath>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/producer/arbor_multimeter.hpp"

namespace niv {
namespace producer {

ArborMultimeter::ArborMultimeter(const std::string& name,
                                 const std::vector<std::string>& value_names,
                                 conduit::Node* node)
    : Device{name, node}, value_names_{value_names} {}

std::unique_ptr<ArborMultimeter> ArborMultimeter::New(
    const std::string& name, const std::vector<std::string>& value_names,
    conduit::Node* node) {
  return std::make_unique<ArborMultimeter>(name, value_names, node);
}

void ArborMultimeter::Record(const ArborMultimeter::Datum& datum) {
  const std::string path{CreatePath(datum)};
  GetNode(path) = datum.value;
}

std::string ArborMultimeter::CreatePath(const ArborMultimeter::Datum& datum) {
  std::stringstream path;
  path << GetName() << '/';
  path << std::round(10.0 * datum.time) / 10.0 << '/';
  path << datum.attribute << '/';
  path << datum.id;
  return path.str();
}

}  // namespace producer
}  // namespace niv
