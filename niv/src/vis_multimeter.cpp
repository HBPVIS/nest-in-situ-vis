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
                             const std::vector<std::string>& value_names,
                             const conduit::Node& node)
    : name_{name}, value_names_(value_names) {
  node_.set_external(node);
}

void VisMultimeter::SetTime(double time) {
  std::stringstream time_stream;
  time_stream << time;
  try {
    timestep_node_ = &node_.fetch_child(name_ + "/" + time_stream.str());
  } catch (...) {
  }
}

std::vector<double> VisMultimeter::GetAttribute(const std::string& value_name) {
  std::vector<double> result;

  conduit::Node* attribute_node{nullptr};
  try {
    attribute_node = &timestep_node_->fetch_child(value_name);
  } catch (...) {
    return result;
  }

  for (auto i = 0u; i < attribute_node->number_of_children(); ++i) {
    result.push_back(attribute_node->child(i).as_double());
  }

  return result;
}

}  // namespace niv
