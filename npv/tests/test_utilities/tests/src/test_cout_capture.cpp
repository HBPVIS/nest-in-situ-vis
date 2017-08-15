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

#include <iostream>

#include "catch/catch.hpp"

#include "test_utilities/cout_capture.hpp"

SCENARIO("CoutCapture captures standard output", "[tests][test::utils]") {
  GIVEN("a CoutCapture") {
    test_utilities::CoutCapture cout_capture;

    WHEN("I print something to cout") {
      std::cout << "something";
      THEN("'something' is captured") { REQUIRE(cout_capture == "something"); }
      WHEN("I add else to cout") {
        std::cout << " else";
        THEN("'something else' is captures") {
          REQUIRE(cout_capture == "something else");
        }
      }
      WHEN("I then use another CoutCapture and print foo") {
        test_utilities::CoutCapture another_cout_capture;
        std::cout << "foo";
        THEN("only 'foo' should be captured") {
          REQUIRE(another_cout_capture == "foo");
        }
      }
    }
    WHEN("I print two lines to cout") {
      std::cout << "two" << std::endl;
      std::cout << "lines";
      THEN("two lines are captured") { REQUIRE(cout_capture == "two\nlines"); }
    }
  }
}

SCENARIO(
    "CoutCapture captures standard output respecting the scope of the "
    "CoutCapture",
    "[tests][test::utils]") {
  WHEN("I use CoutCapture in different scopes") {
    test_utilities::CoutCapture cout_capture;
    std::cout << "something";
    {
      test_utilities::CoutCapture another_cout_capture;
      std::cout << "foo";
    }
    std::cout << " else";
    THEN("the scope is respected") {
      REQUIRE(cout_capture == "something else");
    }
  }
}
