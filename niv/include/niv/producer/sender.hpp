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

#ifndef NIV_INCLUDE_NIV_PRODUCER_SENDER_HPP_
#define NIV_INCLUDE_NIV_PRODUCER_SENDER_HPP_

#include "conduit/conduit_node.hpp"

#include "niv/exchange/relay_shared_memory.hpp"

namespace niv {
namespace producer {

class Sender {
 public:
  Sender() = default;
  Sender(const Sender&) = delete;
  Sender(Sender&&) = default;
  ~Sender() = default;

  Sender& operator=(const Sender&) = delete;
  Sender& operator=(Sender&&) = default;

  void SetNode(conduit::Node* node) { node_ = node; }

  virtual void Send();

 private:
  conduit::Node* node_{nullptr};
  niv::exchange::RelaySharedMemory relay_;
};

}  // namespace producer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_PRODUCER_SENDER_HPP_
