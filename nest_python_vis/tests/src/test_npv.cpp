//------------------------------------------------------------------------------
// nest python vis
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

#include "npv/npv.hpp"

#include "test_utilities/cout_capture.hpp"

SCENARIO("An npv object shall visualize the double it is bound to",
         "[npv][npv::NestPythonVis") {
  GIVEN("A double and A NestPythonVis object") {
    double value = 0.0;
    npv::NestPythonVis vis(&value);

    WHEN("I ask for a string representing the value") {
      auto ret_val = vis.ValueString();
      THEN("it shall represent the bound value.") { REQUIRE(ret_val == "0"); }
    }

    WHEN("the bound value is changed by some external code") {
      value = 42.0;
      THEN("its string representation shall be updated accordingly.") {
        REQUIRE(vis.ValueString() == "42");
      }
    }

    WHEN("I run the visualization") {
      test_utilities::CoutCapture cout_capture;
      vis.Run();
      THEN("I will find the string representation of value on cout") {
        REQUIRE(cout_capture == "0\n");
      }
    }
  }

  GIVEN("A NestPythonVis object bound to nullptr") {
    npv::NestPythonVis vis(nullptr);
    WHEN("I ask for a string representing tha value") {
      auto ret_val = vis.ValueString();
      THEN("it shall read 'nullptr'.") { REQUIRE(ret_val == "nullptr"); }
    }
  }
}
