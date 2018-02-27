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

std::vector<std::string> ArborMultimeter::GetNodeIds(
    double time, const std::string& attribute) {
  const conduit::Node* node{GetNode()};

  const conduit::Node* device_node{nullptr};
  try {
    device_node = &node->fetch_child(GetName());
  } catch (...) {
    return std::vector<std::string>();
  }

  std::stringstream time_stream;
  time_stream << time;
  const conduit::Node* timestep_node{nullptr};
  try {
    timestep_node = &(device_node->fetch_child(time_stream.str()));
  } catch (...) {
    return std::vector<std::string>();
  }

  const conduit::Node* attribute_node{nullptr};
  try {
    attribute_node = &(timestep_node->fetch_child(attribute));
  } catch (...) {
    return std::vector<std::string>();
  }

  return attribute_node->child_names();
}

}  // namespace consumer
}  // namespace niv
