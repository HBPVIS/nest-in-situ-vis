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

#ifndef NIV_INCLUDE_NIV_CONDUIT_RECEIVER_HPP_
#define NIV_INCLUDE_NIV_CONDUIT_RECEIVER_HPP_

#include <memory>
#include <string>

#include "conduit/conduit_node.hpp"

#include "niv/receiving_relay_shared_memory.hpp"
#include "niv/shared_memory_segment.hpp"

namespace niv {

class ConduitReceiver {
 public:
  void Start();
  double Get(const std::string& path) const;

 private:
  niv::ReceivingRelaySharedMemory relay_{
      std::make_unique<SharedMemorySegment>()};
  conduit::Node node_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_CONDUIT_RECEIVER_HPP_