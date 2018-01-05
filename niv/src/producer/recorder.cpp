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

#include <sstream>
#include <string>
#include <vector>

#include "niv/producer/recorder.hpp"

namespace niv {
namespace producer {

Recorder::Recorder(const std::string& name, conduit::Node* node)
    : node_(node), name_(name) {}

void Recorder::SetRecordingTime(double time) {
  std::stringstream time_stream;
  time_stream << time;
  timestep_node_ = &(*node_)[name_][time_stream.str()];
}

void Recorder::Record(std::size_t) {}
void Recorder::Record(std::size_t, const std::vector<double>&) {}

conduit::Node& Recorder::GetTimestepNode() {
  if (timestep_node_ == nullptr) {
    SetRecordingTime(0.0);
  }
  return *timestep_node_;
}

}  // namespace producer
}  // namespace niv
