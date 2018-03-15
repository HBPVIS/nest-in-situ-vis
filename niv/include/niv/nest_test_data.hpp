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

#include "niv/producer/nest_multimeter.hpp"

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
static const char* NOT_A_MULTIMETER_NAME{"NOT_A_MULTIMETER_NAME"};

static const std::vector<double> ANY_TIMES{0.1, 0.2, 0.3};
static const double ANY_TIME{ANY_TIMES[0]};
static const double ANOTHER_TIME{ANY_TIMES[1]};
static const double THIRD_TIME{ANY_TIMES[2]};
static const double NOT_A_TIME{ANY_TIMES.back() + 1.0};

inline std::vector<std::string> AnyTimesString() {
  std::vector<std::string> retval;
  for (auto time : ANY_TIMES) {
    std::stringstream s;
    s << time;
    retval.push_back(s.str());
  }
  return retval;
}
static const std::vector<std::string> ANY_TIMES_STRING{
    AnyTimesString()[0], AnyTimesString()[1], AnyTimesString()[2]};
static const char* ANY_TIME_STRING{ANY_TIMES_STRING[0].c_str()};
static const char* ANOTHER_TIME_STRING{ANY_TIMES_STRING[1].c_str()};
static const char* THIRD_TIME_STRING{ANY_TIMES_STRING[2].c_str()};
static const char* NOT_A_TIME_STRING{"NOT_A_TIME"};

static const std::vector<std::string> ANY_ATTRIBUTES{"V_m", "g_e", "g_i"};
static const char* ANY_ATTRIBUTE{ANY_ATTRIBUTES[0].c_str()};
static const char* ANOTHER_ATTRIBUTE{ANY_ATTRIBUTES[1].c_str()};
static const char* THIRD_ATTRIBUTE{ANY_ATTRIBUTES[2].c_str()};
static const char* NOT_AN_ATTRIBUTE{"NOT_AN_ATTRIBUTE"};

static const std::vector<std::string> ANY_IDS{"1", "2", "3"};
static const char* ANY_ID{ANY_IDS[0].c_str()};
static const char* ANOTHER_ID{ANY_IDS[1].c_str()};
static const char* THIRD_ID{ANY_IDS[2].c_str()};
static const char* NOT_AN_ID{"NOT_AN_ID"};

// clang-format off
static const std::vector<double> ANY_VALUES{
  0.111, 0.112, 0.113,  0.121, 0.122, 0.123,  0.131, 0.132, 0.133,
  0.211, 0.212, 0.213,  0.221, 0.222, 0.223,  0.231, 0.232, 0.233,
  0.311, 0.312, 0.313,  0.321, 0.322, 0.323,  0.331, 0.332, 0.333};
// clang-format on
static const double ANY_VALUE{ANY_VALUES[0]};
static const std::size_t TIME_STRIDE{9};
static const std::size_t ATTRIBUTE_STRIDE{3};
static const std::size_t ID_STRIDE{1};

static const std::size_t ANY_TIME_OFFSET{0 * niv::testing::TIME_STRIDE};
static const std::size_t ANOTHER_TIME_OFFSET{1 * niv::testing::TIME_STRIDE};
static const std::size_t THIRD_TIME_OFFSET{2 * niv::testing::TIME_STRIDE};
static const std::vector<std::size_t> TIME_OFFSETS{
    ANY_TIME_OFFSET, ANOTHER_TIME_OFFSET, THIRD_TIME_OFFSET};
static const std::size_t ANOTHER_ATTRIBUTE_OFFSET{
    1 * niv::testing::ATTRIBUTE_STRIDE};
static const std::size_t THIRD_ID_OFFSET{2 * niv::testing::ID_STRIDE};

template <typename T>
inline std::string OpenTag(T tag) {
  std::stringstream s;
  s << '\"' << tag << '\"' << ":{ \n";
  return s.str();
}

inline std::string CloseTag() { return std::string("} \n"); }
inline std::string CloseTagNext() { return std::string("}, \n"); }

inline std::string DoubleData(std::size_t offset) {
  std::stringstream s;
  s << "dtype:float64, ";
  s << "number_of_elements:1, ";
  s << "offset:" << offset << ", ";
  s << "stride:8, ";
  s << "element_bytes:8";
  s << "\n";
  return s.str();
}

inline void RemoveNextIndicator(std::stringstream* s) {
  s->clear();
  s->seekp(s->str().size() - 3);
  *s << " \n";
}

inline static const std::string AnyNestDataSchema() {
  std::stringstream s;
  std::size_t offset = 0;
  const std::size_t datum_size = 8;
  s << "{\n";
  s << "  " << OpenTag(ANY_MULTIMETER_NAME);
  for (auto time : ANY_TIMES) {
    s << "    " << OpenTag(time);
    for (auto attribute : ANY_ATTRIBUTES) {
      s << "      " << OpenTag(attribute);
      for (auto id : ANY_IDS) {
        s << "        " << OpenTag(id);
        s << "          " << DoubleData((offset++) * datum_size);
        s << "        " << CloseTagNext();
      }
      RemoveNextIndicator(&s);
      s << "      " << CloseTagNext();
    }
    RemoveNextIndicator(&s);
    s << "    " << CloseTagNext();
  }
  RemoveNextIndicator(&s);
  s << "  " << CloseTag();
  s << "}";
  return s.str();
}

static conduit::Node ANY_NEST_DATA{
    AnyNestDataSchema(), const_cast<double*>(ANY_VALUES.data()), false};

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
