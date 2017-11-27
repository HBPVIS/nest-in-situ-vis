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

#ifndef PYNIV_SRC_CONDUIT_DATA_SENDER_HPP_
#define PYNIV_SRC_CONDUIT_DATA_SENDER_HPP_

#include "niv/relay_shared_memory.hpp"
#include "niv/shared_memory_access.hpp"

#include "conduit_data.hpp"

namespace pyniv {

class ConduitDataSender {
 public:
  void Send(const ConduitData& data);

 private:
  niv::RelaySharedMemory relay_{std::make_unique<niv::SharedMemoryAccess>()};
  conduit::Node node_;
};

}  // namespace pyniv

#endif  // PYNIV_SRC_CONDUIT_DATA_SENDER_HPP_
