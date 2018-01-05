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

#ifndef PYNIV_SRC_ANALYSIS_RECEIVER_HPP_
#define PYNIV_SRC_ANALYSIS_RECEIVER_HPP_

#include "niv/consumer/receiver.hpp"

#include "pyniv.hpp"

namespace pyniv {

struct AnalysisReceiverWrap : niv::consumer::Receiver,
                              wrapper<niv::consumer::Receiver> {
  void Receive() { this->Receive(); }
};

}  // namespace pyniv

#endif  // PYNIV_SRC_ANALYSIS_RECEIVER_HPP_
