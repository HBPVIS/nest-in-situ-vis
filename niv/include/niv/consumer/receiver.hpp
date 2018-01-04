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

#ifndef NIV_INCLUDE_NIV_CONSUMER_RECEIVER_HPP_
#define NIV_INCLUDE_NIV_CONSUMER_RECEIVER_HPP_

#include "conduit/conduit_node.hpp"

#include "niv/relay_shared_memory.hpp"

namespace niv {
namespace consumer {

class Receiver {
 public:
  Receiver() = default;
  Receiver(const Receiver&) = delete;
  Receiver(Receiver&&) = default;
  virtual ~Receiver() = default;

  Receiver& operator=(const Receiver&) = delete;
  Receiver& operator=(Receiver&&) = default;

  void SetNode(conduit::Node* node) { node_ = node; }

  virtual void Receive();

 private:
  RelaySharedMemory relay_;
  conduit::Node* node_;
};

}  // namespace consumer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_CONSUMER_RECEIVER_HPP_
