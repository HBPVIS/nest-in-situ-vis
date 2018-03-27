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
#include "niv/consumer/nest_multimeter.hpp"

namespace pyniv {
namespace consumer {
namespace nest_multimeter {

boost::python::list GetTimeSeriesData(
    const niv::consumer::NestMultimeter& multimeter,
    const std::string& attribute, const std::string& neuron_id) {
  boost::python::list ret_val;
  for (auto v : multimeter.GetTimeSeriesData(attribute, neuron_id)) {
    ret_val.append(v);
  }
  return ret_val;
}

boost::python::list GetTimestepData(
    const niv::consumer::NestMultimeter& multimeter, const std::string& time,
    const std::string& attribute) {
  boost::python::list ret_val;
  for (auto v : multimeter.GetTimestepData(time, attribute)) {
    ret_val.append(v);
  }
  return ret_val;
}

}  // namespace nest_multimeter
}  // namespace consumer

template <>
void expose<niv::consumer::NestMultimeter>() {
  class_<niv::consumer::NestMultimeter, bases<niv::consumer::Multimeter>>(
      "NestMultimeter", init<std::string>())
      .def("GetTimestepData",
           &pyniv::consumer::nest_multimeter::GetTimestepData)
      .def("GetTimeSeriesData",
           &pyniv::consumer::nest_multimeter::GetTimeSeriesData)
      .def("GetDatum", &niv::consumer::NestMultimeter::GetDatum);
}

}  // namespace pyniv
