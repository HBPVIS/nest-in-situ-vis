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

#include "niv/consumer/nest_multimeter.hpp"

#include <cmath>

#include <string>
#include <vector>

namespace niv {
namespace consumer {

NestMultimeter::NestMultimeter(const std::string& name)
    : consumer::Multimeter{name} {}

std::vector<double> NestMultimeter::GetTimestepData(
    const std::string& time, const std::string& attribute) const {
  std::vector<double> retval;
  const auto neuron_ids{GetNeuronIds(time, attribute)};
  for (auto curr_neuron_id : neuron_ids) {
    retval.push_back(GetDatum(time, attribute, curr_neuron_id));
  }
  return retval;
}

std::vector<double> NestMultimeter::GetTimeSeriesData(
    const std::string& attribute, const std::string& neuron_id) const {
  std::vector<double> retval;
  const auto timesteps = GetTimestepsString();
  retval.reserve(timesteps.size());
  for (auto time : timesteps) {
    retval.push_back(GetDatum(time, attribute, neuron_id));
  }
  return retval;
}

double NestMultimeter::GetDatum(const std::string& time,
                                const std::string& attribute,
                                const std::string& neuron_id) const {
  return GetValue(ConstructPath(time, attribute, neuron_id));
}

double NestMultimeter::GetValue(const std::string& path) const {
  const conduit::Node* node{GetNode(path)};
  return (node != nullptr) ? node->as_double() : std::nan("");
}

// ------------------------------------------------------------

void NestMultimeter::SetAttribute(const std::string& attribute) {
  attribute_ = attribute;
}

void NestMultimeter::Update() {
  SetValues();
}

void NestMultimeter::SetValues() {
  values_.clear();
}

const std::vector<double>& NestMultimeter::GetValues() const { return values_; }

}  // namespace consumer
}  // namespace niv
