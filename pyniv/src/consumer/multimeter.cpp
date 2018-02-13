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
#include <string>    // NOLINT
#include <vector>    // NOLINT

SUPPRESS_WARNINGS_BEGIN
#include "boost/python/numpy.hpp"
SUPPRESS_WARNINGS_END

#include "niv/consumer/device.hpp"
#include "niv/consumer/multimeter.hpp"

namespace pyniv {
namespace consumer {

boost::python::numpy::ndarray GetValues(
    const niv::consumer::Multimeter& multimeter);
boost::python::numpy::ndarray GetValues(
    const niv::consumer::Multimeter& multimeter) {
  const auto& values{multimeter.GetValues()};

  return boost::python::numpy::from_data(
      values.data(), boost::python::numpy::dtype::get_builtin<double>(),
      boost::python::make_tuple(values.size()),
      boost::python::make_tuple(sizeof(double)), boost::python::object());
}

}  // namespace consumer

template <>
void expose<niv::consumer::Multimeter>() {
  class_<niv::consumer::Multimeter, bases<niv::consumer::Device>>(
      "Multimeter", init<std::string>())
      .def("GetValues", &pyniv::consumer::GetValues)
      .def("SetAttribute", &niv::consumer::Multimeter::SetAttribute)
      .def("Update", &niv::consumer::Multimeter::Update);
}

}  // namespace pyniv
