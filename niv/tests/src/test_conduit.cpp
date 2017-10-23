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

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

SCENARIO("update inserts new nodes", "[conduit]") {
  GIVEN("A conduit tree") {
    conduit::Node a;
    a["sim/t=0/Vm/N0"] = 0.5f;
    a["sim/t=0/Vm/N1"] = 0.75f;

    WHEN("A second node updates the second") {
      conduit::Node b;
      b["sim/t=1/Vm/N0"] = 1.5f;
      b["sim/t=1/Vm/N1"] = 1.75f;

      a.update(b);

      THEN("the first node contains also the content of the second") {
        REQUIRE(a["sim/t=0/Vm/N0"].to_float() == 0.5f);
        REQUIRE(a["sim/t=0/Vm/N1"].to_float() == 0.75f);
        REQUIRE(a["sim/t=1/Vm/N0"].to_float() == 1.5f);
        REQUIRE(a["sim/t=1/Vm/N1"].to_float() == 1.75f);
      }
    }
  }
}
