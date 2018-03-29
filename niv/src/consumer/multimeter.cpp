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

#include "niv/consumer/multimeter.hpp"

#include <string>
#include <vector>

namespace niv {
namespace consumer {

Multimeter::Multimeter(const std::string& name) : Device(name) {}

std::vector<std::string> Multimeter::GetAttributes(
    const std::string& time) const {
  return GetChildNames(Device::ConstructPath(time));
}

std::vector<std::string> Multimeter::GetNeuronIds(
    const std::string& time, const std::string& attribute) const {
  return GetChildNames(ConstructPath(time, attribute));
}

std::string Multimeter::ConstructPath(const std::string& time,
                                      const std::string& attribute) const {
  return Device::ConstructPath(time) + '/' + attribute;
}

std::string Multimeter::ConstructPath(const std::string& time,
                                      const std::string& attribute,
                                      const std::string& neuron_id) const {
  return ConstructPath(time, attribute) + "/" + neuron_id;
}

}  // namespace consumer
}  // namespace niv
