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

#include "conduit/conduit_node.hpp"

#include "niv/consumer/multimeter.hpp"
#include "niv/nest_test_data.hpp"

SCENARIO("a Multimeter provides access to data stored in a conduit node",
         "[niv][niv::consumer][niv::consumer::Multimeter]") {
  GIVEN("A Multimeter with some data") {
    const conduit::Node nest_data{testing::AnyNestData()};
    niv::consumer::Multimeter multimeter(testing::AnyMultimeterName());
    multimeter.SetNode(&nest_data);

    WHEN("The time step is set") {
      multimeter.SetTime(testing::AnyTime());
      WHEN("one attribute is queried") {
        multimeter.SetAttribute(testing::AnyValueNames()[0]);
        multimeter.Update();
        auto result = multimeter.GetValues();
        THEN("the result is correct") {
          REQUIRE_THAT(result,
                       Catch::Matchers::Equals(testing::AnyAttributesValues()));
        }
      }
      WHEN("another attribute is queried") {
        multimeter.SetAttribute(testing::AnyValueNames()[1]);
        multimeter.Update();

        auto result = multimeter.GetValues();
        THEN("the result is correct") {
          REQUIRE_THAT(result, Catch::Matchers::Equals(
                                   testing::AnotherAttributesValues()));
        }
      }
    }
  }
}
