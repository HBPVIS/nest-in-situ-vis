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

#ifndef NIV_INCLUDE_NIV_SHARED_MEMORY_SEGMENT_HPP_
#define NIV_INCLUDE_NIV_SHARED_MEMORY_SEGMENT_HPP_

#include <cstddef>

#include <vector>

#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"

#include "conduit/conduit_core.hpp"

#include "niv/shared_memory.hpp"

namespace niv {

class SharedMemorySegment : public SharedMemory {
 public:
  SharedMemorySegment();
  ~SharedMemorySegment();

 private:
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_SHARED_MEMORY_SEGMENT_HPP_
