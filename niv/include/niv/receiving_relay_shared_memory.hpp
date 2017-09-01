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

#ifndef NIV_INCLUDE_NIV_RECEIVING_RELAY_SHARED_MEMORY_HPP_
#define NIV_INCLUDE_NIV_RECEIVING_RELAY_SHARED_MEMORY_HPP_

#include <memory>

#include "conduit/conduit_node.hpp"

#include "niv/relay_shared_memory.hpp"
#include "niv/shared_memory.hpp"

namespace niv {

class ReceivingRelaySharedMemory : public RelaySharedMemory {
 public:
  explicit ReceivingRelaySharedMemory(
      std::unique_ptr<SharedMemory> shared_memory);
  virtual ~ReceivingRelaySharedMemory() = default;

  void Receive(conduit::Node* node);
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_RECEIVING_RELAY_SHARED_MEMORY_HPP_
