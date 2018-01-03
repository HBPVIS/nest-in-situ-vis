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

#include "pyniv.hpp"

#include "niv/consumer/backend.hpp"
#include "niv/consumer/synchronized_aggregating_receiver.hpp"
#include "niv/niv.hpp"

#include "analysis_device.hpp"
#include "analysis_receiver.hpp"
#include "conduit_data.hpp"
#include "dummy_analysis_backend.hpp"
#include "synchronized_receiver.hpp"
#include "synchronized_sender.hpp"
#include "vis_multimeter.hpp"

BOOST_PYTHON_MODULE(pyniv) {
  boost::python::numpy::initialize();
  def("Greet", niv::Greet);
  pyniv::expose<niv::consumer::Backend>();
  pyniv::expose<pyniv::AnalysisDeviceWrap>();
  pyniv::expose<pyniv::AnalysisReceiverWrap>();
  pyniv::expose<pyniv::ConduitData>();
  pyniv::expose<pyniv::DummyAnalysisBackend>();
  pyniv::expose<pyniv::SynchronizedSender>();
  pyniv::expose<niv::SynchronizedAggregatingReceiver>();
  pyniv::expose<pyniv::SynchronizedReceiver>();
  pyniv::expose<pyniv::VisMultimeter>();
}
