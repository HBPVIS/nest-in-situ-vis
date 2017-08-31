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

#include "catch/catch.hpp"

#include "niv/shared_memory.hpp"

SCENARIO("Shared memory", "[niv][niv::SharedMemory]") {
  GIVEN("A shared memory segment") {
    niv::SharedMemory segment;
    WHEN("I ask it for its free size") {
      auto free_size_after_creation = segment.GetFreeSize();
      THEN("it is > 0") { REQUIRE(free_size_after_creation > 0); }
    }

    WHEN("I request a data vector in that shared memory segment") {
      auto data = segment.GetDataVector();
      THEN("it is empty") { REQUIRE(data.size() == 0); }

      WHEN("I add one data entry into the vector") {
        auto free_size_before_push = segment.GetFreeSize();
        data.push_back(conduit::uint8{9u});
        auto free_size_after_push = segment.GetFreeSize();
        THEN("I can retrieve it") { REQUIRE(data[0] == conduit::uint8{9u}); }
        THEN("we have less free space in the segment") {
          REQUIRE(free_size_after_push < free_size_before_push);
        }
      }
    }

    WHEN("I request a schema string in that shared memory segment") {
      auto schema = segment.GetSchemaString();
      THEN("it is empty") { REQUIRE(schema.size() == 0); }

      WHEN("I assign a string to the schema") {
        const std::string any_string{"foo_bar"};
        auto free_size_before_assign = segment.GetFreeSize();
        schema.assign(any_string.begin(), any_string.end());
        auto free_size_after_assign = segment.GetFreeSize();
        THEN("schema holds the string") {
          const std::string schema_as_string{schema.begin(), schema.end()};
          REQUIRE(schema_as_string == any_string);
        }
        THEN("we have less free space in the segment") {
          REQUIRE(free_size_after_assign < free_size_before_assign);
        }
      }
    }
  }
}
