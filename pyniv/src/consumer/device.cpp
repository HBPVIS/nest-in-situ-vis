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

SUPPRESS_WARNINGS_BEGIN
#include "boost/python/numpy.hpp"
SUPPRESS_WARNINGS_END

#include "niv/consumer/device.hpp"

namespace pyniv {
namespace consumer {
namespace device {

boost::python::list GetTimesteps(const niv::consumer::Device& device) {
  boost::python::list ret_val;
  for (auto t : device.GetTimesteps()) {
    ret_val.append(t);
  }
  return ret_val;
}

boost::python::list GetTimestepsString(const niv::consumer::Device& device) {
  boost::python::list retval;
  const auto timesteps = device.GetTimestepsString();
  for (auto t : timesteps) {
    retval.append(t);
  }
  return retval;
}

static void SetNode(niv::consumer::Device* device, PyObject* node) {
  device->SetNode(boost::python::extract<conduit::Node*>(node));
}

}  // namespace device
}  // namespace consumer

template <>
void expose<niv::consumer::Device>() {
  class_<niv::consumer::Device>("Device", init<const std::string&>())
      .def("GetTimestepsString", &pyniv::consumer::device::GetTimestepsString)
      .def("GetTimesteps", &pyniv::consumer::device::GetTimesteps)
      .def("SetNode", &pyniv::consumer::device::SetNode);
}

}  // namespace pyniv
