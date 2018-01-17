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

#include "conduit/conduit_node.hpp"

#include "niv/nest_test_data.hpp"

#include "pyniv.hpp"

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

template <>
void expose<niv::Testing>() {
  def("TestingAnyAttribute", &niv::testing::AnyAttribute);
  def("TestingAnotherAttribute", &niv::testing::AnotherAttribute);
  def("TestingThirdAttribute", &niv::testing::ThirdAttribute);
  def("TestingAnyTime", &niv::testing::AnyTime);
  def("TestingAnyAttributesValues", &niv::testing::AnyAttributesValues);
  def("TestingAnotherAttributesValues", &niv::testing::AnotherAttributesValues);
  def("TestingThirdAttributesValues", &niv::testing::ThirdAttributesValues);
  def("TestingAnyValueNames", &niv::testing::AnyValueNames);
  def("TestingAnyMultimeterName", &niv::testing::AnyMultimeterName);
  def("TestingAnyNestData", &niv::testing::AnyNestData);
  def("TestingSend", &niv::testing::Send);
  def("TestingAnyNode", &niv::testing::AnyNode);
  def("TestingAnotherNode", &niv::testing::AnotherNode);
  def("TestingUpdate", &niv::testing::Update);
  def("TestingUpdatedNode", &niv::testing::UpdatedNode);
  def("TestingADifferentNode", &niv::testing::ADifferentNode);
  def("TestingEqual", &pyniv::testing::Equal);
}

}  // namespace pyniv
