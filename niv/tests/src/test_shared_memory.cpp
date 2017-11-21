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

#include "conduit/conduit_node.hpp"

#include "niv/shared_memory_access.hpp"
#include "niv/shared_memory_segment.hpp"

namespace {

conduit::Node CreateAnyNode() {
  conduit::Node node;
  node["A/B/C"] = 3.1415;
  node["A/B/D"] = 4.124;
  node["A/E"] = 42.0;
  return node;
}

conduit::Node CreateAnotherNode() {
  conduit::Node node;
  node["A/B/C"] = 2.0 * 3.1415;
  node["A/B/D"] = 3.0 * 4.124;
  node["A/E"] = 4.0 * 42.0;
  return node;
}

void REQUIRE_EQUAL_NODES(const conduit::Node& actual,
                         const conduit::Node& expected) {
  REQUIRE(actual["A/B/C"].to_double() == Approx(expected["A/B/C"].to_double()));
  REQUIRE(actual["A/B/D"].to_double() == Approx(expected["A/B/D"].to_double()));
  REQUIRE(actual["A/E"].to_double() == Approx(expected["A/E"].to_double()));
}

}  // namespace

SCENARIO("storing and retrieving conduit nodes to/from shared memory",
         "[niv][niv:SharedMemory][niv:SharedMemorySegment][niv:"
         "SharedMemoryAccess]") {
  GIVEN("a conduit node, a shared memory segment and access") {
    conduit::Node any_node = ::CreateAnyNode();
    niv::SharedMemorySegment shared_memory_segment;
    niv::SharedMemoryAccess shared_memory_access;

    WHEN("a node is stored in the shared memory segment") {
      shared_memory_segment.Store(any_node);

      THEN("it can be retrieved from the segment") {
        conduit::Node retrieved_node;
        shared_memory_segment.Read(&retrieved_node);
        REQUIRE_EQUAL_NODES(retrieved_node, any_node);
      }
      THEN("it can be retrieved via access") {
        conduit::Node retrieved_node;
        shared_memory_access.Read(&retrieved_node);
        REQUIRE_EQUAL_NODES(retrieved_node, any_node);
      }

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node;
        shared_memory_access.Listen(&listening_node);
        WHEN("the first node is updated and stored again") {
          conduit::Node any_node = ::CreateAnotherNode();
          shared_memory_segment.Store(any_node);
          THEN("the result arrives at the listening node") {
            REQUIRE_EQUAL_NODES(listening_node, any_node);
          }
        }
      }
    }

    WHEN("a node is stored in the shared memory access") {
      shared_memory_access.Store(any_node);

      THEN("it can be retrieved from the segment") {
        conduit::Node retrieved_node;
        shared_memory_segment.Read(&retrieved_node);
        REQUIRE_EQUAL_NODES(retrieved_node, any_node);
      }
      THEN("it can be retrieved via access") {
        conduit::Node retrieved_node;
        shared_memory_access.Read(&retrieved_node);
        REQUIRE_EQUAL_NODES(retrieved_node, any_node);
      }

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node;
        shared_memory_segment.Listen(&listening_node);
        WHEN("the first node is updated and stored again") {
          conduit::Node any_node = ::CreateAnotherNode();
          shared_memory_segment.Store(any_node);
          THEN("the result arrives at the listening node") {
            REQUIRE_EQUAL_NODES(listening_node, any_node);
          }
        }
      }
    }
  }
}
