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

#include "niv/consumer/device.hpp"

#include "multimeter.hpp"

namespace pyniv {
namespace consumer {

Multimeter::Multimeter(const std::string& name)
    : niv::consumer::Multimeter{name} {}

boost::python::numpy::ndarray Multimeter::GetValues() {
  const auto& values{niv::consumer::Multimeter::GetValues()};

  return boost::python::numpy::from_data(
      values.data(), boost::python::numpy::dtype::get_builtin<double>(),
      boost::python::make_tuple(values.size()),
      boost::python::make_tuple(sizeof(double)), boost::python::object());
}

boost::python::numpy::ndarray Multimeter::GetTimesteps() {
  timesteps_ = niv::consumer::Multimeter::GetTimesteps();

  return boost::python::numpy::from_data(
      timesteps_.data(), boost::python::numpy::dtype::get_builtin<double>(),
      boost::python::make_tuple(timesteps_.size()),
      boost::python::make_tuple(sizeof(double)), boost::python::object());
}

}  // namespace consumer

template <>
void expose<pyniv::consumer::Multimeter>() {
  class_<pyniv::consumer::Multimeter, bases<niv::consumer::Device>>(
      "ConsumerMultimeter", init<std::string>())
      .def("GetValues", &pyniv::consumer::Multimeter::GetValues)
      .def("GetTimesteps", &pyniv::consumer::Multimeter::GetTimesteps)
      .def("SetAttribute", &pyniv::consumer::Multimeter::SetAttribute)
      .def("Update", &pyniv::consumer::Multimeter::Update);
}

}  // namespace pyniv
