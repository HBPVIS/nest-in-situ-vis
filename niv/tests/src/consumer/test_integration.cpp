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
#include "niv/consumer/multimeter.hpp"
#include "niv/consumer/receiver.hpp"
#include "niv/nest_test_data.hpp"

SCENARIO("Consumer integration", "[niv][integration]") {
  GIVEN("The required objects") {
    niv::consumer::Backend backend;

    niv::consumer::Receiver receiver;
    backend.Connect(&receiver);

    niv::consumer::Multimeter multimeter(niv::testing::AnyMultimeterName());
    multimeter.SetAttribute(niv::testing::AnyValueNames()[0]);
    backend.Connect(&multimeter);

    WHEN("The data producer sends data") {
      niv::testing::Send(niv::testing::AnyNestData());

      WHEN("the consuming side receives") {
        backend.Receive();

        WHEN("the multimeter queries the data") {
          multimeter.SetTime(niv::testing::AnyTime());
          multimeter.Update();
          std::vector<double> values{multimeter.GetValues()};

          THEN("the received values are correct") {
            REQUIRE(values == niv::testing::AnyAttributesValues());
          }
        }
      }
    }
  }
}
