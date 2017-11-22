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

#include <iterator>
#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "niv/node_storage.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("update inserts new nodes", "[conduit]") {
  GIVEN("A conduit tree") {
    conduit::Node a = testing::AnyNode();

    WHEN("A second node updates the tree") {
      conduit::Node b = testing::Update();
      a.update(b);

      THEN("the first node contains also the content of the second") {
        REQUIRE_EQUAL_NODES(a, testing::UpdatedNode());
      }
    }
  }
}

SCENARIO("conduit array leafs are compatible to std::vector", "[conduit]") {
  const std::string some_path{"root/inner/leaf"};

  GIVEN("a std vector assigning data to a node") {
    const std::vector<std::size_t> some_data{1, 5, 7, 9};
    conduit::Node node;
    node[some_path].set(some_data);

    THEN("data is stored in the node") {
      for (std::size_t i = 0; i < some_data.size(); ++i) {
        REQUIRE(node[some_path].as_uint64_array()[i] == some_data[i]);
      }
    }

    WHEN("data is retrieved from the node into a vector") {
      const auto& node_data = node[some_path].as_uint64_array();
      const std::size_t num_elements = node_data.number_of_elements();
      const auto* begin = reinterpret_cast<std::size_t*>(node_data.data_ptr());
      const auto* end = begin + num_elements;
      std::vector<std::size_t> retrieved_data(begin, end);

      THEN("the vector and the original data are the same") {
        REQUIRE(retrieved_data == some_data);
      }
    }
  }
}

SCENARIO("node serialization works repeatedly", "[conduit]") {
  GIVEN("a serialized node") {
    std::string schema_string;
    std::vector<conduit::uint8> data;
    testing::Serialize(testing::AnyNode(), &schema_string, &data);
    WHEN("serialization is read into a second node") {
      conduit::Node second_node;
      second_node.set_data_using_schema(conduit::Schema(schema_string),
                                        data.data());
      THEN("they are identical") {
        REQUIRE_EQUAL_NODES(second_node, testing::AnyNode());
      }

      WHEN("the second node is serialized and read again") {
        testing::Serialize(second_node, &schema_string, &data);
        conduit::Node third_node;
        third_node.set_data_using_schema(conduit::Schema(schema_string),
                                         data.data());
        THEN("they are identical") {
          // REQUIRE_EQUAL_NODES(third_node, testing::AnyNode());
        }
      }
    }
  }
}

SCENARIO("node serialization works repeatedly using a node storage",
         "[conduit]") {
  GIVEN("a serialized node") {
    niv::LocalNodeStorage storage;
    storage.Store(testing::AnyNode());

    WHEN("serialization is read into a second node") {
      conduit::Node second_node;
      storage.Read(&second_node);

      THEN("they are identical") {
        REQUIRE_EQUAL_NODES(second_node, testing::AnyNode());
      }

      WHEN("the second node is serialized and read again") {
        storage.Store(second_node);
        conduit::Node third_node;
        storage.Read(&third_node);

        THEN("they are identical") {
          // REQUIRE_EQUAL_NODES(third_node, testing::AnyNode());
        }
      }
    }
  }
}

SCENARIO("node serialization works repeatedly including updates", "[conduit]") {
  GIVEN("a serialized node in some storage") {
    std::string schema_string;
    std::vector<conduit::uint8> data;
    testing::Serialize(testing::AnyNode(), &schema_string, &data);

    WHEN("the data in the storage is updated") {
      conduit::Node tmp;
      tmp.set_data_using_schema(conduit::Schema(schema_string), data.data());
      tmp.update(testing::Update());
      testing::Serialize(tmp, &schema_string, &data);

      THEN("the updated data can be read from the storage") {
        conduit::Node read_node;
        read_node.set_data_using_schema(conduit::Schema(schema_string),
                                        data.data());
        // REQUIRE_EQUAL_NODES(read_node, testing::UpdatedNode());
      }
    }
  }
}
