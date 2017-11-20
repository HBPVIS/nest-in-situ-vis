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

#ifndef NIV_INCLUDE_NIV_SHARED_MEMORY_HPP_
#define NIV_INCLUDE_NIV_SHARED_MEMORY_HPP_

#include <string>
#include <utility>
#include <vector>

#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"

#include "conduit/conduit_core.hpp"
#include "conduit/conduit_node.hpp"

namespace niv {

class SharedMemory {
 public:
  class Create {};
  class Access {};

  using ManagedSharedMemory = boost::interprocess::managed_shared_memory;
  using SegmentManager = ManagedSharedMemory::segment_manager;
  template <typename T>
  using Allocator = boost::interprocess::allocator<T, SegmentManager>;
  using DataVector = std::vector<conduit::uint8, Allocator<conduit::uint8>>;
  using SchemaString = std::vector<char, Allocator<char>>;

  explicit SharedMemory(const Create&);
  explicit SharedMemory(const Access&);
  virtual ~SharedMemory() = default;

  void Destroy();

  std::size_t GetFreeSize() const;

  void Store(const conduit::Node& node);
  void Store(const std::vector<conduit::uint8>& data);
  void Store(const std::string& schema);
  std::vector<conduit::uint8> GetData() const;
  conduit::uint8* GetRawData() const;
  std::string GetSchema() const;

  void Read(conduit::Node* node);

  static constexpr const char* SegmentName() { return "niv-shared-memory"; }
  static constexpr const char* DataVectorName() { return "DataVector"; }
  static constexpr const char* SchemaStringName() { return "SchemaString"; }
  static constexpr std::size_t InitialSize() { return 65536u; }

 protected:
  ManagedSharedMemory segment_;
  DataVector* data_vector_{nullptr};
  SchemaString* schema_string_{nullptr};

 private:
  void StoreSchema(const conduit::Node& node);
  void StoreData(const conduit::Node& node);
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_SHARED_MEMORY_HPP_
