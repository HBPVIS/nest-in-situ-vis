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

#include <chrono>
#include <random>
#include <thread>

#include "catch/catch.hpp"

#include "niv/relay_shared_memory.hpp"

#include "conduit_node_helper.hpp"

namespace {

void Send(niv::RelaySharedMemory* relay) {
  std::random_device random_seed;
  std::mt19937 generator(random_seed());
  std::uniform_int_distribution<> distribution(1, 4);  // define the range

  for (auto i = 0u; i < 10; ++i) {
    const int wait = distribution(generator);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    relay->Send(testing::AnyNode());
  }
}

void Receive(niv::RelaySharedMemory* relay) {
  std::random_device random_seed;
  std::mt19937 generator(random_seed());
  std::uniform_int_distribution<> distribution(3, 6);  // define the range

  for (auto i = 0u; i < 10; ++i) {
    const int wait = distribution(generator);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    relay->Receive();
  }
}

constexpr bool we_reach_this_before_timeout = true;

}  // namespace

SCENARIO("Synchronization across separate threads does not accidently block",
         "[niv][niv::RelaySharedMemory]") {
  GIVEN("A pair of sync relays") {
    niv::RelaySharedMemory relay_segment;
    niv::RelaySharedMemory relay_access;

    WHEN("These send and receive in separate threads") {
      std::thread sender(::Send, &relay_access);
      std::thread receiver(::Receive, &relay_segment);
      THEN("they do not block each other") {
        sender.join();
        receiver.join();
        REQUIRE(::we_reach_this_before_timeout);
      }
    }
  }
}
