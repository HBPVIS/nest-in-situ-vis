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

#include <cstddef>

#include <vector>

#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"

#include "conduit/conduit_core.hpp"

namespace niv {

class SharedMemory {
 public:
  using ManagedSharedMemory = boost::interprocess::managed_shared_memory;
  template <typename T>
  using Allocator =
      boost::interprocess::allocator<T, ManagedSharedMemory::segment_manager>;
  using DataVector = std::vector<conduit::uint8, Allocator<conduit::uint8>>;
  using SchemaString = std::vector<char, Allocator<char>>;

  static constexpr std::size_t kInitialSize{65536u};

  SharedMemory();
  ~SharedMemory();

  std::size_t GetFreeSize() const { return segment_.get_free_memory(); }
  DataVector& GetDataVector();
  SchemaString& GetSchemaString();

 private:
  ManagedSharedMemory segment_;
  DataVector* data_vector_;
  SchemaString* schema_string_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_SHARED_MEMORY_HPP_
