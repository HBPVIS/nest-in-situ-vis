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

#include <memory>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "niv/conduit_receiver.hpp"
#include "niv/relay_shared_memory.hpp"
#include "niv/shared_memory_access.hpp"

SCENARIO("Conduit data is received by a conduit receiver",
         "[niv][niv::ConduitReceiver]") {
  GIVEN("A ConduitReceiver") {
    niv::ConduitReceiver receiver;

    WHEN("I send some data") {
      conduit::Node data;
      data["A"]["B"] = 17.0;
      data["A"]["C"] = 42.0;

      niv::RelaySharedMemory relay(std::make_unique<niv::SharedMemoryAccess>());
      relay.Send(data);

      THEN("I receive the data") {
        receiver.Start();
        REQUIRE(receiver.Get("A/B") == 17.0);
        REQUIRE(receiver.Get("A/C") == 42.0);
      }
    }
  }
}
