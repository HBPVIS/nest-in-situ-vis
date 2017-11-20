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

namespace {

conduit::Node CreateAnyNode() {
  conduit::Node node;
  node["A/B/C"] = 3.1415;
  node["A/B/D"] = 4.124;
  node["A/D"] = 42.0;
  return node;
}

void REQUIRE_EQUAL_NODES(const conduit::Node& actual,
                         const conduit::Node& expected) {
  REQUIRE(actual["A/B/C"].to_double() == Approx(expected["A/B/C"].to_double()));
  REQUIRE(actual["A/B/D"].to_double() == Approx(expected["A/B/D"].to_double()));
  REQUIRE(actual["A/D"].to_double() == Approx(expected["A/D"].to_double()));
}

}  // namespace

SCENARIO("Data gets transported", "[niv][niv::SynchronizedRelaySharedMemory]") {
  GIVEN("A conduit node, a simulation relay, and a visualization relay") {
    conduit::Node any_node = CreateAnyNode();
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
    }
  }
}
