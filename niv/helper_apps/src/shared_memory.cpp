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

#include <iostream>
#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"
#include "conduit/conduit_schema.hpp"

#include "niv/shared_memory.hpp"

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

void StoreSchema(const conduit::Node& node, niv::SharedMemory* shared_memory) {
  conduit::Schema schema;
  node.schema().compact_to(schema);
  shared_memory->Store(schema.to_json());
}

void StoreData(const conduit::Node& node, niv::SharedMemory* shared_memory) {
  std::vector<conduit::uint8> data;
  node.serialize(data);
  shared_memory->Store(data);
}

void FillWithData(niv::SharedMemory* shared_memory) {
  conduit::Node node{AnyNode()};
  StoreSchema(node, shared_memory);
  StoreData(node, shared_memory);
}

void Create() {
  niv::SharedMemory shared_memory{niv::SharedMemory::Create()};
  FillWithData(&shared_memory);
}

void Fill() {
  niv::SharedMemory shared_memory{niv::SharedMemory::Access()};
  FillWithData(&shared_memory);
}

void Destroy() {
  niv::SharedMemory s{niv::SharedMemory::Access()};
  s.Destroy();
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
  }
  return EXIT_FAILURE;
}

int main(int argc, char** argv) {
  if (argc == 2) {
    return Command(argv[1]);
  }
  return EXIT_FAILURE;
}
