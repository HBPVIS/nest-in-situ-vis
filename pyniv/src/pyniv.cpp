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

#include "pyniv.hpp"

SUPPRESS_WARNINGS_BEGIN
#include "boost/python/numpy.hpp"
SUPPRESS_WARNINGS_END

#include "conduit/conduit_node.hpp"

#include "niv/consumer/backend.hpp"
#include "niv/consumer/multimeter.hpp"
#include "niv/consumer/receiver.hpp"
#include "niv/nest_test_data.hpp"
#include "niv/niv.hpp"

BOOST_PYTHON_MODULE(pyniv) {
  boost::python::numpy::initialize();
  def("Greet", niv::Greet);

  pyniv::expose<conduit::Node>();

  pyniv::expose<niv::consumer::Backend>();
  pyniv::expose<niv::consumer::Device>();
  pyniv::expose<niv::consumer::Receiver>();
  pyniv::expose<niv::consumer::Multimeter>();

  pyniv::expose<niv::Testing>();
}
