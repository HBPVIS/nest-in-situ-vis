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

#include <memory>
#include <string>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "niv/nest_test_data.hpp"
#include "niv/producer/spike_detector.hpp"

SCENARIO("A unique spike detector ptr can be constructed via its factory",
         "[niv][niv::SpikeDetector]") {
  WHEN("a new spike detector is constructed") {
    std::unique_ptr<niv::producer::SpikeDetector> spike_detector{
        niv::producer::SpikeDetector::New("name", nullptr)};
    THEN("a pointer was obtained") { REQUIRE(spike_detector.get() != nullptr); }
  }
}

SCENARIO("A spike detector records to a conduit node",
         "[niv][niv::SpikeDetector]") {
  GIVEN("a conduit node and a spike detector") {
    conduit::Node node;
    niv::producer::SpikeDetector spike_detector(
        niv::testing::ANY_SPIKE_DETECTOR_NAME, &node);

    WHEN("recording") {
      spike_detector.Record(niv::producer::SpikeDetector::Datum{
          niv::testing::ANY_TIME, niv::testing::ANY_ID});
      THEN("data is recorded in the node") {
        const auto recorded_node = node[niv::testing::ANY_SPIKE_DETECTOR_NAME]
                                       [niv::testing::ANY_TIME_STRING];
        REQUIRE(recorded_node.as_uint64_array()[0] == niv::testing::ANY_ID);
      }
      WHEN("recording another spike") {
        spike_detector.Record(
            {niv::testing::ANY_TIME, niv::testing::ANOTHER_ID});
        THEN("data is recorded in the node") {
          const auto recorded_node = node[niv::testing::ANY_SPIKE_DETECTOR_NAME]
                                         [niv::testing::ANY_TIME_STRING];
          REQUIRE(recorded_node.as_uint64_array()[0] == niv::testing::ANY_ID);
          REQUIRE(recorded_node.as_uint64_array()[1] ==
                  niv::testing::ANOTHER_ID);
        }
      }
    }
  }
}
