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

#include "niv/node_storage.hpp"

namespace niv {

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
  SharedMemory(const SharedMemory&) = delete;
  SharedMemory(SharedMemory&&) = delete;
  virtual ~SharedMemory() = default;

  void Destroy();

  std::size_t GetFreeSize() const;

  void Store(const conduit::Node& node);
  void Update(const conduit::Node& node);
  void Read(conduit::Node* node);
  void Listen(conduit::Node* node);

  static constexpr const char* SegmentName() { return "niv-shared-memory"; }
  static constexpr const char* DataStorageName() { return "DataStorage"; }
  static constexpr const char* SchemaStorageName() { return "SchemaStorage"; }
  static constexpr std::size_t InitialSize() { return 65536u; }

  SharedMemory& operator=(const SharedMemory&) = delete;
  SharedMemory& operator=(SharedMemory&&) = delete;

 protected:
  explicit SharedMemory(const Create&);
  explicit SharedMemory(const Access&);

 private:
  ManagedSharedMemory segment_;
  NodeStorage<SchemaStorage, DataStorage> node_storage_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_SHARED_MEMORY_HPP_
