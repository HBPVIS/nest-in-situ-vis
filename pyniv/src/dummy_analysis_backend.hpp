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

#ifndef NIV_INCLUDE_NIV_DUMMY_ANALYSIS_BACKEND_HPP_
#define NIV_INCLUDE_NIV_DUMMY_ANALYSIS_BACKEND_HPP_

#include "niv/consumer/analysis_backend.hpp"

namespace pyniv {

class DummyAnalysisBackend : public niv::AnalysisBackend {
 public:
  DummyAnalysisBackend();
  DummyAnalysisBackend(const DummyAnalysisBackend&) = delete;
  DummyAnalysisBackend(DummyAnalysisBackend&&) = delete;
  ~DummyAnalysisBackend() = default;

  DummyAnalysisBackend& operator=(const DummyAnalysisBackend&) = delete;
  DummyAnalysisBackend& operator=(DummyAnalysisBackend&&) = delete;

  void Connect(niv::AnalysisDevice* device);
  void Receive();
};

}  // namespace pyniv

#endif  // NIV_INCLUDE_NIV_DUMMY_ANALYSIS_BACKEND_HPP_
