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

#include <memory>
#include <utility>
#include <vector>

#include "conduit/conduit_core.hpp"
#include "conduit/conduit_schema.hpp"

#include "niv/synchronized_relay_shared_memory.hpp"

namespace niv {

SynchronizedRelaySharedMemory::SynchronizedRelaySharedMemory(
    std::unique_ptr<SharedMemory> shared_memory)
    : RelaySharedMemory{std::move(shared_memory)}, empty(true) {}

void SynchronizedRelaySharedMemory::Send(const conduit::Node& node) {
  std::cout << "SynchronizedRelaySharedMemory::Send" << std::endl;
  if (empty) {
    Store(node);
  } else {
    StoreUpdate(node);
  }
  empty = false;
}

void SynchronizedRelaySharedMemory::Store(const conduit::Node& node) {
  std::cout << "SynchronizedRelaySharedMemory::Store" << std::endl;
  shared_memory_->Store(node);
}

void SynchronizedRelaySharedMemory::StoreUpdate(const conduit::Node& node) {
  std::cout << "SynchronizedRelaySharedMemory::StoreUpdate" << std::endl;
  conduit::Node stored_node;
  shared_memory_->Read(&stored_node);
  stored_node.update(node);
  std::cout << "updated schema: " << std::endl;
  std::cout << stored_node.schema().to_json() << std::endl;
  std::cout << "updated compact schema: " << std::endl;
  conduit::Schema comp_schema;
  stored_node.schema().compact_to(comp_schema);
  std::cout << comp_schema.to_json() << std::endl;
  shared_memory_->Store(stored_node);
}

void SynchronizedRelaySharedMemory::Receive(conduit::Node* node) {
  std::cout << "SynchronizedRelaySharedMemory::Receive" << std::endl;
  shared_memory_->Read(node);
  empty = true;
}

}  // namespace niv
