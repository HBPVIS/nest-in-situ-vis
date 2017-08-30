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

#include "niv/shared_memory.hpp"

SCENARIO("Shared memory", "[niv][niv::SharedMemory]") {
  GIVEN("A shared memory segment") {
    niv::SharedMemory segment;
    WHEN("I ask it for its free size") {
      auto free_size_after_creation = segment.GetFreeSize();
      THEN("it is > 0") { REQUIRE(free_size_after_creation > 0); }
    }

    WHEN("I request a data vector in that shared memory segment") {
      auto data_vector = segment.GetDataVector();
      THEN("it is empty") { REQUIRE(data_vector.size() == 0); }

      WHEN("I add one data entry into the vector") {
        auto free_size_before_push = segment.GetFreeSize();
        data_vector.push_back(conduit::uint8{9u});
        auto free_size_after_push = segment.GetFreeSize();
        THEN("I can retrieve it") {
          REQUIRE(data_vector[0] == conduit::uint8{9u});
        }
        THEN("we have less free space in the segment") {
          REQUIRE(free_size_after_push < free_size_before_push);
        }
      }
    }
  }
}
