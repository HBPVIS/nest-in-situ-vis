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

#ifndef NIV_INCLUDE_NIV_ANALYSIS_BACKEND_HPP_
#define NIV_INCLUDE_NIV_ANALYSIS_BACKEND_HPP_

#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/analysis_device.hpp"
#include "niv/analysis_receiver.hpp"

namespace niv {

class AnalysisBackend {
 public:
  AnalysisBackend() = default;
  AnalysisBackend(const AnalysisBackend&) = delete;
  AnalysisBackend(AnalysisBackend&&) = delete;
  ~AnalysisBackend() = default;

  AnalysisBackend& operator=(const AnalysisBackend&) = delete;
  AnalysisBackend& operator=(AnalysisBackend&&) = delete;

  void Connect(niv::AnalysisReceiver* receiver);
  void Connect(niv::AnalysisDevice* device);
  void Receive();

 private:
  niv::AnalysisReceiver* receiver_{nullptr};
  std::vector<niv::AnalysisDevice*> devices_;

  conduit::Node node_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_ANALYSIS_BACKEND_HPP_
