//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017 RWTH Aachen University, Germany,
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

#include "catch/catch.hpp"

#include "niv/consumer/receiver.hpp"
#include "niv/relay_shared_memory.hpp"

#include "../conduit_node_helper.hpp"

SCENARIO("received data is aggregated in the consumer::Receiver",
         "[niv][niv::consumer][niv::consumer::Receiver]") {
  GIVEN("A SchnchronizedAggregatingReceiver and a sending relay") {
    niv::consumer::Receiver receiver;
    conduit::Node receiving_node;
    receiver.SetNode(&receiving_node);
    niv::RelaySharedMemory sender;

    WHEN("Data is sent and a receive is triggered") {
      sender.Send(testing::AnyNode());
      receiver.Receive();
      THEN("it is received correctly") {
        REQUIRE_THAT(receiving_node, Equals(testing::AnyNode()));
      }

      WHEN("an update is sent and a receive is triggered") {
        sender.Send(testing::Update());
        receiver.Receive();
        THEN("then the data has been updated") {
          REQUIRE_THAT(receiving_node, Equals(testing::UpdatedNode()));
        }
      }
    }
  }
}
