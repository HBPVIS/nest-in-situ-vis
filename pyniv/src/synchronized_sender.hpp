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

#ifndef PYNIV_SRC_SYNCHRONIZED_SENDER_HPP_
#define PYNIV_SRC_SYNCHRONIZED_SENDER_HPP_

#include "niv/exchange/relay_shared_memory.hpp"

#include "conduit_data.hpp"

namespace pyniv {

class SynchronizedSender {
 public:
  SynchronizedSender() = default;
  SynchronizedSender(const SynchronizedSender&) = delete;
  SynchronizedSender(SynchronizedSender&&) = delete;
  ~SynchronizedSender() = default;

  SynchronizedSender& operator=(const SynchronizedSender&) = delete;
  SynchronizedSender& operator=(SynchronizedSender&&) = delete;

  void Send(const ConduitData& data);

 private:
  niv::exchange::RelaySharedMemory relay_;
};

}  // namespace pyniv

#endif  // PYNIV_SRC_SYNCHRONIZED_SENDER_HPP_
