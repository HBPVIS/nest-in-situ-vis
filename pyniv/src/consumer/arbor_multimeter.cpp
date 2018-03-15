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

#include "niv/consumer/arbor_multimeter.hpp"

namespace pyniv {

namespace consumer {
namespace arbor_multimeter {

boost::python::list GetTimestepsString(
    const niv::consumer::ArborMultimeter& multimeter) {
  boost::python::list retval;
  const auto timesteps = multimeter.GetTimestepsString();
  for (auto t : timesteps) {
    retval.append(t);
  }
  return retval;
}

boost::python::list GetAttributes(
    const niv::consumer::ArborMultimeter& multimeter, double time) {
  boost::python::list retval;
  const auto attributes = multimeter.GetAttributes(time);
  for (auto a : attributes) {
    retval.append(a);
  }
  return retval;
}

boost::python::list GetNeuronIds(
    const niv::consumer::ArborMultimeter& multimeter, double time,
    const std::string& attribute) {
  boost::python::list retval;
  const auto ids = multimeter.GetNeuronIds(time, attribute);
  for (auto i : ids) {
    retval.append(i);
  }
  return retval;
}

}  // namespace arbor_multimeter
}  // namespace consumer

template <>
void expose<niv::consumer::ArborMultimeter>() {
  class_<niv::consumer::ArborMultimeter, bases<niv::consumer::Device>>(
      "ArborMultimeter", init<std::string>())
      .def("GetTimestepsString",
           &pyniv::consumer::arbor_multimeter::GetTimestepsString)
      .def("GetAttributes", &pyniv::consumer::arbor_multimeter::GetAttributes)
      .def("GetNeuronIds", &pyniv::consumer::arbor_multimeter::GetNeuronIds);
}

}  // namespace pyniv
