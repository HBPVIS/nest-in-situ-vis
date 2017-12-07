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

namespace niv {

class VisMultimeter {
 public:
  VisMultimeter() = delete;
  explicit VisMultimeter(const std::string& name,
                         const std::vector<std::string>& value_names,
                         const conduit::Node& node);
  VisMultimeter(const VisMultimeter&) = delete;
  VisMultimeter(VisMultimeter&&) = delete;
  ~VisMultimeter() = default;

  VisMultimeter& operator=(const VisMultimeter&) = delete;
  VisMultimeter& operator=(VisMultimeter&&) = delete;

  void SetTime(double time);

  std::vector<double> GetAttribute(const std::string& value_name);

 private:
  std::string name_;
  std::vector<std::string> value_names_;
  conduit::Node node_;
  conduit::Node* timestep_node_{nullptr};
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_VIS_MULTIMETER_HPP_
