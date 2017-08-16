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

SUPPRESS_WARNINGS_BEGIN
#include "boost/python.hpp"
SUPPRESS_WARNINGS_END

#include "npv/npv.hpp"

#if defined __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

BOOST_PYTHON_MODULE(pynpv) {
  using boost::python::class_;
  using boost::python::def;
  using boost::python::init;

  def("Greet", npv::Greet);

  class_<npv::NestPythonVis, boost::noncopyable>("NestPythonVis",
                                                 init<std::size_t>())
      .def("ValueString", &npv::NestPythonVis::ValueString);
}

#if defined __clang__
#pragma clang diagnostic pop
#endif
