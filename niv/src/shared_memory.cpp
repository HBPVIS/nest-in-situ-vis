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

#include "niv/shared_memory.hpp"

#include <vector>

namespace niv {

template <>
SharedMemory<SharedMemoryCreate>::SharedMemory()
    : segment_{boost::interprocess::create_only, "niv-shared-memory",
               InitialSize()},
      data_vector_{segment_.construct<DataVector>("DataVector")(
          DataVector::allocator_type(segment_.get_segment_manager()))},
      schema_string_{segment_.construct<SchemaString>("SchemaString")(
          SchemaString::allocator_type(segment_.get_segment_manager()))} {}

template <>
SharedMemory<SharedMemoryAccess>::SharedMemory()
    : segment_{boost::interprocess::open_only, "niv-shared-memory"},
      data_vector_{segment_.find<DataVector>("DataVector").first},
      schema_string_{segment_.find<SchemaString>("SchemaString").first} {}

template <>
SharedMemory<SharedMemoryCreate>::~SharedMemory() {
  segment_.destroy<DataVector>("DataVector");
  segment_.destroy<SchemaString>("SchemaString");
  boost::interprocess::shared_memory_object::remove("niv-shared-memory");
}

template <>
SharedMemory<SharedMemoryAccess>::~SharedMemory() = default;

}  // namespace niv
