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

#include "niv/producer/multimeter.hpp"

namespace niv {

class Testing {
 public:
  Testing() = delete;
  Testing(const Testing&) = delete;
  Testing(Testing&&) = delete;
  ~Testing() = delete;

  Testing& operator=(const Testing&) = delete;
  Testing& operator=(Testing&&) = delete;
};

namespace testing {

std::string AnyAttribute();
std::string AnotherAttribute();
std::string ThirdAttribute();

double AnyTime();
double AnotherTime();

std::vector<double> AnyAttributesValues(double time = 0.0);
std::vector<double> AnotherAttributesValues(double time = 0.0);
std::vector<double> ThirdAttributesValues(double time = 0.0);

std::vector<std::string> AnyValueNames();

std::string AnyMultimeterName();

conduit::Node AnyNestData();

void Send(const conduit::Node& node);

conduit::Node AnyNode();

conduit::Node AnotherNode();

conduit::Node Update();

conduit::Node UpdatedNode();

conduit::Node ADifferentNode();

}  // namespace testing
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_NEST_TEST_DATA_HPP_
