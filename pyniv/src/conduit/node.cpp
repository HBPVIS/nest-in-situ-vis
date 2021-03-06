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

#include <string>

#include "pyniv.hpp"

#include "conduit/conduit_node.hpp"

namespace pyniv {

double GetDoubleAtPath(const conduit::Node& node, const std::string& path) {
  return node[path].as_double();
}

void SetDoubleAtPath(const conduit::Node& node, const std::string& path,
                     double value) {
  const_cast<conduit::Node&>(node)[path] = value;
}

template <>
void expose<conduit::Node>() {
  class_<conduit::Node>("Node")
      .def("GetDoubleAtPath", &pyniv::GetDoubleAtPath)
      .def("SetDoubleAtPath", &pyniv::SetDoubleAtPath);
}

}  // namespace pyniv
