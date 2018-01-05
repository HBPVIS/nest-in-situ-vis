//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017-2018 RWTH Aachen University, Germany,
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

#include <memory>
#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "niv/exchange/node_storage.hpp"

#include "conduit_node_helper.hpp"

namespace {

using NodeStorageBase =
    niv::exchange::NodeStorage<std::string, std::vector<conduit::uint8>>;

class NodeStorage : public NodeStorageBase {
 public:
  NodeStorage()
      : NodeStorageBase{new std::string, new std::vector<conduit::uint8>},
        owned_schema_storage_{GetSchemaStorage()},
        owned_data_storage_{GetDataStorage()} {}
  NodeStorage(const NodeStorage&) = delete;
  NodeStorage(NodeStorage&&) = default;
  ~NodeStorage() = default;

  NodeStorage& operator=(const NodeStorage&) = delete;
  NodeStorage& operator=(NodeStorage&&) = default;

 private:
  std::unique_ptr<std::string> owned_schema_storage_;
  std::unique_ptr<std::vector<conduit::uint8>> owned_data_storage_;
};

}  // namespace

SCENARIO("storing and reading a node", "[niv][niv::NodeStorage]") {
  GIVEN("a node storage") {
    ::NodeStorage storage;
    WHEN("a node is stored") {
      storage.Store(testing::AnyNode());
      THEN("it can be read") {
        REQUIRE_THAT(storage.Read(), Equals(testing::AnyNode()));
      }
    }
  }
}

SCENARIO("a node can be stored and read multiple times",
         "[niv][niv::NodeStorage]") {
  GIVEN("a node stored and read back") {
    ::NodeStorage storage;
    storage.Store(testing::AnyNode());
    storage.Store(storage.Read());

    WHEN("the node is read") {
      conduit::Node read_node{storage.Read()};
      THEN("it is equal to the initial one") {
        REQUIRE_THAT(read_node, Equals(testing::AnyNode()));
      }
    }
  }
}

SCENARIO("a node can be listening to changes", "[niv][niv::NodeStorage]") {
  GIVEN("a node listening to data") {
    ::NodeStorage storage;
    storage.Store(testing::AnyNode());
    conduit::Node listening_node{storage.Listen()};

    WHEN("stored data is changed") {
      storage.Store(testing::AnotherNode());
      THEN("the listening node gets the change") {
        REQUIRE_THAT(listening_node, Equals(testing::AnotherNode()));
      }
    }
  }
}
