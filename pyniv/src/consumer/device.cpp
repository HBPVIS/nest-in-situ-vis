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

struct DeviceWrap : niv::consumer::Device, wrapper<niv::consumer::Device> {
  explicit DeviceWrap(const std::string& name) : niv::consumer::Device(name) {}
  void Update() { this->get_override("Update")(); }

  boost::python::list GetTimesteps() {
    boost::python::list ret_val;
    for (auto t : Device::GetTimesteps()) {
      ret_val.append(t);
    }
    return ret_val;
  }

  static void SetNodePointer(niv::consumer::Device* device, PyObject* node) {
    device->SetNode(boost::python::extract<conduit::Node*>(node));
  }
};

}  // namespace consumer

template <>
void expose<niv::consumer::Device>() {
  class_<consumer::DeviceWrap, noncopyable>("Device",
                                            init<const std::string&>())
      .def("GetTimesteps", &pyniv::consumer::DeviceWrap::GetTimesteps)
      .def("SetNode", &pyniv::consumer::DeviceWrap::SetNodePointer)
      .def("SetTime", &niv::consumer::Device::SetTime)
      .def("Update", pure_virtual(&niv::consumer::Device::Update));
}

}  // namespace pyniv
