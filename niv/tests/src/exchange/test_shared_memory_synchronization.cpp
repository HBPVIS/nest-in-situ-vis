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

#include "catch/catch.hpp"

#include "niv/exchange/shared_memory_synchronization.hpp"

SCENARIO("SharedMemorySynchronization locks and releases properly",
         "[niv][niv::SharedMemorySynchronization]") {
  GIVEN("A SharedMemorySynchronization") {
    niv::exchange::SharedMemorySynchronization sync{
        niv::exchange::SharedMemorySynchronization::Create()};
    WHEN("scoped lock is acquired") {
      auto lock{sync.ScopedLock()};
      THEN("the mutex cannot be locked a second time") {
        const bool lockable = sync.TryLock();
        REQUIRE_FALSE(lockable);
        if (lockable) {
          sync.Unlock();
        }
      }
    }
    WHEN("The lock is out of scope") {
      THEN("the mutex can be locked a second time") {
        const bool lockable = sync.TryLock();
        REQUIRE(lockable);
        if (lockable) {
          sync.Unlock();
        }
      }
    }
    sync.Destroy();
  }
}

SCENARIO("SharedMemorySynchronization locks and releases through shared mem",
         "[niv][niv::SharedMemorySynchronization]") {
  GIVEN("A pair of shared memory synchronization") {
    niv::exchange::SharedMemorySynchronization sync_object{
        niv::exchange::SharedMemorySynchronization::Create()};
    niv::exchange::SharedMemorySynchronization sync_access{
        niv::exchange::SharedMemorySynchronization::Access()};

    WHEN("scoped lock is acquired on the first one") {
      auto lock = sync_object.ScopedLock();
      THEN("the second one is locked") {
        const bool lockable = sync_access.TryLock();
        REQUIRE_FALSE(lockable);
        if (lockable) {
          sync_access.Unlock();
        }
      }
    }

    WHEN("The lock is out of scope") {
      THEN("the second mutex can be locked") {
        const bool lockable = sync_access.TryLock();
        REQUIRE(lockable);
        if (lockable) {
          sync_access.Unlock();
        }
      }
    }

    WHEN("scoped lock is acquired on the second one") {
      auto lock = sync_access.ScopedLock();
      THEN("the first one is locked") {
        const bool lockable = sync_object.TryLock();
        REQUIRE_FALSE(lockable);
        if (lockable) {
          sync_object.Unlock();
        }
      }
    }

    WHEN("The lock is out of scope") {
      THEN("the first mutex can be locked") {
        const bool lockable = sync_object.TryLock();
        REQUIRE(lockable);
        if (lockable) {
          sync_object.Unlock();
        }
      }
    }
    sync_object.Destroy();
  }
}
