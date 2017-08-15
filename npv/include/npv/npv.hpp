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

#ifndef NPV_INCLUDE_NPV_NPV_HPP_
#define NPV_INCLUDE_NPV_NPV_HPP_

#include <chrono>
#include <memory>
#include <string>
#include <thread>

using std::chrono_literals::operator""ms;

namespace npv {

class NestPythonVis {
 public:
  explicit NestPythonVis(double* value) : value_(value) {}
  ~NestPythonVis() {
    if (thread_ != nullptr) {
      thread_->join();
    }
  }

  void Start() {
    sleep_in_use_ = configured_sleep_;
    thread_ = std::make_unique<std::thread>(&NestPythonVis::Run, this);
  }
  void Stop() { sleep_in_use_ = 0ms; }

  std::string ValueString() const;

 private:
  void PrintValue() const;
  std::string FormatValue() const;
  bool IsRunning() const { return sleep_in_use_ != 0ms; }
  void Run();
  void Sleep() { std::this_thread::sleep_for(sleep_in_use_); }

  double* value_{nullptr};
  std::unique_ptr<std::thread> thread_{nullptr};
  std::chrono::duration<int, std::milli> sleep_in_use_{0ms};
  std::chrono::duration<int, std::milli> configured_sleep_{10ms};
};

}  // namespace npv

#endif  // NPV_INCLUDE_NPV_NPV_HPP_
