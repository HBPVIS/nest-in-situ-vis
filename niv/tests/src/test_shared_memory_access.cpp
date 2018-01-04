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

#include "niv/shared_memory.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("Shared memory access", "[niv][niv::SharedMemoryAccess]") {
  GIVEN("No shared memory segment") {
    THEN("Creating a shared memory access throws an exception.") {
      REQUIRE_THROWS_WITH(
          []() {
            niv::SharedMemory segment_access{niv::SharedMemory::Access()};
          }(),
          "No such file or directory");
    }
  }

  GIVEN("A shared memory segment") {
    niv::SharedMemory segment{niv::SharedMemory::Create()};

    WHEN("I create shared memory access") {
      THEN("It does not throw an exception") {
        REQUIRE_NOTHROW([]() {
          niv::SharedMemory segment_access{niv::SharedMemory::Access()};
        }());
      }
      niv::SharedMemory segment_access{niv::SharedMemory::Access()};

      WHEN("data is sotred in the shared memory access") {
        segment_access.Store(testing::AnyNode());

        THEN("it can be read") {
          REQUIRE_THAT(segment_access.Read(), Equals(testing::AnyNode()));
        }
      }
    }
    segment.Destroy();
  }
}
