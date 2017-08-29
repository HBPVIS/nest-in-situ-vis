//------------------------------------------------------------------------------
// nest python vis
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

#include "npv/nest_python_vis.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace npv {

constexpr std::chrono::duration<int, std::milli> NestPythonVis::disabled_sleep_;

NestPythonVis::NestPythonVis(conduit::Node* node) : node_(node) {}

NestPythonVis::NestPythonVis(std::size_t ptr_to_node)
    : NestPythonVis(reinterpret_cast<conduit::Node*>(ptr_to_node)) {}

NestPythonVis::~NestPythonVis() { JoinAndDeleteThread(); }

void NestPythonVis::Start() {
  EnableIsRunning();
  SpawnThread();
}

void NestPythonVis::EnableIsRunning() { sleep_in_use_ = configured_sleep_; }

void NestPythonVis::DisableIsRunning() { sleep_in_use_ = disabled_sleep_; }

bool NestPythonVis::IsRunning() const {
  return sleep_in_use_ != disabled_sleep_;
}

void NestPythonVis::Stop() {
  DisableIsRunning();
  JoinAndDeleteThread();
}

void NestPythonVis::Run() {
  while (IsRunning()) {
    Step();
  }
}

void NestPythonVis::Step() {
  PrintNode();
  Sleep();
}

void NestPythonVis::PrintNode() const {
  std::cout << NodeString() << std::endl;
}

std::string NestPythonVis::NodeString() const {
  return node_ == nullptr ? "nullptr" : FormatNode();
}

std::string NestPythonVis::FormatNode() const {
  std::ostringstream sstr;
  sstr << (*node_)["V_m"].as_double();
  return sstr.str();
}

}  // namespace npv
