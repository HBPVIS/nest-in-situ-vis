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

#ifndef NIV_INCLUDE_NIV_SYNCHRONIZED_RELAY_SHARED_MEMORY_SEGMENT_HPP_
#define NIV_INCLUDE_NIV_SYNCHRONIZED_RELAY_SHARED_MEMORY_SEGMENT_HPP_

#include "niv/synchronized_relay_shared_memory.hpp"

namespace niv {

class SynchronizedRelaySharedMemorySegment
    : public SynchronizedRelaySharedMemory {
 public:
  SynchronizedRelaySharedMemorySegment()
      : SynchronizedRelaySharedMemory{
            niv::SynchronizedRelaySharedMemory::CreateSharedMemory()} {}
  SynchronizedRelaySharedMemorySegment(
      const SynchronizedRelaySharedMemorySegment&) = delete;
  SynchronizedRelaySharedMemorySegment(SynchronizedRelaySharedMemorySegment&&) =
      delete;
  ~SynchronizedRelaySharedMemorySegment() = default;

  SynchronizedRelaySharedMemorySegment& operator=(
      const SynchronizedRelaySharedMemorySegment&) = delete;
  SynchronizedRelaySharedMemorySegment& operator=(
      SynchronizedRelaySharedMemorySegment&&) = delete;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_SYNCHRONIZED_RELAY_SHARED_MEMORY_SEGMENT_HPP_
