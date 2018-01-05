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

#include "pyniv.hpp"

#include <iostream>  // NOLINT

#include "conduit_data.hpp"

namespace pyniv {

ConduitData::ConduitData() { node_["V_m"] = 1.2; }

ConduitData::ConduitData(const conduit::Node& node) { node_ = node; }

void ConduitData::Set(const char* path, double value) { node_[path] = value; }

double ConduitData::Get(const char* path) { return node_[path].as_double(); }

void ConduitData::Print() const { std::cout << node_.to_json() << std::endl; }

template <>
void expose<ConduitData>() {
  class_<ConduitData>("ConduitData")
      .def("Set", &ConduitData::Set)
      .def("Get", &ConduitData::Get)
      .def("Print", &ConduitData::Print);
}

}  // namespace pyniv
