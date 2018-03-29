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

#ifndef NIV_INCLUDE_NIV_TESTING_DATA_HPP_
#define NIV_INCLUDE_NIV_TESTING_DATA_HPP_

#include <string>
#include <vector>

#include "niv/producer/nest_multimeter.hpp"

#include "niv/testing/conduit_schema.hpp"

namespace niv {
namespace testing {

class Data;

#if defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

static const char* ANY_DEVICE_NAME{"multimeter A"};
static const char* NOT_A_DEVICE_NAME{"NOT_A_DEVICE_NAME"};

static const char* ANY_MULTIMETER_NAME{"multimeter A"};
static const char* NOT_A_MULTIMETER_NAME{"NOT_A_MULTIMETER_NAME"};

static const char* ANY_SPIKE_DETECTOR_NAME{"spikes A"};
static const char* NOT_A_SPIKE_DETECTOR_NAME{"NOT_A_SPIKE_DETECTOR_NAME"};

static const std::size_t ANY_INDEX{0};
static const std::size_t ANOTHER_INDEX{1};
static const std::size_t THIRD_INDEX{2};

static const std::size_t ANY_TIME_INDEX{ANY_INDEX};
static const std::size_t ANOTHER_TIME_INDEX{ANOTHER_INDEX};
static const std::size_t THIRD_TIME_INDEX{THIRD_INDEX};

static const std::size_t ANY_ATTRIBUTE_INDEX{ANY_INDEX};
static const std::size_t ANOTHER_ATTRIBUTE_INDEX{ANOTHER_INDEX};
static const std::size_t THIRD_ATTRIBUTE_INDEX{THIRD_INDEX};

static const std::size_t ANY_ID_INDEX{ANY_INDEX};
static const std::size_t ANOTHER_ID_INDEX{ANOTHER_INDEX};
static const std::size_t THIRD_ID_INDEX{THIRD_INDEX};

static const std::vector<double> ANY_TIMES{0.1, 0.2, 0.3};

static const double ANY_TIME{ANY_TIMES[ANY_TIME_INDEX]};
static const double ANOTHER_TIME{ANY_TIMES[ANOTHER_TIME_INDEX]};
static const double THIRD_TIME{ANY_TIMES[THIRD_TIME_INDEX]};
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
    AnyTimesString()[ANY_TIME_INDEX], AnyTimesString()[ANOTHER_TIME_INDEX],
    AnyTimesString()[THIRD_TIME_INDEX]};
static const char* ANY_TIME_STRING{ANY_TIMES_STRING[ANY_TIME_INDEX].c_str()};
static const char* ANOTHER_TIME_STRING{
    ANY_TIMES_STRING[ANOTHER_TIME_INDEX].c_str()};
static const char* THIRD_TIME_STRING{
    ANY_TIMES_STRING[THIRD_TIME_INDEX].c_str()};
static const char* NOT_A_TIME_STRING{"NOT_A_TIME"};

static const std::vector<std::string> ANY_ATTRIBUTES{"V_m", "g_e", "g_i"};
static const char* ANY_ATTRIBUTE{ANY_ATTRIBUTES[ANY_ATTRIBUTE_INDEX].c_str()};
static const char* ANOTHER_ATTRIBUTE{
    ANY_ATTRIBUTES[ANOTHER_ATTRIBUTE_INDEX].c_str()};
static const char* THIRD_ATTRIBUTE{
    ANY_ATTRIBUTES[THIRD_ATTRIBUTE_INDEX].c_str()};
static const char* NOT_AN_ATTRIBUTE{"NOT_AN_ATTRIBUTE"};

static const std::vector<std::size_t> ANY_IDS{1ul, 2ul, 3ul};
static const std::size_t ANY_ID{ANY_IDS[ANY_ID_INDEX]};
static const std::size_t ANOTHER_ID{ANY_IDS[ANOTHER_ID_INDEX]};
static const std::size_t THIRD_ID{ANY_IDS[THIRD_ID_INDEX]};
static const std::size_t NOT_AN_ID{THIRD_ID + 1};

static const std::vector<std::string> ANY_IDS_STRING{"1", "2", "3"};
static const char* ANY_ID_STRING{ANY_IDS_STRING[ANY_ID_INDEX].c_str()};
static const char* ANOTHER_ID_STRING{ANY_IDS_STRING[ANOTHER_ID_INDEX].c_str()};
static const char* THIRD_ID_STRING{ANY_IDS_STRING[THIRD_ID_INDEX].c_str()};
static const char* NOT_AN_ID_STRING{"NOT_AN_ID"};

inline std::string PathFor(const std::string& device_name,
                           const std::string& timestep,
                           const std::string& attribute,
                           const std::string& neuron_id) {
  return device_name + '/' + timestep + '/' + attribute + '/' + neuron_id;
}

// clang-format off
static const std::vector<double> ANY_DATA_VALUES{
  0.111, 0.112, 0.113,  0.121, 0.122, 0.123,  0.131, 0.132, 0.133,
  0.211, 0.212, 0.213,  0.221, 0.222, 0.223,  0.231, 0.232, 0.233,
  0.311, 0.312, 0.313,  0.321, 0.322, 0.323,  0.331, 0.332, 0.333};
// clang-format on
static const double ANY_DATA_VALUE{ANY_DATA_VALUES[0]};
static const std::vector<double> ANY_DATA_VALUES_FOR_ATTRIBUTES{
    ANY_DATA_VALUES[0], ANY_DATA_VALUES[3], ANY_DATA_VALUES[6]};

static const std::size_t TIME_STRIDE{9};
static const std::size_t ATTRIBUTE_STRIDE{3};
static const std::size_t ID_STRIDE{1};

inline double ValueAt(std::size_t time_id, std::size_t attribute_id,
                      std::size_t neuron_id) {
  const std::size_t index = time_id * TIME_STRIDE +
                            attribute_id * ATTRIBUTE_STRIDE +
                            neuron_id * ID_STRIDE;
  return ANY_DATA_VALUES[index];
}

static const std::size_t ANY_TIME_OFFSET{ANY_INDEX * niv::testing::TIME_STRIDE};
static const std::size_t ANOTHER_TIME_OFFSET{ANOTHER_INDEX *
                                             niv::testing::TIME_STRIDE};
static const std::size_t THIRD_TIME_OFFSET{THIRD_INDEX *
                                           niv::testing::TIME_STRIDE};
static const std::vector<std::size_t> TIME_OFFSETS{
    ANY_TIME_OFFSET, ANOTHER_TIME_OFFSET, THIRD_TIME_OFFSET};

static const std::size_t ANOTHER_ATTRIBUTE_OFFSET{
    1 * niv::testing::ATTRIBUTE_STRIDE};

static const std::size_t ANY_ID_OFFSET{ANY_INDEX * niv::testing::ID_STRIDE};
static const std::size_t ANOTHER_ID_OFFSET{ANOTHER_INDEX *
                                           niv::testing::ID_STRIDE};
static const std::size_t THIRD_ID_OFFSET{THIRD_INDEX * niv::testing::ID_STRIDE};
static const std::vector<std::size_t> ID_OFFSETS{
    ANY_ID_OFFSET, ANOTHER_ID_OFFSET, THIRD_ID_OFFSET};

inline static const std::string AnyNestDataSchema() {
  std::stringstream s;
  std::size_t offset = 0;
  const std::size_t datum_size = 8;
  s << "{\n";
  s << "  " << conduit_schema::OpenTag(ANY_MULTIMETER_NAME);
  for (auto time : ANY_TIMES) {
    s << "    " << conduit_schema::OpenTag(time);
    for (auto attribute : ANY_ATTRIBUTES) {
      s << "      " << conduit_schema::OpenTag(attribute);
      for (auto id : ANY_IDS) {
        s << "        " << conduit_schema::OpenTag(id);
        s << "          "
          << conduit_schema::DoubleData((offset++) * datum_size);
        s << "        " << conduit_schema::CloseTagNext();
      }
      conduit_schema::RemoveNextIndicator(&s);
      s << "      " << conduit_schema::CloseTagNext();
    }
    conduit_schema::RemoveNextIndicator(&s);
    s << "    " << conduit_schema::CloseTagNext();
  }
  conduit_schema::RemoveNextIndicator(&s);
  s << "  " << conduit_schema::CloseTag();
  s << "}";
  return s.str();
}

static conduit::Node ANY_NEST_DATA{
    AnyNestDataSchema(), const_cast<double*>(ANY_DATA_VALUES.data()), false};

#if defined __GNUC__
#pragma GCC diagnostic pop
#endif

}  // namespace testing
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_TESTING_DATA_HPP_
