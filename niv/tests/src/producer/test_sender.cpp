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

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "niv/exchange/relay_shared_memory.hpp"
#include "niv/producer/sender.hpp"
#include "niv/testing/nest_test_data.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("data is sent via the producer::Sender",
         "[niv][niv::producer::Sender]") {
  GIVEN("sender and receiving relay") {
    niv::producer::Sender sender;
    conduit::Node sending_node{niv::testing::AnyNode()};
    sender.SetNode(&sending_node);
    niv::exchange::RelaySharedMemory receiver;

    WHEN("data is sent and Receive is called on the relay") {
      sender.Send();
      conduit::Node received_node = receiver.Receive();

      THEN("data is received correctly") {
        REQUIRE_THAT(received_node, Equals(niv::testing::AnyNode()));
      }
    }
  }
}
