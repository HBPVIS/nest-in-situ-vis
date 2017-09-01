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

namespace {
conduit::Node AnyNode() {
  conduit::Node node;
  node["A"]["B"]["E"] = 1.1;
  node["A"]["C"]["F"] = 2.1;
  node["A"]["C"]["G"] = 2.2;
  node["A"]["D"]["H"] = 3.1;
  node["A"]["D"]["I"] = 3.2;
  node["A"]["D"]["J"] = 3.3;
  return node;
}

void REQUIRE_EQ(const conduit::Node left, const conduit::Node right) {
  REQUIRE(left["A"]["B"]["E"].as_double() == right["A"]["B"]["E"].as_double());
  REQUIRE(left["A"]["C"]["F"].as_double() == right["A"]["C"]["F"].as_double());
  REQUIRE(left["A"]["C"]["G"].as_double() == left["A"]["C"]["G"].as_double());
  REQUIRE(left["A"]["D"]["H"].as_double() == right["A"]["D"]["H"].as_double());
  REQUIRE(left["A"]["D"]["I"].as_double() == right["A"]["D"]["I"].as_double());
  REQUIRE(left["A"]["D"]["J"].as_double() == right["A"]["D"]["J"].as_double());
}

conduit::Node& AnyLeaf(conduit::Node* node) { return (*node)["A"]["D"]["H"]; }

constexpr double kAnyOtherValue{42.0f};

}  // namespace

SCENARIO("Communicate a conduit node", "[niv][nvi::RelaySharedMemory]") {
  GIVEN(
      "A conduit node with some data, a sending shared memory relay, and a "
      "reveiving node") {
    conduit::Node any_node{::AnyNode()};

    niv::SendingRelaySharedMemory sending_relay{
        std::make_unique<niv::SharedMemorySegment>()};

    conduit::Node receiving_node;

    GIVEN("a receiving shared memory relay") {
      niv::ReceivingRelaySharedMemory receiving_relay{
          std::make_unique<niv::SharedMemoryAccess>()};

      WHEN("I send the data via the sending relay") {
        sending_relay.Send(any_node);

        THEN("I receive the data on the receiving relay") {
          receiving_relay.Receive(&receiving_node);
          REQUIRE_EQ(receiving_node, any_node);
        }

        WHEN("I change one value and send again") {
          ::AnyLeaf(&any_node) = ::kAnyOtherValue;
          sending_relay.Send(any_node);

          THEN("I receive the data on the receiving relay") {
            receiving_relay.Receive(&receiving_node);
            REQUIRE_EQ(receiving_node, any_node);
          }
        }
      }
    }
  }
}
