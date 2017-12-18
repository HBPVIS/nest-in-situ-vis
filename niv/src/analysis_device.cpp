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

#include "niv/analysis_device.hpp"

#include <string>

namespace niv {

AnalysisDevice::AnalysisDevice(const std::string& name) : name_{name} {}

void AnalysisDevice::SetTime(double time) {
  std::cout << "AnalysisDevice::SetTime(" << time << ")" << std::endl;
  time_ = time;
}

void AnalysisDevice::SetTimestepNode() {
  std::cout << "Enter SetTimestepNode" << std::endl;
  std::stringstream time_stream;
  time_stream << time_;
  try {
    timestep_node_ = &node_->fetch_child(name_ + "/" + time_stream.str());
  } catch (...) {
  }
  std::cout << "AnalysisDevice::SetTimestepNode" << std::endl;
  std::cout << "time_ " << time_ << std::endl;
  std::cout << node_ << std::endl;
  node_->print();
}

const conduit::Node* AnalysisDevice::GetTimestepNode() const {
  return timestep_node_;
}

}  // namespace niv
