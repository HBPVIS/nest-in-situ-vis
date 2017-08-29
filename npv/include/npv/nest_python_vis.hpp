//------------------------------------------------------------------------------
// nest python vis
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

#ifndef NPV_INCLUDE_NPV_NEST_PYTHON_VIS_HPP_
#define NPV_INCLUDE_NPV_NEST_PYTHON_VIS_HPP_

#include <chrono>
#include <memory>
#include <string>
#include <thread>

#include "conduit/conduit.hpp"

// gcc-5 does not accept using std::chrono_literals::operator""ms;
using namespace std::literals::chrono_literals;  // NOLINT

namespace npv {

class NestPythonVis {
 public:
  explicit NestPythonVis(conduit::Node* node = nullptr);
  explicit NestPythonVis(std::size_t ptr_to_node);
  ~NestPythonVis();
  NestPythonVis(const NestPythonVis&) = delete;

  void Start();
  void Stop();

  std::string NodeString() const;

 private:
  void PrintNode() const;
  std::string FormatNode() const;
  void EnableIsRunning();
  void DisableIsRunning();
  bool IsRunning() const;
  void Run();
  void Step();
  void Sleep() { std::this_thread::sleep_for(sleep_in_use_); }
  void SpawnThread() {
    thread_ = std::make_unique<std::thread>(&NestPythonVis::Run, this);
  }
  void JoinAndDeleteThread() {
    if (thread_ != nullptr) {
      thread_->join();
      thread_.reset();
    }
  }

  conduit::Node* node_{nullptr};
  std::unique_ptr<std::thread> thread_{nullptr};
  static constexpr std::chrono::duration<int, std::milli> disabled_sleep_{0ms};
  std::chrono::duration<int, std::milli> configured_sleep_{10ms};
  std::chrono::duration<int, std::milli> sleep_in_use_{disabled_sleep_};
};

}  // namespace npv

#endif  // NPV_INCLUDE_NPV_NEST_PYTHON_VIS_HPP_
