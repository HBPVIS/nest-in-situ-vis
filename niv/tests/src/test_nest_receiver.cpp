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

#include "niv/nest_receiver.hpp"
#include "niv/synchronized_relay_shared_memory_access.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("received data is aggregated in the NestReceiver",
         "[niv][niv::NestReceiver]") {
  GIVEN("A NestReceiver and a sending relay") {
    niv::NestReceiver receiver;
    niv::SynchronizedRelaySharedMemoryAccess sender;

    WHEN("Data is sent and a receive is triggered") {
      sender.Send(testing::AnyNode());
      auto received = receiver.Receive();
      THEN("it is received correctly") {
        REQUIRE_THAT(received, Equals(testing::AnyNode()));
      }

      WHEN("an update is sent and a receive is triggered") {
        sender.Send(testing::Update());
        auto received = receiver.Receive();
        THEN("then the data has been updated") {
          REQUIRE_THAT(received, Equals(testing::UpdatedNode()));
        }
      }
    }
  }
}
