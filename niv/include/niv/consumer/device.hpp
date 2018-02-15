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

#ifndef NIV_INCLUDE_NIV_CONSUMER_DEVICE_HPP_
#define NIV_INCLUDE_NIV_CONSUMER_DEVICE_HPP_

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

namespace niv {
namespace consumer {

class Device {
 public:
  Device() = delete;
  Device(const Device&) = default;
  Device(Device&&) = default;
  virtual ~Device() = default;

  Device& operator=(const Device&) = default;
  Device& operator=(Device&&) = default;

  const std::vector<double>& GetTimesteps();

  virtual void SetTime(double time);

  virtual void Update() = 0;

  void SetNode(const conduit::Node* node) { node_ = node; }

  void Print() const;

 protected:
  explicit Device(const std::string& name);

  void SetTimestepNode();
  const conduit::Node* GetTimestepNode() const;

 private:
  const conduit::Node* node_{nullptr};
  const conduit::Node* timestep_node_{nullptr};

  std::vector<double> timesteps_;

  double time_{0.0};
  std::string name_{""};
};

}  // namespace consumer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_CONSUMER_DEVICE_HPP_
