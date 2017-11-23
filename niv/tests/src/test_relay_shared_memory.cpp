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

#include "niv/receiving_relay_shared_memory.hpp"
#include "niv/sending_relay_shared_memory.hpp"
#include "niv/shared_memory_access.hpp"
#include "niv/shared_memory_segment.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("Communicate a conduit node from shared mem segment to access",
         "[niv][nvi::RelaySharedMemory]") {
  GIVEN(
      "A conduit node with some data, a sending shared memory segment relay, a "
      "receiving shared memory access relay, and a receiving node") {
    niv::SendingRelaySharedMemory sending_relay{
        std::make_unique<niv::SharedMemorySegment>()};
    niv::ReceivingRelaySharedMemory receiving_relay{
        std::make_unique<niv::SharedMemoryAccess>()};
    conduit::Node receiving_node;

    WHEN("I send the data via the sending relay") {
      sending_relay.Send(testing::AnyNode());

      THEN("I receive the data on the receiving relay") {
        receiving_relay.Receive(&receiving_node);
        REQUIRE_EQUAL_NODES(receiving_node, testing::AnyNode());
      }

      WHEN("I change the values and send again") {
        sending_relay.Send(testing::AnotherNode());

        THEN("I receive the data on the receiving relay") {
          receiving_relay.Receive(&receiving_node);
          REQUIRE_EQUAL_NODES(receiving_node, testing::AnotherNode());
        }
      }

      WHEN("I listen to the data on the receiving relay") {
        receiving_relay.Listen(&receiving_node);
        THEN("I receive the data on the receiving relay") {
          REQUIRE_EQUAL_NODES(receiving_node, testing::AnyNode());
        }

        WHEN("I change the values and send again") {
          sending_relay.Send(testing::AnotherNode());

          THEN("I receive the data on the receiving relay") {
            REQUIRE_EQUAL_NODES(receiving_node, testing::AnotherNode());
          }
        }
      }
    }
  }
}

SCENARIO("Communicate a conduit node from shared mem access to segment",
         "[niv][nvi::RelaySharedMemory]") {
  GIVEN(
      "A conduit node with some data, a sending shared memory access relay, a "
      "receiving shared memory segment relay, and a receiving node") {
    niv::ReceivingRelaySharedMemory receiving_relay{
        std::make_unique<niv::SharedMemorySegment>()};
    conduit::Node receiving_node;
    niv::SendingRelaySharedMemory sending_relay{
        std::make_unique<niv::SharedMemoryAccess>()};

    WHEN("I send the data via the sending relay") {
      sending_relay.Send(testing::AnyNode());

      THEN("I receive the data on the receiving relay") {
        receiving_relay.Receive(&receiving_node);
        REQUIRE_EQUAL_NODES(receiving_node, testing::AnyNode());
      }

      WHEN("I change the values and send again") {
        sending_relay.Send(testing::AnotherNode());

        THEN("I receive the data on the receiving relay") {
          receiving_relay.Receive(&receiving_node);
          REQUIRE_EQUAL_NODES(receiving_node, testing::AnotherNode());
        }
      }

      WHEN("I listen to the data on the receiving relay") {
        receiving_relay.Listen(&receiving_node);
        THEN("I receive the data on the receiving relay") {
          REQUIRE_EQUAL_NODES(receiving_node, testing::AnyNode());
        }

        WHEN("I change the values and send again") {
          sending_relay.Send(testing::AnotherNode());

          THEN("I receive the data on the receiving relay") {
            REQUIRE_EQUAL_NODES(receiving_node, testing::AnotherNode());
          }
        }
      }
    }
  }
}
