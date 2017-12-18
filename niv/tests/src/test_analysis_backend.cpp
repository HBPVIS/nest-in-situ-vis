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

#include "niv/analysis_backend.hpp"
#include "niv/analysis_device.hpp"
#include "niv/analysis_receiver.hpp"

namespace {

class Receiver : public niv::AnalysisReceiver {
 public:
  void Receive() override { ++count_receives_; }

  std::size_t GetCountReceives() const { return count_receives_; }

 private:
  std::size_t count_receives_{0u};
};

class Device : public niv::AnalysisDevice {
 public:
  Device() : niv::AnalysisDevice("Device") {}
  void Update() override { ++count_updates_; }

  std::size_t GetCountUpdates() const { return count_updates_; }

 private:
  std::size_t count_updates_{0u};
};

}  // namespace

SCENARIO("An analysis backend feeds data into the connected devices",
         "[niv][niv::AnalysisBackend]") {
  GIVEN("An analysis backend") {
    niv::AnalysisBackend backend;

    WHEN("a receiver is connected") {
      ::Receiver receiver;
      backend.Connect(&receiver);

      WHEN("the backend receives") {
        backend.Receive();
        THEN("the receiver has received once") {
          REQUIRE(receiver.GetCountReceives() == 1);
        }

        WHEN("when a device is connected") {
          ::Device device;
          backend.Connect(&device);

          WHEN("the backend receives again") {
            backend.Receive();
            THEN("the receiver was updated twice") {
              REQUIRE(receiver.GetCountReceives() == 2);
            }
            THEN("the device was updated once") {
              REQUIRE(device.GetCountUpdates() == 1);
            }
          }
        }
      }
    }
  }
}
