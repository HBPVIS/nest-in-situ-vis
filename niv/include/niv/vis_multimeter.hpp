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

#ifndef NIV_INCLUDE_NIV_VIS_MULTIMETER_HPP_
#define NIV_INCLUDE_NIV_VIS_MULTIMETER_HPP_

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/analysis_device.hpp"

namespace niv {

class VisMultimeter : public AnalysisDevice {
 public:
  VisMultimeter() = delete;
  explicit VisMultimeter(const std::string& name,
                         const std::vector<std::string>& attribute_names);
  VisMultimeter(const VisMultimeter&) = delete;
  VisMultimeter(VisMultimeter&&) = delete;
  ~VisMultimeter() = default;

  VisMultimeter& operator=(const VisMultimeter&) = delete;
  VisMultimeter& operator=(VisMultimeter&&) = delete;

  void SetTime(double time);

  const std::vector<double> GetAttributeValues(
      const std::string& attribute_name) const;

  void Update() override;

 private:
  void SetTimestepNode();
  void SetValues();
  std::vector<double> ExtractValues(std::size_t attribute_index) const;
  const conduit::Node* GetAttributeNode(std::size_t attribute_index) const;
  std::vector<double> GetAttributeNodesValues(
      const conduit::Node* attribute_node) const;

  double time_{0.0};
  std::string name_{""};
  std::vector<std::string> attribute_names_;
  std::vector<std::vector<double>> values_;
  const conduit::Node* timestep_node_{nullptr};
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_VIS_MULTIMETER_HPP_
