//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017-2018 RWTH Aachen University, Germany,
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

#ifndef NIV_INCLUDE_NIV_CONSUMER_NEST_MULTIMETER_HPP_
#define NIV_INCLUDE_NIV_CONSUMER_NEST_MULTIMETER_HPP_

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/consumer/device.hpp"

namespace niv {
namespace consumer {

class NestMultimeter : public consumer::Device {
 public:
  NestMultimeter() = delete;
  explicit NestMultimeter(const std::string& name);
  NestMultimeter(const NestMultimeter&) = default;
  NestMultimeter(NestMultimeter&&) = default;
  ~NestMultimeter() = default;

  NestMultimeter& operator=(const NestMultimeter&) = default;
  NestMultimeter& operator=(NestMultimeter&&) = default;

  void SetAttribute(const std::string& attribute);

  void Update();

  const std::vector<double>& GetValues() const;

 private:
  void SetValues();

  std::vector<double> values_;
  std::string attribute_{""};
};

}  // namespace consumer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_CONSUMER_NEST_MULTIMETER_HPP_
