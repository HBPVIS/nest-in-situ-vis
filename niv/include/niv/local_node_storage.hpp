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

#ifndef NIV_INCLUDE_NIV_LOCAL_NODE_STORAGE_HPP_
#define NIV_INCLUDE_NIV_LOCAL_NODE_STORAGE_HPP_

#include <memory>
#include <string>
#include <vector>

#include "niv/node_storage.hpp"

namespace niv {

using NodeStorageBase = NodeStorage<std::string, std::vector<conduit::uint8>>;

class LocalNodeStorage : public NodeStorageBase {
 public:
  LocalNodeStorage()
      : NodeStorageBase{new std::string, new std::vector<conduit::uint8>},
        owned_schema_storage_{GetSchemaStorage()},
        owned_data_storage_{GetDataStorage()} {}
  LocalNodeStorage(const LocalNodeStorage&) = delete;
  LocalNodeStorage(LocalNodeStorage&&) = default;
  ~LocalNodeStorage() = default;

  LocalNodeStorage& operator=(const LocalNodeStorage&) = delete;
  LocalNodeStorage& operator=(LocalNodeStorage&&) = default;

 private:
  std::unique_ptr<std::string> owned_schema_storage_;
  std::unique_ptr<std::vector<conduit::uint8>> owned_data_storage_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_LOCAL_NODE_STORAGE_HPP_
