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

#include "conduit_node_helper.hpp"

SCENARIO("storing and retrieving conduit nodes to/from shared memory",
         "[niv][niv:SharedMemory][niv:SharedMemorySegment][niv:"
         "SharedMemoryAccess]") {
  GIVEN("a shared memory segment and access") {
    niv::SharedMemorySegment shared_memory_segment;
    niv::SharedMemoryAccess shared_memory_access;

    WHEN("a node is stored in the shared memory segment") {
      shared_memory_segment.Store(testing::AnyNode());

      THEN("it can be read via access") {
        REQUIRE_EQUAL_NODES(shared_memory_access.Read(), testing::AnyNode());
      }

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node{shared_memory_access.Listen()};
        WHEN("the first node is updated and stored again") {
          shared_memory_segment.Store(testing::AnotherNode());
          THEN("the result arrives at the listening node") {
            REQUIRE_EQUAL_NODES(listening_node, testing::AnotherNode());
          }
        }
      }
    }

    WHEN("a node is stored in the shared memory access") {
      shared_memory_access.Store(testing::AnyNode());

      THEN("it can be read from the segment") {
        REQUIRE_EQUAL_NODES(shared_memory_segment.Read(), testing::AnyNode());
      }

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node{shared_memory_segment.Listen()};
        WHEN("the first node is updated and stored again") {
          shared_memory_segment.Store(testing::AnotherNode());
          THEN("the result arrives at the listening node") {
            REQUIRE_EQUAL_NODES(listening_node, testing::AnotherNode());
          }
        }
      }
    }
  }
}

SCENARIO("Overwriting data in shared memory",
         "[niv][niv::SharedMemory][niv::SharedMemorySegment][niv::"
         "SharedMemoryAccess") {
  GIVEN("A shared memory segment + access, with some data in it") {
    niv::SharedMemorySegment shared_memory_segment;
    niv::SharedMemoryAccess shared_memory_access;
    shared_memory_segment.Store(testing::AnyNode());
    WHEN("when new data is stored in the segment") {
      shared_memory_segment.Store(testing::ADifferentNode());
      WHEN("that data is read") {
        conduit::Node read_node{shared_memory_access.Read()};
        THEN("the read data is equal to the stored one") {
          REQUIRE_EQUAL_NODES(read_node, testing::ADifferentNode());
        }
      }
    }
  }
}

SCENARIO("data can be updated in shared memory",
         "[niv][niv::SharedMemory][niv::SharedMemorySegment][niv::"
         "SharedMemoryAccess") {
  std::cout << "SCENARIO(\"data can be updated in shared memory\")"
            << std::endl;
  GIVEN("a shared memory segment with data in it, and shared memory access") {
    niv::SharedMemorySegment segment;
    niv::SharedMemoryAccess segment_access;
    segment.Store(testing::AnyNode());

    WHEN("the data in the shared memory is updated") {
      segment.Update(testing::Update());
      THEN("the  updated data can be read from the segment") {
        REQUIRE_EQUAL_NODES(segment.Read(), testing::UpdatedNode());
      }
      THEN("the updated data can be read from the segment access") {
        REQUIRE_EQUAL_NODES(segment.Read(), testing::UpdatedNode());
      }
    }
  }
}
