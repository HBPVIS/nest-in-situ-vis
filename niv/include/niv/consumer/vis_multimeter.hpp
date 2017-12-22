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

#ifndef NIV_INCLUDE_NIV_CONSUMER_VIS_MULTIMETER_HPP_
#define NIV_INCLUDE_NIV_CONSUMER_VIS_MULTIMETER_HPP_

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/consumer/analysis_device.hpp"

namespace niv {

class VisMultimeter : public AnalysisDevice {
 public:
  VisMultimeter() = delete;
  explicit VisMultimeter(const std::string& name);
  VisMultimeter(const VisMultimeter&) = default;
  VisMultimeter(VisMultimeter&&) = default;
  ~VisMultimeter() = default;

  VisMultimeter& operator=(const VisMultimeter&) = default;
  VisMultimeter& operator=(VisMultimeter&&) = default;

  void SetAttribute(const std::string& attribute);

  void Update() override;

  const std::vector<double>& GetValues() const;

 private:
  void SetValues();

  std::vector<double> values_;
  std::string attribute_{""};
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_CONSUMER_VIS_MULTIMETER_HPP_
