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

#include <string>  // NOLINT
#include <vector>  // NOLINT

#include "conduit/conduit_node.hpp"

#include "niv/testing/helpers.hpp"

namespace pyniv {
namespace testing {

bool Equal(const conduit::Node& node1, const conduit::Node& node2) {
  bool is_equal = (node1.to_json() == node2.to_json());
  if (!is_equal) {
    std::cout << "Nodes are not equal:" << std::endl;
    std::cout << "Node 1:" << std::endl;
    std::cout << node1.to_json() << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "Node 2:" << std::endl;
    std::cout << node2.to_json() << std::endl;
  }
  return is_equal;
}

}  // namespace testing

#ifndef EXPOSE_CONSTANT
#define EXPOSE_CONSTANT(a) scope().attr(#a) = niv::testing::a
#endif

template <>
void expose<niv::testing::Helpers>() {
  EXPOSE_CONSTANT(ANY_NODE);
  EXPOSE_CONSTANT(ANOTHER_NODE);
  EXPOSE_CONSTANT(ANY_UPDATE);
  EXPOSE_CONSTANT(UPDATED_NODE);
  EXPOSE_CONSTANT(A_DIFFERENT_NODE);

  def("Send", &niv::testing::Send);
  def("Equal", &pyniv::testing::Equal);
}

}  // namespace pyniv
