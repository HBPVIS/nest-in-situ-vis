#-------------------------------------------------------------------------------
# nest in situ vis
#
# Copyright (c) 2017-2018 RWTH Aachen University, Germany,
# Virtual Reality & Immersive Visualisation Group.
#-------------------------------------------------------------------------------
#                                  License
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#-------------------------------------------------------------------------------

add_executable(niv-shared-memory
  src/shared_memory.cpp
  )
target_link_libraries(niv-shared-memory
  niv
  )
set_warning_levels_RWTH(niv-shared-memory
  SUPPRESS_WARNINGS_HEADER
    ${CMAKE_CURRENT_BINARY_DIR}/include/niv/suppress_warnings.hpp
  )
