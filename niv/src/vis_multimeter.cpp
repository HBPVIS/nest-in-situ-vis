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

VisMultimeter::VisMultimeter(const std::string& name) : AnalysisDevice{name} {}

void VisMultimeter::SetAttribute(const std::string& attribute) {
  attribute_ = attribute;
}

void VisMultimeter::Update() {
  SetTimestepNode();
  SetValues();
}

void VisMultimeter::SetValues() {
  values_.clear();
  try {
    const conduit::Node* attribute_node =
        &GetTimestepNode()->fetch_child(attribute_);
    for (auto i = 0u; i < attribute_node->number_of_children(); ++i) {
      values_.push_back(attribute_node->child(i).as_double());
    }
  } catch (...) {
  }
}

const std::vector<double>& VisMultimeter::GetValues() const { return values_; }

}  // namespace niv
