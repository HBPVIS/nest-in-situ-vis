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

#include <vector>

#include "catch/catch.hpp"

#include "niv/consumer/backend.hpp"
#include "niv/consumer/nest_multimeter.hpp"
#include "niv/consumer/receiver.hpp"
#include "niv/nest_test_data.hpp"

SCENARIO("Consumer integration", "[niv][integration]") {
  GIVEN("The required objects") {
    niv::consumer::Backend backend;

    niv::consumer::Receiver receiver;
    backend.Connect(&receiver);

    niv::consumer::NestMultimeter multimeter(niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetAttribute(niv::testing::ANY_ATTRIBUTE);
    backend.Connect(&multimeter);

    WHEN("The data producer sends data") {
      niv::testing::Send(niv::testing::ANY_NEST_DATA);

      WHEN("the consuming side receives") {
        backend.Receive();

        WHEN("the multimeter queries the data") {
          std::vector<double> values_at_t0{multimeter.GetTimestepData(
              niv::testing::ANY_TIME_STRING, niv::testing::ANY_ATTRIBUTE)};
          std::vector<double> values_at_t1{multimeter.GetTimestepData(
              niv::testing::ANOTHER_TIME_STRING, niv::testing::ANY_ATTRIBUTE)};

          THEN("the received values are correct") {
            const std::vector<double> expected_at_t0{
                niv::testing::ValueAt(niv::testing::ANY_TIME_INDEX,
                                      niv::testing::ANY_ATTRIBUTE_INDEX,
                                      niv::testing::ANY_ID_INDEX),
                niv::testing::ValueAt(niv::testing::ANY_TIME_INDEX,
                                      niv::testing::ANY_ATTRIBUTE_INDEX,
                                      niv::testing::ANOTHER_ID_INDEX),
                niv::testing::ValueAt(niv::testing::ANY_TIME_INDEX,
                                      niv::testing::ANY_ATTRIBUTE_INDEX,
                                      niv::testing::THIRD_ID_INDEX)};
            REQUIRE(values_at_t0 == expected_at_t0);
            const std::vector<double> expected_at_t1{
                niv::testing::ValueAt(niv::testing::ANOTHER_TIME_INDEX,
                                      niv::testing::ANY_ATTRIBUTE_INDEX,
                                      niv::testing::ANY_ID_INDEX),
                niv::testing::ValueAt(niv::testing::ANOTHER_TIME_INDEX,
                                      niv::testing::ANY_ATTRIBUTE_INDEX,
                                      niv::testing::ANOTHER_ID_INDEX),
                niv::testing::ValueAt(niv::testing::ANOTHER_TIME_INDEX,
                                      niv::testing::ANY_ATTRIBUTE_INDEX,
                                      niv::testing::THIRD_ID_INDEX)};
            REQUIRE(values_at_t1 == expected_at_t1);
          }
        }
      }
    }
  }
}
