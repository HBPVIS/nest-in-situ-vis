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

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/consumer/arbor_multimeter.hpp"
#include "niv/nest_test_data.hpp"

namespace niv {
namespace consumer {

ArborMultimeter::ArborMultimeter(const std::string& name) : Device(name) {}

void ArborMultimeter::Update() { SetTimestepNode(); }

std::vector<std::string> ArborMultimeter::GetNeuronIds(
    double time, const std::string& attribute) {
  const conduit::Node* const root_node{GetNode()};
  const conduit::Node* const device_node{GetChildNode(root_node, GetName())};
  const conduit::Node* const timestep_node{
      GetChildNode(device_node, TimeToString(time))};
  const conduit::Node* const attribute_node{
      GetChildNode(timestep_node, attribute)};

  return GetChildNames(attribute_node);
}

std::string ArborMultimeter::TimeToString(double time) {
  std::stringstream s;
  s << time;
  return s.str();
}

const conduit::Node* ArborMultimeter::GetChildNode(
    const conduit::Node* parent, const std::string& child_name) {
  if (parent == nullptr) {
    return nullptr;
  }

  const conduit::Node* child{nullptr};
  try {
    child = &parent->fetch_child(child_name);
  } catch (...) {
  }
  return child;
}

std::vector<std::string> ArborMultimeter::GetChildNames(
    const conduit::Node* node) {
  if (node == nullptr) {
    return std::vector<std::string>();
  }
  return node->child_names();
}

}  // namespace consumer
}  // namespace niv
