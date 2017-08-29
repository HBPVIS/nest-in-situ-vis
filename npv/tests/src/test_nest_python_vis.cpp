
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

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

#include "catch/catch.hpp"

#include "conduit/conduit.hpp"

#include "npv/nest_python_vis.hpp"

#include "test_utilities/cout_capture.hpp"

// gcc-5 does not accept using std::chrono_literals::operator""ms;
using namespace std::literals::chrono_literals;  // NOLINT

SCENARIO("An npv object shall visualize the double it is bound to",
         "[npv][npv::NestPythonVis") {
  GIVEN(
      "A membrane potenial in a conduit node and A NestPythonVis "
      "object") {
    conduit::Node node;
    node["V_m"] = 0.0;
    npv::NestPythonVis vis(&node);

    WHEN("I ask for a string representing the value") {
      auto ret_node = vis.NodeString();
      THEN("it shall represent the bound value.") { REQUIRE(ret_node == "0"); }
    }

    WHEN("the bound value is changed by some external code") {
      node["V_m"] = 42.0;
      THEN("its string representation shall be updated accordingly.") {
        REQUIRE(vis.NodeString() == "42");
      }
    }

    WHEN("I run the visualization for 30 ms") {
      test_utilities::CoutCapture cout_capture;
      vis.Start();
      std::this_thread::sleep_for(30ms);
      vis.Stop();
      THEN(
          "I will find more than one linebreak in printed the string "
          "representation") {
        const std::string cout_string = cout_capture.ToString();
        auto num_linebreaks =
            std::count(cout_string.begin(), cout_string.end(), '\n');
        REQUIRE(num_linebreaks > 1);
      }
    }
  }

  GIVEN("A NestPythonVis object bound to nullptr") {
    npv::NestPythonVis vis(nullptr);
    WHEN("I ask for a string representing tha value") {
      auto ret_val = vis.NodeString();
      THEN("it shall read 'nullptr'.") { REQUIRE(ret_val == "nullptr"); }
    }
  }
}

SCENARIO("We have a visualization application with a window") {
  GIVEN("A VisApplication") {
    npv::NestPythonVis app{nullptr};
    app.Start();
    WHEN("we call run") {
      THEN("we see one window") {
        auto all_windows{QApplication::topLevelWindows()};
        REQUIRE(all_windows.size() == 1);
      }
    }
    app.Stop();
  }
}
