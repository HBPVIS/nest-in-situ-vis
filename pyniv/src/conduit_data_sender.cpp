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

#include "pyniv.hpp"

#include "conduit_data_sender.hpp"

#include "conduit_data.hpp"

namespace pyniv {

void ConduitDataSender::Send(const ConduitData& data) {
  relay_.Send(data.GetNode());
}

template <>
void expose<ConduitDataSender>() {
  class_<ConduitDataSender, boost::noncopyable>("ConduitDataSender")
      .def("Send", &ConduitDataSender::Send, args("data"));
}

}  // namespace pyniv
