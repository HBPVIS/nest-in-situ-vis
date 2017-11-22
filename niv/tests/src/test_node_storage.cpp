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

#include "niv/node_storage.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("storing and reading a node", "[niv][niv::NodeStorage]") {
  GIVEN("a node storage") {
    niv::LocalNodeStorage storage;
    WHEN("a node is stored") {
      storage.Store(testing::AnyNode());
      THEN("it can be read") {
        REQUIRE_EQUAL_NODES(storage.Read(), testing::AnyNode());
      }
    }
  }
}

SCENARIO("a node can be stored and read multiple times",
         "[niv][niv::NodeStorage]") {
  GIVEN("a node stored and read back") {
    niv::LocalNodeStorage storage;
    storage.Store(testing::AnyNode());
    storage.Store(storage.Read());

    WHEN("the node is read") {
      conduit::Node read_node{storage.Read()};
      THEN("it is equal to the initial one") {
        REQUIRE_EQUAL_NODES(read_node, testing::AnyNode());
      }
    }
  }
}
