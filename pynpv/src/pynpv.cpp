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

#include "pynpv.hpp"

SUPPRESS_WARNINGS_BEGIN
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "boost/python.hpp"
SUPPRESS_WARNINGS_END

#include "npv/npv.hpp"

#include "nest_python_vis.hpp"

BOOST_PYTHON_MODULE(pynpv) {
  def("Greet", npv::Greet);
  pynpv::expose<npv::NestPythonVis>();
}

#if defined __clang__
#pragma clang diagnostic pop
#endif
