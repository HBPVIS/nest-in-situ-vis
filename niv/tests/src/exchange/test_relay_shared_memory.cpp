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

#include <memory>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "niv/exchange/relay_shared_memory.hpp"
#include "niv/exchange/shared_memory.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("Data gets transported", "[niv][niv::RelaySharedMemory]") {
  GIVEN("a simulation relay, and a visualization relay") {
    niv::exchange::RelaySharedMemory visualization_relay;
    niv::exchange::RelaySharedMemory simulation_relay;

    WHEN("a node is sent via the simulation relay") {
      simulation_relay.Send(testing::AnyNode());

      WHEN("data is received via the visualization relay") {
        conduit::Node received_node{visualization_relay.Receive()};

        THEN("received data matches original data") {
          REQUIRE_THAT(received_node, Equals(testing::AnyNode()));
        }
      }
    }
  }
}

SCENARIO("data in relay gets updated on sending update",
         "[niv][niv::RelaySharedMemory]") {
  GIVEN("a relay storing data") {
    niv::exchange::RelaySharedMemory simulation_relay;
    simulation_relay.Send(testing::AnyNode());

    WHEN("an update gets sent to the relay") {
      simulation_relay.Send(testing::Update());
      WHEN("the node is received from the relay") {
        conduit::Node received_node{simulation_relay.Receive()};
        THEN("the received node includes the update") {
          REQUIRE_THAT(received_node, Equals(testing::UpdatedNode()));
        }
      }
    }
  }
}

SCENARIO("Data in relay is cleared on receive",
         "[niv][niv::RelaySharedMemory]") {
  GIVEN("A synchronized relay with some data") {
    niv::exchange::RelaySharedMemory relay;
    relay.Send(testing::AnyNode());

    WHEN("Data is received") {
      auto node{relay.Receive()};
      THEN("the node is not empty") { REQUIRE_FALSE(node.dtype().is_empty()); }

      WHEN("data is read a second time") {
        auto node2{relay.Receive()};
        THEN("the node is empty") { REQUIRE(node2.dtype().is_empty()); }
      }
    }
  }
}

SCENARIO("Relay's emptyness is passed throug shared memory",
         "[niv][niv::RelaySharedMemory]") {
  GIVEN("a pair of relays") {
    niv::exchange::RelaySharedMemory relay_segment;
    niv::exchange::RelaySharedMemory relay_access;

    THEN("both relays are empty") {
      REQUIRE(relay_segment.IsEmpty());
      REQUIRE(relay_access.IsEmpty());
    }

    WHEN("Data is sent") {
      relay_segment.Send(testing::AnyNode());
      THEN("both relays are not empty.") {
        REQUIRE_FALSE(relay_segment.IsEmpty());
        REQUIRE_FALSE(relay_access.IsEmpty());
      }

      WHEN("Data is received") {
        relay_access.Receive();
        THEN("both relays are empty again.") {
          REQUIRE(relay_segment.IsEmpty());
          REQUIRE(relay_access.IsEmpty());
        }
      }
    }
  }
}

SCENARIO("ordered destruction of relays is properly reflectes by shared memory",
         "[niv][niv::RelaySharedMemory]") {
  GIVEN("no relay") {
    THEN("accessing shared throws an exception") {
      REQUIRE_THROWS_WITH(
          niv::exchange::SharedMemory(niv::exchange::SharedMemory::Access()),
          "No such file or directory");
    }
  }

  GIVEN("a relay in a new scope") {
    {  // new scope
      niv::exchange::RelaySharedMemory relay;
      THEN("accessing shared memory does not throw") {
        REQUIRE_NOTHROW(
            niv::exchange::SharedMemory(niv::exchange::SharedMemory::Access()));
      }

      THEN("creating a second relay does not throw") {
        REQUIRE_NOTHROW(niv::exchange::RelaySharedMemory());
      }

      WHEN("a second relay gets out of scope") {
        {  // new scope
          niv::exchange::RelaySharedMemory relay2;
        }
        THEN("accessing shared memory does not throw") {
          REQUIRE_NOTHROW(niv::exchange::SharedMemory(
              niv::exchange::SharedMemory::Access()));
        }
      }
    }

    WHEN("the first relay is out of scope") {
      THEN("accessing shared memory throws an exception") {
        REQUIRE_THROWS_WITH(
            niv::exchange::SharedMemory(niv::exchange::SharedMemory::Access()),
            "No such file or directory");
      }
    }
  }
}

SCENARIO(
    "unorderd destruction of relays is properly reflected by shared memory",
    "[niv][niv::RelaySharedMemory]") {
  GIVEN("two relays") {
    auto relay1 = std::make_unique<niv::exchange::RelaySharedMemory>();
    auto relay2 = std::make_unique<niv::exchange::RelaySharedMemory>();

    WHEN("deleting the first relay") {
      relay1.reset();
      THEN("accessing shared memory does not throw") {
        REQUIRE_NOTHROW(
            niv::exchange::SharedMemory(niv::exchange::SharedMemory::Access()));
      }

      WHEN("deleting the second relay") {
        relay2.reset();
        THEN("accessing shared memory throws an exception") {
          REQUIRE_THROWS_WITH(niv::exchange::SharedMemory(
                                  niv::exchange::SharedMemory::Access()),
                              "No such file or directory");
        }
      }
    }
  }
}
