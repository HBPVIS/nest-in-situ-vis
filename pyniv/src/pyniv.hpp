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

#ifndef PYNIV_SRC_PYNIV_HPP_
#define PYNIV_SRC_PYNIV_HPP_

SUPPRESS_WARNINGS_BEGIN
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#if __GNUC__ >= 7
#pragma GCC diagnostic ignored "-Wregister"
#endif
#include "boost/python.hpp"
SUPPRESS_WARNINGS_END

using boost::noncopyable;
using boost::python::args;
using boost::python::bases;
using boost::python::class_;
using boost::python::def;
using boost::python::init;
using boost::python::no_init;
using boost::python::pure_virtual;
using boost::python::scope;
using boost::python::wrapper;

namespace pyniv {

template <typename T>
void expose();

}  // namespace pyniv

#endif  // PYNIV_SRC_PYNIV_HPP_
