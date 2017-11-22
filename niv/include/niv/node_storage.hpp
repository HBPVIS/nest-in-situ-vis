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

#ifndef NIV_INCLUDE_NIV_NODE_STORAGE_HPP_
#define NIV_INCLUDE_NIV_NODE_STORAGE_HPP_

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

namespace niv {

std::string CompactedSchemaJson(const conduit::Node& node);
std::vector<conduit::uint8> Serialize(const conduit::Node& node);

template <typename SchemaStorage, typename DataStorage>
class NodeStorage {
 public:
  void Store(const conduit::Node& node) {
    StoreSchema(node);
    StoreData(node);
  }
  void Read(conduit::Node* node) {
    node->set_data_using_schema(conduit::Schema(schema_storage_),
                                data_storage_.data());
  }

 private:
  void StoreSchema(const conduit::Node& node) {
    const std::string schema{CompactedSchemaJson(node)};
    schema_storage_.clear();
    schema_storage_.assign(schema.begin(), schema.end());
  }

  void StoreData(const conduit::Node& node) {
    const std::vector<conduit::uint8> data{Serialize(node)};
    data_storage_.clear();
    data_storage_.assign(data.begin(), data.end());
  }

  SchemaStorage schema_storage_;
  DataStorage data_storage_;
};

using LocalNodeStorage = NodeStorage<std::string, std::vector<conduit::uint8>>;

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_NODE_STORAGE_HPP_
