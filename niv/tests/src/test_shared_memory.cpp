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
  GIVEN("a conduit node, a shared memory segment and access") {
    conduit::Node any_node = testing::CreateAnyNode();
    niv::SharedMemorySegment shared_memory_segment;
    niv::SharedMemoryAccess shared_memory_access;

    WHEN("a node is stored in the shared memory segment") {
      shared_memory_segment.Store(any_node);

      THEN("it can be retrieved via access") {
        conduit::Node retrieved_node;
        shared_memory_access.Read(&retrieved_node);
        REQUIRE_EQUAL_NODES(retrieved_node, any_node);
      }

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node;
        shared_memory_access.Listen(&listening_node);
        WHEN("the first node is updated and stored again") {
          conduit::Node any_node = testing::CreateAnotherNode();
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

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node;
        shared_memory_segment.Listen(&listening_node);
        WHEN("the first node is updated and stored again") {
          conduit::Node any_node = testing::CreateAnotherNode();
          shared_memory_segment.Store(any_node);
          THEN("the result arrives at the listening node") {
            REQUIRE_EQUAL_NODES(listening_node, any_node);
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
    conduit::Node any_node = testing::CreateAnyNode();
    shared_memory_segment.Store(any_node);
    WHEN("when new data is stored in the segment") {
      conduit::Node new_data_node = testing::CreateNewDataNode();
      shared_memory_segment.Store(new_data_node);
      WHEN("that data is retrieved") {
        conduit::Node retrieved_node;
        shared_memory_access.Read(&retrieved_node);
        THEN("the retrieved data is equal to the stored one") {
          REQUIRE_EQUAL_NODES(retrieved_node, new_data_node);
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
  GIVEN(
      "a shared memory segment with a conduit node, and shared memory access") {
    niv::SharedMemorySegment segment;
    niv::SharedMemoryAccess segment_access;
    conduit::Node node = testing::CreateAnyNode();
    segment.Store(node);

    WHEN("the data in the shared memory is updated") {
      const conduit::Node update = testing::CreateNewDataNode();
      segment.Update(update);
      THEN("the  updated data can be retrieved from the segment") {
        conduit::Node node_with_update = node;
        node_with_update.update(update);
        conduit::Node retrieved_node;
        segment.Read(&retrieved_node);
        REQUIRE_EQUAL_NODES(retrieved_node, node_with_update);
      }
      THEN("the updated data can be retrieved from the segment access") {
        conduit::Node node_with_update = node;
        node_with_update.update(update);
        conduit::Node retrieved_node;
        segment_access.Read(&retrieved_node);
        REQUIRE_EQUAL_NODES(retrieved_node, node_with_update);
      }
    }
  }
}
