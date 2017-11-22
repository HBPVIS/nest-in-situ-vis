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

#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "niv/shared_memory_segment.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("Shared memory creation", "[niv][niv::SharedMemorySegment]") {
  GIVEN("A shared memory segment") {
    niv::SharedMemorySegment segment;
    WHEN("I ask it for its free size") {
      auto free_size_after_creation = segment.GetFreeSize();
      THEN("it is > 0") { REQUIRE(free_size_after_creation > 0); }
    }

    WHEN("I read data from the new segment") {
      conduit::Node node;
      segment.Read(&node);
      THEN("it is empty") { REQUIRE(node.dtype().is_empty()); }
    }

    WHEN("I store data in the segment") {
      auto free_size_before = segment.GetFreeSize();
      segment.Store(testing::AnyNode());
      auto free_size_after = segment.GetFreeSize();
      THEN("we have less free space in the segment") {
        REQUIRE(free_size_after < free_size_before);
      }
      THEN("I can read the data") {
        conduit::Node read_node;
        segment.Read(&read_node);
        REQUIRE_EQUAL_NODES(read_node, testing::AnyNode());
      }
    }

    WHEN("I request a second shared memory segment") {
      THEN("It throws an exception") {
        REQUIRE_THROWS_WITH([]() { niv::SharedMemorySegment segment2; }(),
                            "File exists");
      }
    }
  }
}

SCENARIO("write updated node to shared memory segment",
         "[niv][niv::SharedMemorySegment]") {
  GIVEN("a shared memory segment with some data") {
    niv::SharedMemorySegment segment;
    segment.Store(testing::AnyNode());
    WHEN("a larger node is stored") {
      segment.Store(testing::UpdatedNode());
      WHEN("the node is read") {
        conduit::Node read_node;
        segment.Read(&read_node);
        THEN("the content is equal to the written one") {
          REQUIRE_EQUAL_NODES(read_node, testing::UpdatedNode());
        }
      }
    }
  }
}
