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

#ifndef NIV_INCLUDE_NIV_EXCHANGE_SHARED_MEMORY_HPP_
#define NIV_INCLUDE_NIV_EXCHANGE_SHARED_MEMORY_HPP_

#include <memory>
#include <string>
#include <utility>
#include <vector>

SUPPRESS_WARNINGS_BEGIN
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
SUPPRESS_WARNINGS_END

#include "conduit/conduit_core.hpp"
#include "conduit/conduit_node.hpp"

#include "niv/exchange/node_storage.hpp"

namespace niv {
namespace exchange {

class SharedMemory {
 public:
  class Create {};
  class Access {};

  using ManagedSharedMemory = boost::interprocess::managed_shared_memory;
  using SegmentManager = ManagedSharedMemory::segment_manager;
  template <typename T>
  using Allocator = boost::interprocess::allocator<T, SegmentManager>;
  using DataStorage = std::vector<conduit::uint8, Allocator<conduit::uint8>>;
  using SchemaStorage = std::vector<char, Allocator<char>>;

  SharedMemory() = delete;
  explicit SharedMemory(const Create&);
  explicit SharedMemory(const Access&);
  SharedMemory(const SharedMemory&) = delete;
  SharedMemory(SharedMemory&&) = delete;
  virtual ~SharedMemory();

  void Destroy();

  std::size_t GetFreeSize() const;

  void Store(const conduit::Node& node);
  void Update(const conduit::Node& node);
  conduit::Node Read();
  conduit::Node Listen();

  void Clear();
  bool IsEmpty() const;

  static constexpr const char* SegmentName() { return "niv-shared-memory"; }
  static constexpr const char* DataStorageName() { return "DataStorage"; }
  static constexpr const char* SchemaStorageName() { return "SchemaStorage"; }
  static constexpr const char* ReferenceCountName() { return "ReferenceCount"; }

  static constexpr std::size_t InitialSize() { return 1073741824u; }

  SharedMemory& operator=(const SharedMemory&) = delete;
  SharedMemory& operator=(SharedMemory&&) = delete;

  int GetReferenceCount() const;

 private:
  SchemaStorage* ConstructSchemaStorage();
  DataStorage* ConstructDataStorage();
  int* ConstructReferenceCount();

  SchemaStorage* FindSchemaStorage();
  DataStorage* FindDataStorage();
  int* FindReferenceCount();

  ManagedSharedMemory segment_;
  NodeStorage<SchemaStorage, DataStorage> node_storage_;
  int* reference_count_;
};

}  // namespace exchange
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_EXCHANGE_SHARED_MEMORY_HPP_
