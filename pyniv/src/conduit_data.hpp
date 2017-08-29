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

#ifndef PYNIV_SRC_CONDUIT_DATA_HPP_
#define PYNIV_SRC_CONDUIT_DATA_HPP_

#include "conduit/conduit.hpp"

namespace pyniv {

class ConduitData {
 public:
  ConduitData() {
    node_["V_m"] = 0.0;
    std::cout << "Ptr. to conduit node: " << Pointer() << std::endl;
  }
  ~ConduitData() = default;
  ConduitData(const ConduitData&) = default;
  ConduitData(ConduitData&&) = default;

  void Set(const char* attribute, double value) { node_[attribute] = value; }
  std::size_t Pointer() const { return reinterpret_cast<std::size_t>(&node_); }

 private:
  conduit::Node node_;
};

}  // namespace pyniv

#endif  // PYNIV_SRC_CONDUIT_DATA_HPP_
