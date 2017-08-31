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
#include "niv/shared_memory_access.hpp"

SCENARIO("Shared memory access", "[niv][niv::SharedMemoryAccess]") {
  GIVEN("A shared memory segment with some data in it") {
    niv::SharedMemory segment;
    auto data = segment.GetDataVector();
    data.push_back(conduit::uint8{9u});
    auto schema = segment.GetSchemaString();
    const std::string any_string{"foo_bar"};
    schema.assign(any_string.begin(), any_string.end());

    WHEN("I request a second shared memory segment for accessing the first") {
      THEN("It does not throw an exception") {
        REQUIRE_NOTHROW([]() { niv::SharedMemoryAccess segment2; }());
      }
    }
  }
}
