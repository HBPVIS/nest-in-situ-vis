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

#include "conduit/conduit_node.hpp"

#include "niv/exchange/shared_memory.hpp"
#include "niv/testing/helpers.hpp"

#include "conduit_node_helper.hpp"

SCENARIO("Shared memory creation", "[niv][niv::SharedMemory]") {
  GIVEN("A shared memory segment") {
    niv::exchange::SharedMemory segment{niv::exchange::SharedMemory::Create()};
    WHEN("I ask it for its free size") {
      auto free_size_after_creation = segment.GetFreeSize();
      THEN("it is > 0") { REQUIRE(free_size_after_creation > 0); }
    }

    WHEN("I read data from the new segment") {
      THEN("it does not throw") { REQUIRE_NOTHROW(segment.Read()); }
      THEN("it is empty") { REQUIRE(segment.Read().dtype().is_empty()); }
    }

    WHEN("I store data in the segment") {
      auto free_size_before = segment.GetFreeSize();
      segment.Store(niv::testing::ANY_NODE);
      auto free_size_after = segment.GetFreeSize();
      THEN("we have less free space in the segment") {
        REQUIRE(free_size_after < free_size_before);
      }
      THEN("I can read the data") {
        REQUIRE_THAT(segment.Read(), Equals(niv::testing::ANY_NODE));
      }
    }

    WHEN("I request a second shared memory segment") {
      THEN("It throws an exception") {
        REQUIRE_THROWS_WITH(
            []() {
              niv::exchange::SharedMemory segment2{
                  niv::exchange::SharedMemory::Create()};
              segment2.Destroy();
            }(),
            "File exists");
      }
    }
    segment.Destroy();
  }
}

SCENARIO("write updated node to shared memory segment",
         "[niv][niv::SharedMemory]") {
  GIVEN("a shared memory segment with some data") {
    niv::exchange::SharedMemory segment{niv::exchange::SharedMemory::Create()};
    segment.Store(niv::testing::ANY_NODE);
    WHEN("a larger node is stored") {
      segment.Store(niv::testing::UPDATED_NODE);
      WHEN("the node is read") {
        conduit::Node read_node{segment.Read()};
        THEN("the content is equal to the written one") {
          REQUIRE_THAT(read_node, Equals(niv::testing::UPDATED_NODE));
        }
      }
    }
    segment.Destroy();
  }
}

SCENARIO("Shared memory access", "[niv][niv::SharedMemory]") {
  GIVEN("No shared memory segment") {
    THEN("Creating a shared memory access throws an exception.") {
      REQUIRE_THROWS_WITH(
          niv::exchange::SharedMemory{niv::exchange::SharedMemory::Access()},
          "No such file or directory");
    }
  }

  GIVEN("A shared memory segment") {
    niv::exchange::SharedMemory segment{niv::exchange::SharedMemory::Create()};

    WHEN("I create shared memory access") {
      THEN("It does not throw an exception") {
        REQUIRE_NOTHROW(
            niv::exchange::SharedMemory{niv::exchange::SharedMemory::Access()});
      }
      niv::exchange::SharedMemory segment_access{
          niv::exchange::SharedMemory::Access()};

      WHEN("data is stored in the shared memory access") {
        segment_access.Store(niv::testing::ANY_NODE);

        THEN("it can be read") {
          REQUIRE_THAT(segment_access.Read(), Equals(niv::testing::ANY_NODE));
        }
      }
    }
    segment.Destroy();
  }
}

