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

#include "catch/Catch.hpp"

#include "niv/consumer/arbor_multimeter.hpp"
#include "niv/nest_test_data.hpp"

SCENARIO("An ArborMultimeter can list the stored node ids in a timestep",
         "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  GIVEN("a multimeter providing access to some data") {
    const conduit::Node nest_data{niv::testing::AnyNestData()};
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::AnyMultimeterName());
    multimeter.SetNode(&nest_data);

    WHEN("The time step is set") {
      multimeter.SetTime(niv::testing::ANY_TIME);
      multimeter.Update();
    }
  }
}
