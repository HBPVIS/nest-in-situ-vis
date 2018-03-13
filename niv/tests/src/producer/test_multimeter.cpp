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
#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "niv/producer/nest_multimeter.hpp"

SCENARIO("A unique multimeter ptr can be constructed via its factory",
         "[niv][niv::Multimeter]") {
  WHEN("a new multimeter is constructed") {
    std::unique_ptr<niv::producer::NestMultimeter> multimeter{
        niv::producer::NestMultimeter::New("name", std::vector<std::string>(),
                                           nullptr)};
    THEN("a pointer was obtained") { REQUIRE(multimeter.get() != nullptr); }
  }
}

SCENARIO("A multimeter records to a conduit node", "[niv][niv::Multimeter]") {
  const std::string any_name{"multimeter1"};
  constexpr double any_time{1.5};
  const std::string any_time_string{"1.5"};
  constexpr std::size_t any_id{3};
  const std::string any_id_string{"3"};
  const std::vector<std::string> any_value_names{"A", "B", "C"};
  const std::vector<double> any_values{3.1415, 4.123, 42.0};

  GIVEN("a conduit node and a multimeter") {
    conduit::Node node;
    niv::producer::NestMultimeter multimeter(any_name, any_value_names, &node);

    WHEN("setting the recording time") {
      multimeter.SetRecordingTime(any_time);
      WHEN("recording") {
        multimeter.Record(any_id, any_values);
        THEN("data is recorded in the node") {
          for (std::size_t i = 0; i < any_value_names.size(); ++i) {
            REQUIRE(node[any_name][any_time_string][any_value_names[i]]
                        [any_id_string]
                            .to_double() == Approx(any_values[i]));
          }
        }
      }
    }
  }
}
