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

#include <sys/types.h>

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit.hpp"

#include "niv/nest_in_situ_vis.hpp"

#include "test_utilities/cout_capture.hpp"

// gcc-5 does not accept using std::chrono_literals::operator""ms;
using namespace std::literals::chrono_literals;  // NOLINT

SCENARIO("An niv object shall visualize the double it is bound to",
         "[niv][niv::NestInSituVis") {
  GIVEN(
      "A membrane potenial in a conduit node and A NestInSituVis "
      "object") {
    conduit::Node node;
    node["V_m"] = 0.0;
    niv::NestInSituVis vis(&node);

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

    GIVEN("A vector for buffering data") {
      std::vector<conduit::uint8> data;
      THEN("the buffer is empty") { REQUIRE(data.size() == 0); }
      WHEN("When I ask the node to serialize into the buffer") {
        node.serialize(data);
        THEN("there is data in it") { REQUIRE(data.size() > 0); }
      }
    }

    GIVEN("Another node and a buffer") {
      conduit::Node another_node;
      another_node["V_m"] = 3.1415926;
      std::vector<conduit::uint8> data;
      WHEN(
          "I serialize another node into the buffer and read the buffer into "
          "the visualization") {
        another_node.serialize(data);
        conduit::Schema schema;
        another_node.schema().compact_to(schema);

        vis.Read(schema, &data);
        THEN("the first node will have acquired the data") {
          REQUIRE(node["V_m"].as_double() == Approx(3.1415926));
        }
      }
    }
  }

  GIVEN("A NestInSituVis object bound to nullptr") {
    niv::NestInSituVis vis(nullptr);
    WHEN("I ask for a string representing tha value") {
      auto ret_val = vis.NodeString();
      THEN("it shall read 'nullptr'.") { REQUIRE(ret_val == "nullptr"); }
    }
  }
}
