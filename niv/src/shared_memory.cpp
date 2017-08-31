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

#include <utility>

namespace niv {

SharedMemory::SharedMemory(ManagedSharedMemory&& segment)
    : segment_{std::move(segment)} {}

std::size_t SharedMemory::GetFreeSize() const {
  return segment_.get_free_memory();
}
SharedMemory::DataVector& SharedMemory::GetDataVector() {
  return *data_vector_;
}
SharedMemory::SchemaString& SharedMemory::GetSchemaString() {
  return *schema_string_;
}

}  // namespace niv