SCENARIO("storing and retrieving conduit nodes to/from shared memory",
         "[niv][niv:SharedMemory][niv:SharedMemorySegment][niv:"
         "SharedMemoryAccess]") {
  GIVEN("a shared memory segment and access") {
    niv::exchange::SharedMemory shared_memory_segment{
        niv::exchange::SharedMemory::Create()};
    niv::exchange::SharedMemory shared_memory_access{
        niv::exchange::SharedMemory::Access()};

    WHEN("a node is stored in the shared memory segment") {
      shared_memory_segment.Store(niv::testing::ANY_NODE);

      THEN("it can be read via access") {
        REQUIRE_THAT(shared_memory_access.Read(),
                     Equals(niv::testing::ANY_NODE));
      }

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node{shared_memory_access.Listen()};
        WHEN("the first node is updated and stored again") {
          shared_memory_segment.Store(niv::testing::ANOTHER_NODE);
          THEN("the result arrives at the listening node") {
            REQUIRE_THAT(listening_node, Equals(niv::testing::ANOTHER_NODE));
          }
        }
      }
    }

    WHEN("a node is stored in the shared memory access") {
      shared_memory_access.Store(niv::testing::ANY_NODE);

      THEN("it can be read from the segment") {
        REQUIRE_THAT(shared_memory_segment.Read(),
                     Equals(niv::testing::ANY_NODE));
      }

      GIVEN("a node listening to shared memory") {
        conduit::Node listening_node{shared_memory_segment.Listen()};
        WHEN("the first node is updated and stored again") {
          shared_memory_segment.Store(niv::testing::ANOTHER_NODE);
          THEN("the result arrives at the listening node") {
            REQUIRE_THAT(listening_node, Equals(niv::testing::ANOTHER_NODE));
          }
        }
      }
    }
    shared_memory_segment.Destroy();
  }
}

SCENARIO("Overwriting data in shared memory",
         "[niv][niv::SharedMemory][niv::SharedMemorySegment][niv::"
         "SharedMemoryAccess") {
  GIVEN("A shared memory segment + access, with some data in it") {
    niv::exchange::SharedMemory shared_memory_segment{
        niv::exchange::SharedMemory::Create()};
    niv::exchange::SharedMemory shared_memory_access{
        niv::exchange::SharedMemory::Access()};
    shared_memory_segment.Store(niv::testing::ANY_NODE);
    WHEN("when new data is stored in the segment") {
      shared_memory_segment.Store(niv::testing::A_DIFFERENT_NODE);
      WHEN("that data is read") {
        conduit::Node read_node{shared_memory_access.Read()};
        THEN("the read data is equal to the stored one") {
          REQUIRE_THAT(read_node, Equals(niv::testing::A_DIFFERENT_NODE));
        }
      }
    }
    shared_memory_segment.Destroy();
  }
}

SCENARIO("data can be updated in shared memory",
         "[niv][niv::SharedMemory][niv::SharedMemorySegment][niv::"
         "SharedMemoryAccess") {
  std::cout << "SCENARIO(\"data can be updated in shared memory\")"
            << std::endl;
  GIVEN("a shared memory segment with data in it, and shared memory access") {
    niv::exchange::SharedMemory segment{niv::exchange::SharedMemory::Create()};
    niv::exchange::SharedMemory segment_access{
        niv::exchange::SharedMemory::Access()};
    segment.Store(niv::testing::ANY_NODE);

    WHEN("the data in the shared memory is updated") {
      segment.Update(niv::testing::ANY_UPDATE);
      THEN("the  updated data can be read from the segment") {
        REQUIRE_THAT(segment.Read(), Equals(niv::testing::UPDATED_NODE));
      }
      THEN("the updated data can be read from the segment access") {
        REQUIRE_THAT(segment.Read(), Equals(niv::testing::UPDATED_NODE));
      }
    }
    segment.Destroy();
  }
}

SCENARIO("Shared memory provides correct reference counts",
         "[niv][niv::SharedMemory]") {
  GIVEN("a shared memory segment") {
    niv::exchange::SharedMemory segment{niv::exchange::SharedMemory::Create()};
    THEN("the reference count is correct") {
      REQUIRE(segment.GetReferenceCount() == 0);
    }

    WHEN("a shared memory access is created in a new scope") {
      {  // new scope
        niv::exchange::SharedMemory access{
            niv::exchange::SharedMemory::Access()};
        THEN("the reference count is correct") {
          REQUIRE(segment.GetReferenceCount() == 1);
          REQUIRE(access.GetReferenceCount() == 1);
        }
      }
      WHEN("that shared memory access gets out of scope") {
        THEN("the reference count is correct") {
          REQUIRE(segment.GetReferenceCount() == 0);
        }
      }
    }

    segment.Destroy();
  }
}
