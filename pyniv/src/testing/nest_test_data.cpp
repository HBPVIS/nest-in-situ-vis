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

SUPPRESS_WARNINGS_BEGIN
#include "boost/python/numpy.hpp"
SUPPRESS_WARNINGS_END

#include "conduit/conduit_node.hpp"

#include "niv/nest_test_data.hpp"

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

std::string AnyValueNames(std::size_t index) {
  return niv::testing::AnyValueNames()[index];
}

boost::python::numpy::ndarray AnyAttributesValues(double time = 0) {
  static std::vector<double> values;
  values = std::vector<double>{niv::testing::AnyAttributesValues(time)};

  return boost::python::numpy::from_data(
      values.data(), boost::python::numpy::dtype::get_builtin<double>(),
      boost::python::make_tuple(values.size()),
      boost::python::make_tuple(sizeof(double)), boost::python::object());
}

boost::python::numpy::ndarray AnotherAttributesValues() {
  static std::vector<double> values{niv::testing::AnotherAttributesValues()};

  return boost::python::numpy::from_data(
      values.data(), boost::python::numpy::dtype::get_builtin<double>(),
      boost::python::make_tuple(values.size()),
      boost::python::make_tuple(sizeof(double)), boost::python::object());
}

BOOST_PYTHON_FUNCTION_OVERLOADS(AnyAttributesValuesOverloads,
                                AnyAttributesValues, 0, 1)

boost::python::list TimeOffsets() {
  boost::python::list ret_val;
  for (auto t : niv::testing::TIME_OFFSETS) {
    ret_val.append(t);
  }
  return ret_val;
}

}  // namespace testing

#ifndef EXPOSE_CONSTANT
#define EXPOSE_CONSTANT(a) scope().attr(#a) = niv::testing::a
#endif

template <>
void expose<niv::Testing>() {
  EXPOSE_CONSTANT(ANY_MULTIMETER_NAME);
  EXPOSE_CONSTANT(NOT_A_MULTIMETER_NAME);

  EXPOSE_CONSTANT(ANY_TIME);
  EXPOSE_CONSTANT(ANOTHER_TIME);
  EXPOSE_CONSTANT(THIRD_TIME);
  EXPOSE_CONSTANT(NOT_A_TIME);

  EXPOSE_CONSTANT(ANY_TIME_STRING);
  EXPOSE_CONSTANT(ANOTHER_TIME_STRING);
  EXPOSE_CONSTANT(THIRD_TIME_STRING);
  EXPOSE_CONSTANT(NOT_A_TIME_STRING);

  EXPOSE_CONSTANT(ANY_ATTRIBUTE);
  EXPOSE_CONSTANT(ANOTHER_ATTRIBUTE);
  EXPOSE_CONSTANT(THIRD_ATTRIBUTE);
  EXPOSE_CONSTANT(NOT_AN_ATTRIBUTE);

  EXPOSE_CONSTANT(ANY_ID);
  EXPOSE_CONSTANT(ANOTHER_ID);
  EXPOSE_CONSTANT(THIRD_ID);
  EXPOSE_CONSTANT(NOT_AN_ID);

  EXPOSE_CONSTANT(ANY_NEST_DATA);

  EXPOSE_CONSTANT(ANY_VALUE);
  EXPOSE_CONSTANT(TIME_STRIDE);
  EXPOSE_CONSTANT(ATTRIBUTE_STRIDE);
  EXPOSE_CONSTANT(ID_STRIDE);

  EXPOSE_CONSTANT(ANY_TIME_OFFSET);
  EXPOSE_CONSTANT(ANOTHER_ATTRIBUTE_OFFSET);
  EXPOSE_CONSTANT(THIRD_ID_OFFSET);

  def("TIME_OFFSETS", &pyniv::testing::TimeOffsets);
  def("AnyAttributesValues", &pyniv::testing::AnyAttributesValues,
      pyniv::testing::AnyAttributesValuesOverloads());
  def("AnotherAttributesValues", &pyniv::testing::AnotherAttributesValues);
  def("ThirdAttributesValues", &niv::testing::ThirdAttributesValues);
  def("AnyValueNames", &pyniv::testing::AnyValueNames);
  def("AnyMultimeterName", &niv::testing::AnyMultimeterName);
  def("AnyNestData", &niv::testing::AnyNestData);
  def("Send", &niv::testing::Send);
  def("AnyNode", &niv::testing::AnyNode);
  def("AnotherNode", &niv::testing::AnotherNode);
  def("Update", &niv::testing::Update);
  def("UpdatedNode", &niv::testing::UpdatedNode);
  def("ADifferentNode", &niv::testing::ADifferentNode);
  def("Equal", &pyniv::testing::Equal);
}

}  // namespace pyniv
