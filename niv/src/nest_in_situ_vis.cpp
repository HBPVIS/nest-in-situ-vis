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

#include "niv/nest_in_situ_vis.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace niv {

constexpr std::chrono::duration<int, std::milli> NestInSituVis::disabled_sleep_;

NestInSituVis::NestInSituVis(conduit::Node* node) : node_(node) {}

NestInSituVis::NestInSituVis(std::size_t ptr_to_node)
    : NestInSituVis(reinterpret_cast<conduit::Node*>(ptr_to_node)) {}

NestInSituVis::~NestInSituVis() { JoinAndDeleteThread(); }

void NestInSituVis::Start() {
  EnableIsRunning();
  SpawnThread();
}

void NestInSituVis::EnableIsRunning() { sleep_in_use_ = configured_sleep_; }

void NestInSituVis::DisableIsRunning() { sleep_in_use_ = disabled_sleep_; }

bool NestInSituVis::IsRunning() const {
  return sleep_in_use_ != disabled_sleep_;
}

void NestInSituVis::Stop() {
  DisableIsRunning();
  JoinAndDeleteThread();
}

void NestInSituVis::Run() {
  while (IsRunning()) {
    Step();
  }
}

void NestInSituVis::Step() {
  PrintNode();
  Sleep();
}

void NestInSituVis::PrintNode() const {
  std::cout << NodeString() << std::endl;
}

std::string NestInSituVis::NodeString() const {
  return node_ == nullptr ? "nullptr" : FormatNode();
}

std::string NestInSituVis::FormatNode() const {
  std::ostringstream sstr;
  sstr << (*node_)["V_m"].as_double();
  return sstr.str();
}

void NestInSituVis::Read(const conduit::Schema& schema,
                         std::vector<conduit::uint8>* data) {
  node_->set_external(schema, data->data());
}

}  // namespace niv
