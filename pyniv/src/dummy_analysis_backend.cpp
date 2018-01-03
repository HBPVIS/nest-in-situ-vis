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

#include "dummy_analysis_backend.hpp"

#include "niv/nest_test_data.hpp"

#include "pyniv.hpp"

namespace pyniv {

DummyAnalysisBackend::DummyAnalysisBackend() { node_ = testing::AnyNestData(); }

void DummyAnalysisBackend::Connect(niv::consumer::Device* device) {
  niv::consumer::Backend::Connect(device);
}

void DummyAnalysisBackend::Receive() { niv::consumer::Backend::Receive(); }

template <>
void expose<pyniv::DummyAnalysisBackend>() {
  class_<pyniv::DummyAnalysisBackend, noncopyable>("DummyAnalysisBackend")
      .def("Connect", &DummyAnalysisBackend::Connect)
      .def("Receive", &DummyAnalysisBackend::Receive);
}

}  // namespace pyniv
