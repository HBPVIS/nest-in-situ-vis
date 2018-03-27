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

#include "niv/consumer/backend.hpp"

#include <algorithm>

#include "niv/consumer/receiver.hpp"

namespace niv {

void consumer::Backend::Connect(niv::consumer::Receiver* receiver) {
  receiver->SetNode(&node_);
  receiver_ = receiver;
}

void consumer::Backend::Connect(niv::consumer::Device* device) {
  auto found = std::find(devices_.begin(), devices_.end(), device);
  if (found == devices_.end()) {
    device->SetNode(&node_);
    devices_.push_back(device);
  }
}

void consumer::Backend::Receive() {
  if (receiver_ != nullptr) {
    receiver_->Receive();
  }

  // for (auto device : devices_) {
  // device->Update();
  //}
}

}  // namespace niv
