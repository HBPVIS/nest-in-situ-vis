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

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/consumer/arbor_multimeter.hpp"
#include "niv/nest_test_data.hpp"

namespace niv {
namespace consumer {

ArborMultimeter::ArborMultimeter(const std::string& name) : Device(name) {}

void ArborMultimeter::Update() {}

std::vector<std::string> ArborMultimeter::GetNeuronIds(
    double time, const std::string& attribute) const {
  const std::string path{ConstructPath(time, attribute)};
  const conduit::Node* node{GetNode(path)};
  return GetChildNames(node);
}

double ArborMultimeter::GetDatum(double time, const std::string& attribute,
                                 const std::string& neuron_id) const {
  const std::string path{ConstructPath(time, attribute, neuron_id)};
  const conduit::Node* node{GetNode(path)};
  return GetValue(node);
}

std::string ArborMultimeter::ConstructPath(double time,
                                           const std::string& attribute,
                                           const std::string& neuron_id) const {
  std::stringstream path;
  path << ConstructPath(time, attribute) << "/";
  path << neuron_id;
  return path.str();
}

std::string ArborMultimeter::ConstructPath(double time,
                                           const std::string& attribute) const {
  std::stringstream path;
  path << GetName() << "/";
  path << time << "/";
  path << attribute;
  return path.str();
}

const conduit::Node* ArborMultimeter::GetNode(const std::string& path) const {
  const conduit::Node* node{nullptr};
  try {
    node = &GetRootNode()->fetch_child(path);
  } catch (...) {
  }
  return node;
}

std::vector<std::string> ArborMultimeter::GetChildNames(
    const conduit::Node* node) {
  if (node == nullptr) {
    return std::vector<std::string>();
  }
  return node->child_names();
}

double ArborMultimeter::GetValue(const conduit::Node* node) {
  if (node == nullptr) {
    return std::nan("");
  }
  return node->as_double();
}

}  // namespace consumer
}  // namespace niv
