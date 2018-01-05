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

#ifndef NIV_INCLUDE_NIV_NEST_TEST_DATA_HPP_
#define NIV_INCLUDE_NIV_NEST_TEST_DATA_HPP_

#include <string>
#include <vector>

#include "niv/multimeter.hpp"

namespace testing {
std::string AnyAttribute() { return "V_m"; }
std::string AnotherAttribute() { return "g_m"; }
std::string ThirdAttribute() { return "g_i"; }

constexpr double AnyTime();
constexpr double AnyTime() { return 0.0; }

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
  niv::Multimeter multimeter(AnyMultimeterName(), AnyValueNames(), &node);
  multimeter.SetRecordingTime(AnyTime());
  for (auto i = 0u; i < AnyAttributesValues().size(); ++i) {
    multimeter.Record(i, std::vector<double>{AnyAttributesValues()[i],
                                             AnotherAttributesValues()[i],
                                             ThirdAttributesValues()[i]});
  }

  return node;
}

}  // namespace testing

#endif  // NIV_INCLUDE_NIV_NEST_TEST_DATA_HPP_
