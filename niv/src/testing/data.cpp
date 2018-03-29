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

#include "niv/testing/data.hpp"

#include <string>
#include <vector>

#include "niv/exchange/relay_shared_memory.hpp"

namespace niv {
namespace testing {

void unused() { (void)(ANY_MULTIMETER_NAME); }

std::vector<std::string> AnyValueNames() {
  return std::vector<std::string>{"V_m", "g_e", "g_i"};
}
std::string AnyAttribute() { return AnyValueNames()[0]; }
std::string AnotherAttribute() { return AnyValueNames()[1]; }
std::string ThirdAttribute() { return AnyValueNames()[2]; }

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

std::string AnyMultimeterName() { return "multimeter A"; }

}  // namespace testing
}  // namespace niv
