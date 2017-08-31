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

constexpr std::size_t SharedMemory::kInitialSize;

SharedMemory::SharedMemory()
    : segment_{boost::interprocess::create_only, "niv-shared-memory",
               kInitialSize},
      allocator_{segment_.get_segment_manager()},
      data_vector_(segment_.construct<DataVector>("DataVector")(allocator_)) {}

SharedMemory::~SharedMemory() {
  segment_.destroy<DataVector>("DataVector");
  boost::interprocess::shared_memory_object::remove("niv-shared-memory");
}

SharedMemory::DataVector& SharedMemory::GetDataVector() {
  return *data_vector_;
}

}  // namespace niv
