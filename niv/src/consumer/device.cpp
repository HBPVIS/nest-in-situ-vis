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

#include <cstdlib>

#include <iostream>

#include <algorithm>
#include <string>
#include <vector>

namespace niv {
namespace consumer {

Device::Device(const std::string& name) : name_{name} {}

const std::vector<double>& Device::GetTimesteps() {
  timesteps_.clear();

  const conduit::Node* device_node{nullptr};
  try {
    device_node = &node_->fetch_child(name_);
  } catch (...) {
    return timesteps_;
  }

  const std::string device_node_path{device_node->path()};
  for (auto i = 0u; i < device_node->number_of_children(); ++i) {
    const conduit::Node& curr_child{device_node->child(i)};
    const std::string child_path{curr_child.path()};
    const std::string child_local_path{
        child_path.substr(device_node_path.size() + 1,
                          child_path.size() - device_node_path.size() - 1)};
    timesteps_.push_back(std::strtof(child_local_path.c_str(), nullptr));
  }

  std::sort(timesteps_.begin(), timesteps_.end());
  return timesteps_;
}

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

const conduit::Node* Device::GetNode() const { return node_; }

const std::string Device::GetName() const { return name_; }

}  // namespace consumer
}  // namespace niv
