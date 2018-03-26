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
  struct Datum {
    using Device_t = Device;

    double time;
  };

  Device() = delete;
  Device(const Device&) = default;
  Device(Device&&) = default;
  virtual ~Device() = default;

  Device& operator=(const Device&) = default;
  Device& operator=(Device&&) = default;

  template <typename Datum_t>
  void Record(const Datum_t& datum);

 protected:
  explicit Device(const std::string& name);

  std::string ConstructPath(const Datum& datum);

  const std::string& GetName() { return name_; }

 private:
  std::string name_{"recorder"};
};

template <>
inline void Device::Record(const Datum& /*datum*/) {}

template <typename Datum_t>
inline void Device::Record(const Datum_t& datum) {
  static_cast<typename Datum_t::Device_t*>(this)->Record(datum);
}

}  // namespace producer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_PRODUCER_DEVICE_HPP_
