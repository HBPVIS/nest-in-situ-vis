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

#ifndef NIV_INCLUDE_NIV_CONSUMER_MULTIMETER_HPP_
#define NIV_INCLUDE_NIV_CONSUMER_MULTIMETER_HPP_

#include <string>
#include <vector>

#include "niv/consumer/device.hpp"

namespace niv {
namespace consumer {

class Multimeter : public niv::consumer::Device {
 public:
  Multimeter() = delete;
  explicit Multimeter(const std::string& name);
  Multimeter(const Multimeter&) = default;
  Multimeter(Multimeter&&) = default;
  ~Multimeter() = default;

  Multimeter& operator=(const Multimeter&) = default;
  Multimeter& operator=(Multimeter&&) = default;

  std::vector<std::string> GetAttributes(const std::string& time) const;
  std::vector<std::string> GetNeuronIds(const std::string& time,
                                        const std::string& attribute) const;

 protected:
  std::string ConstructPath(const std::string& time,
                            const std::string& attribute) const;
};

}  // namespace consumer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_CONSUMER_MULTIMETER_HPP_
