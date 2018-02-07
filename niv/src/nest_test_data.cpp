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

std::vector<double> AnyAttributesValues() {
  return std::vector<double>{0.0, -0.1, 0.2, -0.3, 0.4, -0.5};
}
std::vector<double> AnotherAttributesValues() {
  return std::vector<double>{1.0, -1.1, 1.2, -1.3, 1.4, -1.5};
}
std::vector<double> ThirdAttributesValues() {
  return std::vector<double>{-2.01, 3.12, -4.23, 5.34, -6.45, 7.56};
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

conduit::Node ADifferentNode() { return Update(); }

}  // namespace testing
}  // namespace niv
