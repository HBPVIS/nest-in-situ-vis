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
#include <sstream>
#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "niv/nest_test_data.hpp"
#include "niv/producer/arbor_multimeter.hpp"

SCENARIO("A unique multimeter ptr can be constructed via its factory",
         "[niv][niv::ArborMultimeter]") {
  WHEN("a multimeter is constructed") {
    std::unique_ptr<niv::producer::ArborMultimeter> multimeter{
        niv::producer::ArborMultimeter::New("name", std::vector<std::string>(),
                                            nullptr)};
    THEN("a pointer was obtained") { REQUIRE(multimeter.get() != nullptr); }
  }
}

SCENARIO("A multimeter records to a conduit node",
         "[niv][niv::ArborMultimeter]") {
  GIVEN("A conduit node and a multimeter") {
    conduit::Node node;
    niv::producer::ArborMultimeter multimeter{
        niv::testing::ANY_MULTIMETER_NAME, niv::testing::ANY_ATTRIBUTES, &node};

    WHEN("recording data") {
      niv::producer::ArborMultimeter::Datum datum{
          niv::testing::ANY_TIME + niv::testing::ANY_TIME_OFFSET,
          std::string(niv::testing::ANY_ATTRIBUTE), niv::testing::ANY_ID,
          niv::testing::ANY_VALUE};
      multimeter.Record(datum);
      THEN("the data is recorded in the node") {
        std::stringstream path;
        path << niv::testing::ANY_MULTIMETER_NAME << '/';
        path << niv::testing::ANY_TIME << '/';
        path << niv::testing::ANY_ATTRIBUTE << '/';
        path << niv::testing::ANY_ID;

        REQUIRE(node[path.str()].as_double() ==
                Approx(niv::testing::ANY_VALUE));
      }
      // id tag time value
    }
  }
}
