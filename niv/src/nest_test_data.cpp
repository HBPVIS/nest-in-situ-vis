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

#include "niv/nest_test_data.hpp"

#include <string>
#include <vector>

#include "niv/exchange/relay_shared_memory.hpp"

namespace niv {
namespace testing {

std::string AnyAttribute() { return "V_m"; }
std::string AnotherAttribute() { return "g_m"; }
std::string ThirdAttribute() { return "g_i"; }

double AnyTime() { return 0.0; }
double AnotherTime() { return 0.1; }

std::vector<double> AnyAttributesValues(double time) {
  const double timed_offset = 1.1 * time + 2.2;
  return std::vector<double>{0.0 + timed_offset, -0.1 + timed_offset,
                             0.2 + timed_offset, -0.3 + timed_offset,
                             0.4 + timed_offset, -0.5 + timed_offset};
}
std::vector<double> AnotherAttributesValues(double time) {
  const double timed_offset = 2.2 * time + 3.3;
  return std::vector<double>{1.0 + timed_offset, -1.1 + timed_offset,
                             1.2 + timed_offset, -1.3 + timed_offset,
                             1.4 + timed_offset, -1.5 + timed_offset};
}
std::vector<double> ThirdAttributesValues(double time) {
  const double timed_offset = 3.3 * time + 4.4;
  return std::vector<double>{-2.01 + timed_offset, 3.12 + timed_offset,
                             -4.23 + timed_offset, 5.34 + timed_offset,
                             -6.45 + timed_offset, 7.56 + timed_offset};
}

std::vector<std::string> AnyValueNames() {
  return std::vector<std::string>{AnyAttribute(), AnotherAttribute(),
                                  ThirdAttribute()};
}

std::string AnyMultimeterName() { return "multimeter A"; }

conduit::Node AnyNestData() {
  conduit::Node node;
  niv::producer::Multimeter multimeter(AnyMultimeterName(), AnyValueNames(),
                                       &node);
  multimeter.SetRecordingTime(AnyTime());
  for (auto i = 0u; i < AnyAttributesValues().size(); ++i) {
    multimeter.Record(i, std::vector<double>{AnyAttributesValues()[i],
                                             AnotherAttributesValues()[i],
                                             ThirdAttributesValues()[i]});
  }

  multimeter.SetRecordingTime(AnotherTime());
  for (auto i = 0u; i < AnyAttributesValues().size(); ++i) {
    multimeter.Record(
        i, std::vector<double>{AnyAttributesValues(AnotherTime())[i],
                               AnotherAttributesValues(AnotherTime())[i],
                               ThirdAttributesValues(AnotherTime())[i]});
  }

  return node;
}

void Send(const conduit::Node& node) {
  exchange::RelaySharedMemory relay;
  relay.Send(node);
}

conduit::Node AnyNode() {
  conduit::Node node;
  node["A/B/C"] = 3.1415;
  node["A/B/D"] = 4.124;
  node["A/E"] = 42.0;
  return node;
}

conduit::Node AnotherNode() {
  conduit::Node node;
  node["A/B/C"] = 2.0 * 3.1415;
  node["A/B/D"] = 3.0 * 4.124;
  node["A/E"] = 4.0 * 42.0;
  return node;
}

conduit::Node Update() {
  conduit::Node node;
  node["A/B/F"] = 2.0 * 3.1415;
  node["A/B/G"] = 3.0 * 4.124;
  node["A/H"] = 4.0 * 42.0;
  return node;
}

conduit::Node UpdatedNode() {
  conduit::Node node;
  node["A/B/C"] = 3.1415;
  node["A/B/D"] = 4.124;
  node["A/E"] = 42.0;
  node["A/B/F"] = 2.0 * 3.1415;
  node["A/B/G"] = 3.0 * 4.124;
  node["A/H"] = 4.0 * 42.0;
  return node;
}

conduit::Node UpdatedNodeAllZeros() {
  conduit::Node node;
  node["A/B/C"] = 0.0;
  node["A/B/D"] = 0.0;
  node["A/E"] = 0.0;
  node["A/B/F"] = 0.0;
  node["A/B/G"] = 0.0;
  node["A/H"] = 0.0;
  return node;
}

conduit::Node ADifferentNode() { return Update(); }

}  // namespace testing
}  // namespace niv
