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

#include <string>

#include "conduit/conduit_node.hpp"

namespace niv {

class AnalysisDevice {
 public:
  AnalysisDevice() = delete;
  explicit AnalysisDevice(const std::string& name);
  AnalysisDevice(const AnalysisDevice&) = default;
  AnalysisDevice(AnalysisDevice&&) = default;
  virtual ~AnalysisDevice() = default;

  AnalysisDevice& operator=(const AnalysisDevice&) = default;
  AnalysisDevice& operator=(AnalysisDevice&&) = default;

  virtual void SetTime(double time);

  virtual void Update() = 0;

  void SetNode(const conduit::Node* node) { node_ = node; }

 protected:
  void SetTimestepNode();
  const conduit::Node* GetTimestepNode() const;

 private:
  const conduit::Node* node_;
  const conduit::Node* timestep_node_{nullptr};
  double time_{0.0};
  std::string name_{""};
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_ANALYSIS_DEVICE_HPP_
