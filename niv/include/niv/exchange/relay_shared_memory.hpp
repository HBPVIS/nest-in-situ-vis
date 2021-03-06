//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017-2018 RWTH Aachen University, Germany,
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

#ifndef NIV_INCLUDE_NIV_EXCHANGE_RELAY_SHARED_MEMORY_HPP_
#define NIV_INCLUDE_NIV_EXCHANGE_RELAY_SHARED_MEMORY_HPP_

#include <memory>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/exchange/shared_memory.hpp"
#include "niv/exchange/shared_memory_synchronization.hpp"

namespace niv {
namespace exchange {

SUPPRESS_WARNINGS_BEGIN_PADDED
class RelaySharedMemory {
 public:
  class CreateSharedMemory {};
  class AccessSharedMemory {};

  RelaySharedMemory();
  virtual ~RelaySharedMemory();
  RelaySharedMemory(const RelaySharedMemory&) = delete;
  RelaySharedMemory(RelaySharedMemory&&) = delete;

  void Send(const conduit::Node& node);
  conduit::Node Receive();

  RelaySharedMemory& operator=(const RelaySharedMemory&) = delete;
  RelaySharedMemory& operator=(RelaySharedMemory&&) = delete;

  bool IsEmpty() const;

 protected:
  explicit RelaySharedMemory(const CreateSharedMemory&);
  explicit RelaySharedMemory(const AccessSharedMemory&);
  SharedMemory* GetSharedMemory() { return shared_memory_.get(); }
  const SharedMemory* GetSharedMemory() const { return shared_memory_.get(); }

 private:
  void SendUpdate(const conduit::Node& node);

  std::unique_ptr<SharedMemory> shared_memory_;
  std::unique_ptr<SharedMemorySynchronization> synchronization_;
};
SUPPRESS_WARNINGS_END

}  // namespace exchange
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_EXCHANGE_RELAY_SHARED_MEMORY_HPP_
