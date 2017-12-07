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

#ifndef NIV_INCLUDE_NIV_ANALYSIS_DEVICE_HPP_
#define NIV_INCLUDE_NIV_ANALYSIS_DEVICE_HPP_

#include "conduit/conduit_node.hpp"

namespace niv {

class AnalysisDevice {
 public:
  AnalysisDevice() = default;
  AnalysisDevice(const AnalysisDevice&) = delete;
  AnalysisDevice(AnalysisDevice&&) = delete;
  virtual ~AnalysisDevice() = default;

  AnalysisDevice& operator=(const AnalysisDevice&) = delete;
  AnalysisDevice& operator=(AnalysisDevice&&) = delete;

  virtual void Update() = 0;

  void SetNode(const conduit::Node& node) { node_.set_external(node); }

 private:
  conduit::Node node_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_ANALYSIS_DEVICE_HPP_
