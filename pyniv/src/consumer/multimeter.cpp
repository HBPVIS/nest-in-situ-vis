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
#include "niv/consumer/multimeter.hpp"

namespace pyniv {
namespace consumer {
namespace multimeter {

boost::python::list GetAttributes(const niv::consumer::Multimeter& multimeter,
                                  const std::string& time) {
  boost::python::list ret_val;
  for (auto v : multimeter.GetAttributes(time)) {
    ret_val.append(v);
  }
  return ret_val;
}

boost::python::list GetNeuronIds(const niv::consumer::Multimeter& multimeter,
                                 const std::string& time,
                                 const std::string& attribute) {
  boost::python::list ret_val;
  for (auto v : multimeter.GetNeuronIds(time, attribute)) {
    ret_val.append(v);
  }
  return ret_val;
}

}  // namespace multimeter
}  // namespace consumer

template <>
void expose<niv::consumer::Multimeter>() {
  class_<niv::consumer::Multimeter, bases<niv::consumer::Device>>(
      "Multimeter", init<std::string>())
      .def("GetAttributes", &pyniv::consumer::multimeter::GetAttributes)
      .def("GetNeuronIds", &pyniv::consumer::multimeter::GetNeuronIds);
}

}  // namespace pyniv
