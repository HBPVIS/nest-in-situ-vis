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

#ifndef NIV_TESTS_SRC_CONDUIT_NODE_HELPER_HPP_
#define NIV_TESTS_SRC_CONDUIT_NODE_HELPER_HPP_

#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

namespace testing {

conduit::Node CreateAnyNode() {
  conduit::Node node;
  node["A/B/C"] = 3.1415;
  node["A/B/D"] = 4.124;
  node["A/E"] = 42.0;
  return node;
}

conduit::Node CreateAnotherNode() {
  conduit::Node node;
  node["A/B/C"] = 2.0 * 3.1415;
  node["A/B/D"] = 3.0 * 4.124;
  node["A/E"] = 4.0 * 42.0;
  return node;
}

conduit::Node CreateNewDataNode() {
  conduit::Node node;
  node["A/B/F"] = 2.0 * 3.1415;
  node["A/B/G"] = 3.0 * 4.124;
  node["A/H"] = 4.0 * 42.0;
  return node;
}

conduit::Node CreateCombinedNode() {
  conduit::Node node;
  node["A/B/C"] = 3.1415;
  node["A/B/D"] = 4.124;
  node["A/E"] = 42.0;
  node["A/B/F"] = 2.0 * 3.1415;
  node["A/B/G"] = 3.0 * 4.124;
  node["A/H"] = 4.0 * 42.0;
  return node;
}

#define REQUIRE_EQUAL_NODES(a, b) REQUIRE(a.to_json() == b.to_json())

void Serialize(const conduit::Node node, std::string* schema_string,
               std::vector<conduit::uint8>* data) {
  conduit::Schema schema;
  node.schema().compact_to(schema);
  const std::string schema_json{schema.to_json()};

  schema_string->clear();
  schema_string->assign(schema_json.begin(), schema_json.end());

  std::vector<conduit::uint8> serialized_data;
  node.serialize(serialized_data);
  data->clear();
  data->assign(serialized_data.begin(), serialized_data.end());
}

}  // namespace testing

#endif  // NIV_TESTS_SRC_CONDUIT_NODE_HELPER_HPP_
