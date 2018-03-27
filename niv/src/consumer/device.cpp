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

#include "niv/consumer/device.hpp"

#include <cmath>
#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace niv {
namespace consumer {

Device::Device(const std::string& name) : name_{name} {}

std::vector<std::string> Device::GetTimestepsString() const {
  return GetChildNames(ConstructPath());
}

const std::vector<double> Device::GetTimesteps() const {
  const auto timestep_strings{GetTimestepsString()};
  std::vector<double> timesteps_double(timestep_strings.size(), std::nan(""));
  std::transform(timestep_strings.begin(), timestep_strings.end(),
                 timesteps_double.begin(), [](const std::string& t) {
                   return std::strtof(t.c_str(), nullptr);
                 });
  return timesteps_double;
}

std::vector<std::string> Device::GetChildNames(const std::string& path) const {
  const conduit::Node* node{GetNode(path)};
  return (node != nullptr) ? node->child_names() : std::vector<std::string>();
}

const conduit::Node* Device::GetNode(const std::string& path) const {
  const conduit::Node* node{nullptr};
  try {
    node = &GetRootNode()->fetch_child(path);
  } catch (...) {
  }
  return node;
}

std::string Device::ConstructPath() const { return name_; }

void Device::SetTime(double time) { time_ = time; }

void Device::SetTimestepNode() {
  std::stringstream time_stream;
  time_stream << time_;
  try {
    timestep_node_ = &node_->fetch_child(name_ + "/" + time_stream.str());
  } catch (...) {
  }
}

void Device::Print() const {
  if (node_ != nullptr) {
    std::cout << "Schema" << std::endl;
    std::cout << node_->schema().to_json() << std::endl;
    std::cout << "Data" << std::endl;
    node_->print();
  }
}

const conduit::Node* Device::GetTimestepNode() const { return timestep_node_; }

const conduit::Node* Device::GetRootNode() const { return node_; }

const std::string Device::GetName() const { return name_; }

}  // namespace consumer
}  // namespace niv
