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

#ifndef NIV_INCLUDE_NIV_PRODUCER_MULTIMETER_HPP_
#define NIV_INCLUDE_NIV_PRODUCER_MULTIMETER_HPP_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "niv/producer/recorder.hpp"

namespace niv {
namespace producer {

class Multimeter final : public Recorder {
 public:
  Multimeter(const std::string& name,
             const std::vector<std::string>& value_names, conduit::Node* node);
  Multimeter(const Multimeter&) = default;
  Multimeter(Multimeter&&) = default;
  virtual ~Multimeter() = default;

  void Record(std::size_t id, const std::vector<double>& values) override;

  Multimeter& operator=(const Multimeter&) = default;
  Multimeter& operator=(Multimeter&&) = default;

  static std::unique_ptr<Multimeter> New(
      const std::string& name, const std::vector<std::string>& value_names,
      conduit::Node* node);

 private:
  void RecordValue(std::string id_string, const std::vector<double> values,
                   std::size_t value_index);
  std::string IdString(std::size_t id) const;

  std::vector<std::string> value_names_;
};

}  // namespace producer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_PRODUCER_MULTIMETER_HPP_
