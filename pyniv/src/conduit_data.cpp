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

#include "pyniv.hpp"

#include "conduit_data.hpp"

#include <iostream>

namespace pyniv {

ConduitData::ConduitData() {
  node_["V_m"] = 1.2;
  std::cout << "Ptr. to conduit node: " << Pointer() << std::endl;
}

void ConduitData::Set(const char* attribute, double value) {
  node_[attribute] = value;
}

std::size_t ConduitData::Pointer() const {
  return reinterpret_cast<std::size_t>(&node_);
}

template <>
void expose<ConduitData>() {
  class_<ConduitData>("ConduitData")
      .def("Set", &ConduitData::Set)
      .def("Pointer", &ConduitData::Pointer);
}

}  // namespace pyniv
