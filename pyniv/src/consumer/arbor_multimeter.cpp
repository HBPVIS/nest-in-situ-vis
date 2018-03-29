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

boost::python::list GetTimeSeriesData(
    const niv::consumer::ArborMultimeter& multimeter,
    const std::string& attribute, const std::string& neuron_id) {
  boost::python::list ret_val;
  for (auto v : multimeter.GetTimeSeriesData(attribute, neuron_id)) {
    ret_val.append(v);
  }
  return ret_val;
}

boost::python::list GetTimestepData(
    const niv::consumer::ArborMultimeter& multimeter, const std::string& time,
    const std::string& attribute) {
  boost::python::list ret_val;
  for (auto v : multimeter.GetTimestepData(time, attribute)) {
    ret_val.append(v);
  }
  return ret_val;
}

}  // namespace arbor_multimeter
}  // namespace consumer

template <>
void expose<niv::consumer::ArborMultimeter>() {
  class_<niv::consumer::ArborMultimeter, bases<niv::consumer::Multimeter>>(
      "ArborMultimeter", init<std::string>())
      .def("GetTimestepData",
           &pyniv::consumer::arbor_multimeter::GetTimestepData)
      .def("GetTimeSeriesData",
           &pyniv::consumer::arbor_multimeter::GetTimeSeriesData)
      .def("GetDatum", &niv::consumer::ArborMultimeter::GetDatum);
}

}  // namespace pyniv
