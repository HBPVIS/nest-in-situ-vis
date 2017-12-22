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

#include <string>
#include <vector>

SUPPRESS_WARNINGS_BEGIN
#include "boost/python/numpy.hpp"
SUPPRESS_WARNINGS_END

#include "niv/consumer/device.hpp"

#include "pyniv.hpp"
#include "vis_multimeter.hpp"

namespace pyniv {

VisMultimeter::VisMultimeter(const std::string& name)
    : niv::VisMultimeter{name} {}

boost::python::numpy::ndarray VisMultimeter::GetValues() {
  const auto& values{niv::VisMultimeter::GetValues()};

  return boost::python::numpy::from_data(
      values.data(), boost::python::numpy::dtype::get_builtin<double>(),
      boost::python::make_tuple(values.size()),
      boost::python::make_tuple(sizeof(double)), boost::python::object());
}

boost::python::numpy::ndarray VisMultimeter::GetTimesteps() {
  timesteps_ = niv::VisMultimeter::GetTimesteps();

  return boost::python::numpy::from_data(
      timesteps_.data(), boost::python::numpy::dtype::get_builtin<double>(),
      boost::python::make_tuple(timesteps_.size()),
      boost::python::make_tuple(sizeof(double)), boost::python::object());
}

template <>
void expose<pyniv::VisMultimeter>() {
  class_<pyniv::VisMultimeter, bases<niv::consumer::Device>>(
      "VisMultimeter", init<std::string>())
      .def("GetValues", &pyniv::VisMultimeter::GetValues)
      .def("GetTimesteps", &pyniv::VisMultimeter::GetTimesteps)
      .def("SetAttribute", &pyniv::VisMultimeter::SetAttribute)
      .def("Update", &pyniv::VisMultimeter::Update);
}

}  // namespace pyniv
