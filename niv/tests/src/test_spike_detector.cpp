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

#include "niv/spike_detector.hpp"

SCENARIO("A unique spike detector ptr can be constructed via its factory",
         "[niv][niv::SpikeDetector]") {
  WHEN("a new spike detector is constructed") {
    std::unique_ptr<niv::SpikeDetector> spike_detector{
        niv::SpikeDetector::New("name", nullptr)};
    THEN("a pointer was obtained") { REQUIRE(spike_detector.get() != nullptr); }
  }
}

SCENARIO("A spike detector records to a conduit node",
         "[niv][niv::SpikeDetector]") {
  const std::string any_name{"spikes1"};
  constexpr double any_time{1.5};
  const std::string any_time_string{"1.5"};
  constexpr std::size_t any_id{3};
  constexpr std::size_t another_id{5};

  GIVEN("a conduit node and a spike detector") {
    conduit::Node node;
    niv::SpikeDetector spike_detector(any_name, &node);

    WHEN("setting the recording time") {
      spike_detector.SetRecordingTime(any_time);
      WHEN("recording") {
        spike_detector.Record(any_id);
        THEN("data is recorded in the node") {
          REQUIRE(node[any_name][any_time_string].as_uint64_array()[0] ==
                  any_id);
        }
        WHEN("recording another spike") {
          spike_detector.Record(another_id);
          THEN("data is recorded in the node") {
            REQUIRE(node[any_name][any_time_string].as_uint64_array()[0] ==
                    any_id);
            REQUIRE(node[any_name][any_time_string].as_uint64_array()[1] ==
                    another_id);
          }
        }
      }
    }
  }
}
