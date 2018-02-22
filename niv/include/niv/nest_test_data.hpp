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

#if defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

static const char* ANY_MULTIMETER_NAME{"multimeter A"};

static const std::vector<double> ANY_TIMES{0.1, 0.2, 0.3};
static const double ANY_TIME{ANY_TIMES[0]};
static const double ANOTHER_TIME{ANY_TIMES[1]};
static const double THIRD_TIME{ANY_TIMES[2]};

static const std::vector<double> ANY_TIME_OFFSETS{0.0123, 0.0234, 0.0345};
static const double ANY_TIME_OFFSET{ANY_TIME_OFFSETS[0]};
static const double ANOTHER_TIME_OFFSET{ANY_TIME_OFFSETS[1]};
static const double THIRD_TIME_OFFSET{ANY_TIME_OFFSETS[2]};

static const std::vector<std::string> ANY_ATTRIBUTES{"V_m", "g_e", "g_i"};
static const char* ANY_ATTRIBUTE{ANY_ATTRIBUTES[0].c_str()};
static const char* ANOTHER_ATTRIBUTE{ANY_ATTRIBUTES[1].c_str()};
static const char* THIRD_ATTRIBUTE{ANY_ATTRIBUTES[2].c_str()};

static const std::vector<std::string> ANY_IDS{"1", "2", "3"};
static const char* ANY_ID{ANY_IDS[0].c_str()};
static const char* ANOTHER_ID{ANY_IDS[1].c_str()};
static const char* THIRD_ID{ANY_IDS[2].c_str()};

// clang-format off
static const std::vector<double> ANY_VALUES{
  0.111, 0.112, 0.113,  0.121, 0.122, 0.123,  0.131, 0.132, 0.133,
  0.211, 0.212, 0.213,  0.221, 0.222, 0.223,  0.231, 0.232, 0.233,
  0.311, 0.312, 0.313,  0.321, 0.322, 0.323,  0.331, 0.332, 0.333};
// clang-format on
static const double ANY_VALUE{ANY_VALUES[0]};

#if defined __GNUC__
#pragma GCC diagnostic pop
#endif

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
conduit::Node UpdatedNodeAllZeros();

conduit::Node ADifferentNode();

}  // namespace testing
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_NEST_TEST_DATA_HPP_
