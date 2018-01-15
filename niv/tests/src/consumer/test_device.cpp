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

#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "niv/consumer/device.hpp"
#include "niv/nest_test_data.hpp"

namespace {

class Device : public niv::consumer::Device {
 public:
  explicit Device(const std::string& name) : niv::consumer::Device(name) {}
  Device(const Device&) = delete;
  Device(Device&&) = delete;
  ~Device() = default;

  Device& operator=(const Device&) = delete;
  Device& operator=(Device&&) = delete;

  void Update() override {}
};

}  // namespace

SCENARIO("A consumer::Device can list its timesteps",
         "[niv][niv::consumer][niv::consumer::Device]") {
  GIVEN("A device accessing a node") {
    conduit::Node any_data{niv::testing::AnyNestData()};
    ::Device device("multimeter A");
    device.SetNode(&any_data);
    WHEN("The device is asked for the timesteps") {
      auto timesteps(device.GetTimesteps());
      THEN("the list of timesteps is correct") {
        REQUIRE_THAT(timesteps,
                     Catch::Matchers::Equals(std::vector<double>{0}));
      }
    }
  }
}
