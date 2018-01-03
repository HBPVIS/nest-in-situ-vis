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

#include "niv/consumer/backend.hpp"
#include "niv/consumer/device.hpp"

#include "pyniv.hpp"

namespace pyniv {

template <>
void expose<niv::consumer::Backend>() {
  class_<niv::consumer::Backend, noncopyable>("AnalysisBackend")
      .def("Connect",
           static_cast<void (niv::consumer::Backend::*)(  // NOLINT
               niv::consumer::Receiver*)>(&niv::consumer::Backend::Connect))
      .def(
          "Connect",
          static_cast<void (niv::consumer::Backend::*)(niv::consumer::Device*)>(
              &niv::consumer::Backend::Connect))
      .def("Receive", &niv::consumer::Backend::Receive);
}

}  // namespace pyniv
