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

#include "niv/vis_multimeter.hpp"

#include <string>
#include <vector>

namespace niv {

VisMultimeter::VisMultimeter(const std::string& name,
                             const std::vector<std::string>& attribute_names)
    : name_{name}, attribute_names_(attribute_names) {}

void VisMultimeter::SetTime(double time) {
  time_ = time;
  Update();
}

const std::vector<double> VisMultimeter::GetAttributeValues(
    const std::string& attribute_name) const {
  for (auto attribute_index = 0u; attribute_index < attribute_names_.size();
       ++attribute_index) {
    if (attribute_names_[attribute_index] == attribute_name) {
      return values_[attribute_index];
    }
  }

  return std::vector<double>();
}

void VisMultimeter::Update() {
  SetTimestepNode();
  SetValues();
}

void VisMultimeter::SetTimestepNode() {
  std::stringstream time_stream;
  time_stream << time_;
  try {
    timestep_node_ = &node_.fetch_child(name_ + "/" + time_stream.str());
  } catch (...) {
  }
}

void VisMultimeter::SetValues() {
  values_.clear();
  for (auto attribute_index = 0u; attribute_index < attribute_names_.size();
       ++attribute_index) {
    const auto current_values = ExtractValues(attribute_index);
    values_.push_back(current_values);
  }
}

std::vector<double> VisMultimeter::ExtractValues(
    std::size_t attribute_index) const {
  const conduit::Node* attribute_node = GetAttributeNode(attribute_index);
  if (attribute_node == nullptr) {
    return std::vector<double>();
  }

  return GetAttributeNodesValues(attribute_node);
}

const conduit::Node* VisMultimeter::GetAttributeNode(
    std::size_t attribute_index) const {
  const conduit::Node* attribute_node{nullptr};
  const std::string attribute_name{attribute_names_[attribute_index]};
  try {
    attribute_node = &timestep_node_->fetch_child(attribute_name);
  } catch (...) {
  }

  return attribute_node;
}

std::vector<double> VisMultimeter::GetAttributeNodesValues(
    const conduit::Node* attribute_node) const {
  std::vector<double> values;
  for (auto i = 0u; i < attribute_node->number_of_children(); ++i) {
    values.push_back(attribute_node->child(i).as_double());
  }
  return values;
}

}  // namespace niv
