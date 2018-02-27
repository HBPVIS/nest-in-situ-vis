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

#include "catch/Catch.hpp"

#include "niv/consumer/arbor_multimeter.hpp"
#include "niv/nest_test_data.hpp"

SCENARIO(
    "ArborMultimeter lists the neuron ids stored for an attribute in a "
    "timestep",
    "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("neuron ids are requested") {
      auto ids{multimeter.GetNeuronIds(niv::testing::ANY_TIME,
                                       niv::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter provides the ids") {
        REQUIRE(ids == niv::testing::ANY_IDS);
      }
    }
  }
}

SCENARIO("ArborMultimeter reports no neuron ids if these cannot be found",
         "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  GIVEN("a multimeter with an incorrect name providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("neuron ids are requested") {
      auto ids{multimeter.GetNeuronIds(niv::testing::ANY_TIME,
                                       niv::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }
  }

  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("neuron ids are requested for an invalid timestep") {
      auto ids{multimeter.GetNeuronIds(niv::testing::NOT_A_TIME,
                                       niv::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }

    WHEN("neuron ids are requested for an invalid attribute") {
      auto ids{multimeter.GetNeuronIds(niv::testing::ANY_TIME,
                                       niv::testing::NOT_AN_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }
  }
}
