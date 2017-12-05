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
  NodeStorage() = delete;
  NodeStorage(SchemaStorage* schema_storage, DataStorage* data_storage)
      : schema_storage_{schema_storage}, data_storage_{data_storage} {}
  NodeStorage(const NodeStorage&) = default;
  NodeStorage(NodeStorage&&) = default;
  virtual ~NodeStorage() = default;

  void Store(const conduit::Node& node) {
    StoreSchema(node);
    StoreData(node);
  }

  void Update(const conduit::Node& node) {
    conduit::Node tmp{Read()};
    tmp.update(node);
    Store(tmp);
  }

  conduit::Node Read() {
    constexpr bool keep_listening = false;
    return ConstructNode(keep_listening);
  }

  conduit::Node Listen() {
    constexpr bool keep_listening = true;
    return ConstructNode(keep_listening);
  }

  void Clear() {
    schema_storage_->clear();
    data_storage_->clear();
  }

  bool IsEmpty() const {
    return schema_storage_->empty() && data_storage_->empty();
  }

  NodeStorage& operator=(const NodeStorage&) = default;
  NodeStorage& operator=(NodeStorage&&) = default;

 protected:
  SchemaStorage* GetSchemaStorage() { return schema_storage_; }
  DataStorage* GetDataStorage() { return data_storage_; }

 private:
  conduit::Node ConstructNode(bool keep_listening) {
    if (schema_storage_->empty()) {
      return conduit::Node();
    } else {
      return conduit::Node(GetSchema(), data_storage_->data(), keep_listening);
    }
  }

  std::string GetSchema() {
    return std::string(schema_storage_->begin(), schema_storage_->end());
  }
  void StoreSchema(const conduit::Node& node) {
    const std::string schema{CompactedSchemaJson(node)};
    schema_storage_->clear();
    schema_storage_->assign(schema.begin(), schema.end());
  }

  void StoreData(const conduit::Node& node) {
    const std::vector<conduit::uint8> data{Serialize(node)};
    data_storage_->clear();
    data_storage_->assign(data.begin(), data.end());
  }

  SchemaStorage* schema_storage_{nullptr};
  DataStorage* data_storage_{nullptr};
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_NODE_STORAGE_HPP_
