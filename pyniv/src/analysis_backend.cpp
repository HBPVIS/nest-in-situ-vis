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

#include "niv/consumer/analysis_backend.hpp"
#include "niv/consumer/analysis_device.hpp"

#include "pyniv.hpp"

namespace pyniv {

template <>
void expose<niv::AnalysisBackend>() {
  class_<niv::AnalysisBackend, noncopyable>("AnalysisBackend")
      .def("Connect",
           static_cast<void (niv::AnalysisBackend::*)(niv::AnalysisReceiver*)>(
               &niv::AnalysisBackend::Connect))
      .def("Connect",
           static_cast<void (niv::AnalysisBackend::*)(niv::AnalysisDevice*)>(
               &niv::AnalysisBackend::Connect))
      .def("Receive", &niv::AnalysisBackend::Receive);
}

}  // namespace pyniv
