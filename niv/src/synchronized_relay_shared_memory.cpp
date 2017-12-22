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

#include "niv/synchronized_relay_shared_memory.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "conduit/conduit_core.hpp"
#include "conduit/conduit_schema.hpp"

#include "niv/shared_memory_access.hpp"
#include "niv/shared_memory_segment.hpp"
#include "niv/shared_memory_synchronization_access.hpp"
#include "niv/shared_memory_synchronization_object.hpp"

namespace niv {

SynchronizedRelaySharedMemory::SynchronizedRelaySharedMemory(
    const CreateSharedMemory&)
    : shared_memory_{std::make_unique<SharedMemorySegment>()},
      synchronization_{std::make_unique<SharedMemorySynchronizationObject>()} {}
SynchronizedRelaySharedMemory::SynchronizedRelaySharedMemory(
    const AccessSharedMemory&)
    : shared_memory_{std::make_unique<SharedMemoryAccess>()},
      synchronization_{std::make_unique<SharedMemorySynchronizationAccess>()} {}

void SynchronizedRelaySharedMemory::Send(const conduit::Node& node) {
  auto lock = synchronization_->ScopedLock();
  if (IsEmpty()) {
    shared_memory_->Store(node);
  } else {
    SendUpdate(node);
  }
}

void SynchronizedRelaySharedMemory::SendUpdate(const conduit::Node& node) {
  GetSharedMemory()->Update(node);
}

conduit::Node SynchronizedRelaySharedMemory::Receive() {
  auto lock = synchronization_->ScopedLock();
  auto received_data = shared_memory_->Read();
  GetSharedMemory()->Clear();
  return received_data;
}

bool SynchronizedRelaySharedMemory::IsEmpty() const {
  return GetSharedMemory()->IsEmpty();
}

}  // namespace niv
