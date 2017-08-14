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

#ifndef NEST_PYTHON_VIS_INCLUDE_NPV_NPV_HPP_
#define NEST_PYTHON_VIS_INCLUDE_NPV_NPV_HPP_

#include <string>

namespace npv {

class NestPythonVis {
 public:
  explicit NestPythonVis(double* value) : value_(value) {}

  std::string ValueString() const;

  void Run();

 private:
  std::string FormatValue() const;
  double* value_{nullptr};
};

}  // namespace npv

#endif  // NEST_PYTHON_VIS_INCLUDE_NPV_NPV_HPP_
