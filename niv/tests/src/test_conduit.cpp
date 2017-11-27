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

namespace conduit {

template <>
DataArray<uint64>::~DataArray();

}  // namespace conduit

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

namespace {

void SerializeConstRef(const conduit::Node& node, std::string* schema,
                       std::vector<conduit::uint8>* bytes) {
  conduit::Schema compact_schema;
  node.schema().compact_to(compact_schema);
  const std::string compact_schema_json(compact_schema.to_json());
  schema->assign(compact_schema_json.begin(), compact_schema_json.end());

  // intermediate vector not required in general, but our use case requires it
  std::vector<conduit::uint8> data;
  node.serialize(data);
  bytes->assign(data.begin(), data.end());
}

}  // namespace

SCENARIO("confirm that conduit issue #226 is not yet fixed", "[conduit]") {
  INFO(
      "This test's failing indicates that conduit issue #226 might have been "
      "fixed.\n"
      "Check https://github.com/LLNL/conduit/issues/226 \n"
      "Also adjust niv::NodeStorage::Store(...) and "
      "niv::NodeStorage::Update(...) \n"
      "so that they not do superfluous copying anymore.");
  GIVEN("a node that is serialized and read back") {
    std::string schema;
    std::vector<conduit::uint8> bytes;

    SerializeConstRef(testing::AnyNode(), &schema, &bytes);

    conduit::Node second_node;
    second_node.set_data_using_schema(conduit::Schema(schema), bytes.data());

    WHEN("the second node is serialized and read into a third node") {
      SerializeConstRef(second_node, &schema, &bytes);

      conduit::Node third_node;
      third_node.set_data_using_schema(conduit::Schema(schema), bytes.data());

      REQUIRE_FALSE(third_node.to_json() == testing::AnyNode().to_json());
    }
  }
}
