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

#include <iostream>
#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"
#include "conduit/conduit_schema.hpp"

#include "niv/shared_memory.hpp"
#include "niv/shared_memory_synchronization.hpp"

conduit::Node AnyNode() {
  conduit::Node node;
  node["A"]["B"]["E"] = 1.1;
  node["A"]["C"]["F"] = 2.1;
  node["A"]["C"]["G"] = 2.2;
  node["A"]["D"]["H"] = 3.1;
  node["A"]["D"]["I"] = 3.2;
  node["A"]["D"]["J"] = 3.3;
  return node;
}

void FillWithData(niv::SharedMemory* shared_memory) {
  conduit::Node node{AnyNode()};
  shared_memory->Store(node);
}

void Create() {
  niv::SharedMemory segment{niv::SharedMemory::Create()};
  FillWithData(&segment);
}

void Fill() {
  niv::SharedMemory access{niv::SharedMemory::Access()};
  FillWithData(&access);
}

void Destroy() {
  niv::SharedMemory access{niv::SharedMemory::Access()};
  access.Destroy();
}

void CreateMutex() {
  niv::SharedMemorySynchronization::ManagedMutex mutex{
      boost::interprocess::create_only,
      niv::SharedMemorySynchronization::MutexName()};
}

void DestroyMutex() {
  niv::SharedMemorySynchronization::ManagedMutex mutex{
      boost::interprocess::open_only,
      niv::SharedMemorySynchronization::MutexName()};
  mutex.unlock();
  niv::SharedMemorySynchronization::ManagedMutex::remove(
      niv::SharedMemorySynchronization::MutexName());
}

int Command(char* command) {
  if (std::string(command) == std::string("create")) {
    Create();
    return EXIT_SUCCESS;
  } else if (std::string(command) == "fill") {
    Fill();
  } else if (std::string(command) == std::string("destroy")) {
    Destroy();
    return EXIT_SUCCESS;
  } else if (std::string(command) == std::string("create_mutex")) {
    CreateMutex();
    return EXIT_SUCCESS;
  } else if (std::string(command) == std::string("destroy_mutex")) {
    DestroyMutex();
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int main(int argc, char** argv) {
  if (argc == 2) {
    return Command(argv[1]);
  }
  return EXIT_FAILURE;
}
