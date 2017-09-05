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

#include "niv/shared_memory_segment.hpp"

SCENARIO("Shared memory creation", "[niv][niv::SharedMemorySegment]") {
  GIVEN("A shared memory segment") {
    niv::SharedMemorySegment segment;
    WHEN("I ask it for its free size") {
      auto free_size_after_creation = segment.GetFreeSize();
      THEN("it is > 0") { REQUIRE(free_size_after_creation > 0); }
    }

    WHEN("I retrieve data from the new segment") {
      auto retrieved_data = segment.GetData();
      THEN("it is empty") { REQUIRE(retrieved_data.size() == 0); }
    }

    WHEN("I store data in the segment") {
      std::vector<conduit::uint8> some_data{1u, 2u, 3u};
      auto free_size_before = segment.GetFreeSize();
      segment.Store(some_data);
      auto free_size_after = segment.GetFreeSize();
      THEN("we have less free space in the segment") {
        REQUIRE(free_size_after < free_size_before);
      }
      THEN("I can retrieve the data") {
        auto retrieved_data = segment.GetData();
        REQUIRE(retrieved_data == some_data);
      }
    }

    WHEN("I retrieve the schema from the new segment") {
      auto retrieved_schema = segment.GetSchema();
      THEN("it is empty") { REQUIRE(retrieved_schema.size() == 0); }
    }

    WHEN("I store a schema in the segment") {
      std::string some_schema{"foo bar"};
      auto free_size_before = segment.GetFreeSize();
      segment.Store(some_schema);
      auto free_size_after = segment.GetFreeSize();
      THEN("we have less free space in the segment") {
        REQUIRE(free_size_after < free_size_before);
      }
      THEN("I can retrieve it") {
        auto retrieved_schema = segment.GetSchema();
        REQUIRE(retrieved_schema == some_schema);
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
