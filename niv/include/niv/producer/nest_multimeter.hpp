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

#ifndef NIV_INCLUDE_NIV_PRODUCER_NEST_MULTIMETER_HPP_
#define NIV_INCLUDE_NIV_PRODUCER_NEST_MULTIMETER_HPP_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "niv/producer/device.hpp"

namespace niv {
namespace producer {

class NestMultimeter final : public Device {
 public:
  struct Datum : public Device::Datum {
    using Device_t = NestMultimeter;

    Datum(double time, std::string neuron_id, const std::vector<double>& values)
        : Device::Datum{time}, neuron_id{neuron_id}, values{values} {}
    Datum(double time, std::size_t neuron_id, const std::vector<double>& values)
        : Device::Datum{time},
          neuron_id{NestMultimeter::IdString(neuron_id)},
          values{values} {}
    std::string neuron_id;
    std::vector<double> values;
  };

  NestMultimeter(const std::string& name,
                 const std::vector<std::string>& value_names,
                 conduit::Node* node);
  NestMultimeter(const NestMultimeter&) = default;
  NestMultimeter(NestMultimeter&&) = default;
  virtual ~NestMultimeter() = default;

  NestMultimeter& operator=(const NestMultimeter&) = default;
  NestMultimeter& operator=(NestMultimeter&&) = default;

  static std::unique_ptr<NestMultimeter> New(
      const std::string& name, const std::vector<std::string>& value_names,
      conduit::Node* node);

  void Record(const Datum& datum) { RecordImplementation(datum); }
  void RecordImplementation(const Datum& datum);

 private:
  static std::string IdString(std::size_t id);

  std::string ConstructPath(const Datum& datum, std::size_t attribute_index);

  std::vector<std::string> value_names_;
};  // namespace producer

}  // namespace producer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_PRODUCER_NEST_MULTIMETER_HPP_
