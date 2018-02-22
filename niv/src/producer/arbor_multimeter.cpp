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

ArborMultimeter::ArborMultimeter(const std::string& name) : name_{name} {}

void ArborMultimeter::Record(const ArborMultimeter::Datum& datum,
                             conduit::Node* node) {
  const std::string path{ConstructPath(datum)};
  (*node)[path] = datum.value;
}

std::string ArborMultimeter::ConstructPath(
    const ArborMultimeter::Datum& datum) {
  std::stringstream path;
  path << name_ << '/';
  path << ConstructTimestep(datum) << '/';
  path << datum.attribute << '/';
  path << datum.id;
  return path.str();
}

double ArborMultimeter::ConstructTimestep(const ArborMultimeter::Datum& datum) {
  return std::round(10.0 * datum.time) / 10.0;
}

}  // namespace producer
}  // namespace niv
