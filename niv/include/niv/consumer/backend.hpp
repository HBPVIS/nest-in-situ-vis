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

#ifndef NIV_INCLUDE_NIV_CONSUMER_BACKEND_HPP_
#define NIV_INCLUDE_NIV_CONSUMER_BACKEND_HPP_

#include <vector>

#include "conduit/conduit_node.hpp"

#include "niv/consumer/analysis_receiver.hpp"
#include "niv/consumer/device.hpp"

namespace niv {
namespace consumer {

class Backend {
 public:
  Backend() = default;
  Backend(const Backend&) = delete;
  Backend(Backend&&) = delete;
  virtual ~Backend() = default;

  Backend& operator=(const Backend&) = delete;
  Backend& operator=(Backend&&) = delete;

  void Connect(niv::AnalysisReceiver* receiver);
  void Connect(niv::consumer::Device* device);
  void Receive();

 protected:
  niv::AnalysisReceiver* receiver_{nullptr};
  std::vector<niv::consumer::Device*> devices_;

  conduit::Node node_;
};

}  // namespace consumer
}  // namespace niv

#endif  // NIV_INCLUDE_NIV_CONSUMER_BACKEND_HPP_
