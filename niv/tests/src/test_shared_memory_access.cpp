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

#include "niv/shared_memory_access.hpp"
#include "niv/shared_memory_segment.hpp"

SCENARIO("Shared memory access", "[niv][niv::SharedMemoryAccess]") {
  GIVEN("No shared memory segment") {
    THEN("Creating a shared memory access throws an exception.") {
      REQUIRE_THROWS_WITH([]() { niv::SharedMemoryAccess segment_access; }(),
                          "No such file or directory");
    }
  }

  GIVEN("A shared memory segment with some data in it") {
    niv::SharedMemorySegment segment;
    std::vector<conduit::uint8> some_data{1u, 2u, 3u};
    segment.Store(some_data);
    std::string some_schema{"foo bar"};
    segment.Store(some_schema);

    WHEN("I create shared memory access") {
      THEN("It does not throw an exception") {
        REQUIRE_NOTHROW([]() { niv::SharedMemoryAccess segment_access; }());
      }
      niv::SharedMemoryAccess segment_access;

      WHEN("I read the data from shared memory access") {
        auto read_data = segment_access.GetData();
        THEN("I get the original data") { REQUIRE(read_data == some_data); }
      }

      WHEN("I read the schema from shared memory access") {
        auto read_schema = segment_access.GetSchema();
        THEN("I get the original schema") {
          REQUIRE(read_schema == some_schema);
        }
      }
    }
  }
}
