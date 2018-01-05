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

#include "analysis_device.hpp"

#include "niv/consumer/device.hpp"

namespace pyniv {

template <>
void expose<AnalysisDeviceWrap>() {
  class_<AnalysisDeviceWrap, noncopyable>("AnalysisDevice", no_init)
      .def("SetTime", &niv::consumer::Device::SetTime)
      .def("Update", pure_virtual(&niv::consumer::Device::Update));
}

}  // namespace pyniv
