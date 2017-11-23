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

#include "niv/sending_relay_shared_memory.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "conduit/conduit_node.hpp"
#include "conduit/conduit_schema.hpp"

namespace niv {
SendingRelaySharedMemory::SendingRelaySharedMemory(SharedMemory* shared_memory)
    : SendingRelaySharedMemory(std::unique_ptr<SharedMemory>(shared_memory)) {}

SendingRelaySharedMemory::SendingRelaySharedMemory(
    std::unique_ptr<SharedMemory> shared_memory)
    : RelaySharedMemory{std::move(shared_memory)} {}

void SendingRelaySharedMemory::Send(const conduit::Node& node) {
  GetSharedMemory()->Store(node);
}

}  // namespace niv
