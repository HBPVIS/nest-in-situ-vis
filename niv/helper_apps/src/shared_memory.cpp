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

#include "conduit/conduit_core.hpp"
#include "niv/shared_memory.hpp"

void create() {
  niv::SharedMemory s{niv::SharedMemory::Create()};
  auto& data = s.GetDataVector();
  std::vector<conduit::uint8> any_vector{'a', 'b', 'c'};
  data.assign(any_vector.begin(), any_vector.end());
}

void destroy() {
  niv::SharedMemory s{niv::SharedMemory::Access()};
  s.Destroy();
}

int command(char* command) {
  if (std::string(command) == std::string("create")) {
    create();
    return EXIT_SUCCESS;
  } else if (std::string(command) == std::string("destroy")) {
    destroy();
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int main(int argc, char** argv) {
  if (argc == 2) {
    return command(argv[1]);
  }
  return EXIT_FAILURE;
}
