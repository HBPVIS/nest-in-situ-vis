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

#include <cmath>

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/consumer/arbor_multimeter.hpp"
#include "niv/nest_test_data.hpp"

namespace niv {
namespace consumer {

ArborMultimeter::ArborMultimeter(const std::string& name) : Multimeter(name) {}

std::vector<double> ArborMultimeter::GetTimestepData(
    const std::string& time, const std::string& attribute) const {
  std::vector<double> retval;
  const auto neuron_ids{GetNeuronIds(time, attribute)};
  for (auto curr_neuron_id : neuron_ids) {
    retval.push_back(GetDatum(time, attribute, curr_neuron_id));
  }
  return retval;
}

std::vector<double> ArborMultimeter::GetTimeSeriesData(
    const std::string& attribute, const std::string& neuron_id) const {
  std::vector<double> retval;
  const auto timesteps = GetTimestepsString();
  retval.reserve(timesteps.size());
  for (auto time : timesteps) {
    retval.push_back(GetDatum(time, attribute, neuron_id));
  }
  return retval;
}

double ArborMultimeter::GetDatum(const std::string& time,
                                 const std::string& attribute,
                                 const std::string& neuron_id) const {
  return GetValue(ConstructPath(time, attribute, neuron_id));
}

double ArborMultimeter::GetValue(const std::string& path) const {
  const conduit::Node* node{GetNode(path)};
  return (node != nullptr) ? node->as_double() : std::nan("");
}

}  // namespace consumer
}  // namespace niv
