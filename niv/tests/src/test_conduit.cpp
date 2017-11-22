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

#include "conduit_node_helper.hpp"

SCENARIO("update inserts new nodes", "[conduit]") {
  GIVEN("A conduit tree") {
    conduit::Node a = testing::CreateAnyNode();

    WHEN("A second node updates the second") {
      conduit::Node b = testing::CreateNewDataNode();
      a.update(b);

      THEN("the first node contains also the content of the second") {
        REQUIRE_EQUAL_NODES(a, testing::CreateCombinedNode());
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
  GIVEN("a conduit node with some data") {
    conduit::Node node = testing::CreateAnyNode();
    WHEN("node is serialized") {
      std::string schema_string;
      std::vector<conduit::uint8> data;
      testing::Serialize(node, &schema_string, &data);
      WHEN("serialization is read into a second node") {
        conduit::Node second_node;
        second_node.set_data_using_schema(conduit::Schema(schema_string),
                                          data.data());
        THEN("they are identical") { REQUIRE_EQUAL_NODES(second_node, node); }

        WHEN("second node is serialized") {
          std::string second_schema_string;
          std::vector<conduit::uint8> second_data;
          testing::Serialize(second_node, &second_schema_string, &second_data);
          WHEN("serialization is read into a third node") {
            conduit::Node third_node;
            third_node.set_data_using_schema(
                conduit::Schema(second_schema_string), second_data.data());
            THEN("they are identical") {
              REQUIRE_EQUAL_NODES(third_node, node);
            }
          }
        }
      }
    }
  }
}

SCENARIO("node serialization works repeatedly including updates", "[conduit]") {
  GIVEN("a conduit node with some data") {
    conduit::Node node = testing::CreateAnyNode();
    WHEN("node is serialized") {
      std::string schema_string;
      std::vector<conduit::uint8> data;
      testing::Serialize(node, &schema_string, &data);
      WHEN("serialization is read into a second node") {
        conduit::Node second_node;
        second_node.set_data_using_schema(conduit::Schema(schema_string),
                                          data.data());
        THEN("they are identical") { REQUIRE_EQUAL_NODES(second_node, node); }

        WHEN("second node is updates") {
          conduit::Node update = testing::CreateNewDataNode();
          second_node.update(update);
          WHEN("updated second node is serialized") {
            std::string second_schema_string;
            std::vector<conduit::uint8> second_data;
            testing::Serialize(second_node, &second_schema_string,
                               &second_data);
            WHEN("serialization is read into a third node") {
              conduit::Node third_node;
              third_node.set_data_using_schema(
                  conduit::Schema(second_schema_string), second_data.data());
              THEN("they are identical") {
                conduit::Node node_including_update = node;
                node_including_update.update(update);
                REQUIRE_EQUAL_NODES(third_node, node_including_update);
              }
            }
          }
        }
      }
    }
  }
}
