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

#ifndef PYNPV_SRC_NEST_PYTHON_VIS_HPP_
#define PYNPV_SRC_NEST_PYTHON_VIS_HPP_

#include "npv/nest_python_vis.hpp"

#include "pynpv.hpp"

namespace pynpv {

template <>
void expose<npv::NestPythonVis>() {
  class_<npv::NestPythonVis, boost::noncopyable>("NestPythonVis",
                                                 init<std::size_t>())
      .def("NodeString", &npv::NestPythonVis::NodeString)
      .def("Start", &npv::NestPythonVis::Start)
      .def("Stop", &npv::NestPythonVis::Stop);
}

}  // namespace pynpv

#endif  // PYNPV_SRC_NEST_PYTHON_VIS_HPP_
