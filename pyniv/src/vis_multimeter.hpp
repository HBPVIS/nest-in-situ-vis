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

#ifndef PYNIV_SRC_VIS_MULTIMETER_HPP_
#define PYNIV_SRC_VIS_MULTIMETER_HPP_

SUPPRESS_WARNINGS_BEGIN
#include "boost/python/numpy.hpp"
SUPPRESS_WARNINGS_END

#include "niv/vis_multimeter.hpp"

namespace pyniv {

class VisMultimeter : public niv::VisMultimeter {
 public:
  VisMultimeter() = delete;
  explicit VisMultimeter(const std::string& name);
  VisMultimeter(const VisMultimeter&) = default;
  VisMultimeter(VisMultimeter&&) = default;
  ~VisMultimeter() = default;

  VisMultimeter& operator=(const VisMultimeter&) = default;
  VisMultimeter& operator=(VisMultimeter&&) = default;

  boost::python::numpy::ndarray GetValues();

  void Update() override;

 private:
  boost::python::numpy::ndarray values_;
};

}  // namespace pyniv

#endif  // PYNIV_SRC_VIS_MULTIMETER_HPP_
