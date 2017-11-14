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

#ifndef NIV_INCLUDE_NIV_RECORDER_HPP_
#define NIV_INCLUDE_NIV_RECORDER_HPP_

#include "conduit/conduit_node.hpp"

namespace niv {

class Recorder {
 public:
  Recorder(const Recorder&) = default;
  Recorder(Recorder&&) = default;
  virtual ~Recorder() = default;

  void SetRecordingTime(double time) {
    std::stringstream time_stream;
    time_stream << time;
    recording_time_ = time_stream.str();
  }

  virtual void Record(std::size_t) {}
  virtual void Record(std::size_t, const std::vector<double>) {}

  Recorder& operator=(const Recorder&) = default;
  Recorder& operator=(Recorder&&) = default;

 protected:
  Recorder(const std::string& name, conduit::Node* node)
      : node_(node), name_(name) {}

  conduit::Node* node_{nullptr};
  std::string name_{"recorder"};
  std::string recording_time_{"0"};
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_RECORDER_HPP_
