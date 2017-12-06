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

#include <memory>

#include "catch/catch.hpp"

#include "niv/shared_memory_access.hpp"
#include "niv/shared_memory_segment.hpp"
#include "niv/synchronized_relay_shared_memory.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("Mutex does not stall multiple sends/receives",
         "[niv][niv::SynchronizedRelaySharedMemory]") {
  GIVEN("a pair of relays") {
    niv::SynchronizedRelaySharedMemory relay_segment{
        niv::SynchronizedRelaySharedMemory::CreateSharedMemory()};
    niv::SynchronizedRelaySharedMemory relay_access{
        niv::SynchronizedRelaySharedMemory::AccessSharedMemory()};

    THEN("send, receive works") {
      relay_segment.Send(testing::AnyNode());
      relay_access.Receive();
    }

    THEN("receive, send works") {
      relay_access.Receive();
      relay_segment.Send(testing::AnyNode());
    }

    THEN("send, send, receive works") {
      relay_segment.Send(testing::AnyNode());
      relay_segment.Send(testing::AnotherNode());
      relay_access.Receive();
    }

    THEN("send, receive, send, receive works") {
      relay_segment.Send(testing::AnyNode());
      relay_access.Receive();
      relay_segment.Send(testing::AnotherNode());
    }

    THEN("receive, send, send, receive works") {
      relay_segment.Send(testing::AnyNode());
      relay_segment.Send(testing::AnotherNode());
      relay_access.Receive();
    }
  }
}
