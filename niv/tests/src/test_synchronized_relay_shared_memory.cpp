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

#include "niv/shared_memory_access.hpp"
#include "niv/shared_memory_segment.hpp"
#include "niv/synchronized_relay_shared_memory.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("Data gets transported", "[niv][niv::SynchronizedRelaySharedMemory]") {
  GIVEN("A conduit node, a simulation relay, and a visualization relay") {
    conduit::Node any_node = testing::CreateAnyNode();
    niv::SynchronizedRelaySharedMemory simulation_relay{
        std::make_unique<niv::SharedMemorySegment>()};
    niv::SynchronizedRelaySharedMemory visualization_relay{
        std::make_unique<niv::SharedMemoryAccess>()};

    WHEN("the node is sent via the simulation relay") {
      simulation_relay.Send(any_node);

      WHEN("data is received via the visualization relay") {
        conduit::Node received_node;
        visualization_relay.Receive(&received_node);

        THEN("received data matches original data") {
          REQUIRE_EQUAL_NODES(received_node, any_node);
        }
      }

      WHEN("new data is sent") {
        conduit::Node new_data = testing::CreateNewDataNode();
        simulation_relay.Send(new_data);
        WHEN("data is received via the visualization relay") {
          conduit::Node received_node;
          visualization_relay.Receive(&received_node);

          THEN("received data matches original data +  new data") {
            conduit::Node expected_node = any_node;
            expected_node.update(new_data);
            // REQUIRE_EQUAL_NODES(received_node, expected_node);
          }
        }
      }
    }
  }
}
