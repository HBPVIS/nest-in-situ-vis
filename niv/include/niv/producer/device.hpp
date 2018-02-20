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

#ifndef NIV_INCLUDE_NIV_PRODUCER_DEVICE_HPP_
#define NIV_INCLUDE_NIV_PRODUCER_DEVICE_HPP_

#include <string>
#include <vector>

SUPPRESS_WARNINGS_BEGIN
#include "conduit/conduit_node.hpp"
SUPPRESS_WARNINGS_END

namespace conduit {

template <>
DataArray<uint64>::~DataArray();

}  // namespace conduit

namespace niv {
namespace producer {

class Device {
 public:
  Device(const Device&) = default;
  Device(Device&&) = default;
  virtual ~Device() = default;

  void SetRecordingTime(double time);

  virtual void Record(std::size_t);
  virtual void Record(std::size_t, const std::vector<double>&);

  Device& operator=(const Device&) = default;
  Device& operator=(Device&&) = default;

 protected:
  Device(const std::string& name, conduit::Node* node);

  conduit::Node& GetTimestepNode();

  const std::string& GetName() { return name_; }
  conduit::Node& GetNode(const std::string& path);

 private:
  conduit::Node* node_{nullptr};
  conduit::Node* timestep_node_{nullptr};
  std::string name_{"recorder"};
};

}  // namespace producer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_PRODUCER_DEVICE_HPP_
