#-------------------------------------------------------------------------------
# nest in situ vis
#
# Copyright (c) 2017 RWTH Aachen University, Germany,
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

function(GENERATE_CONFIGURE_FILES TARGET)
  # config for the build tree
  set(CONF_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
  )
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/${TARGET}-config.cmake.in
    "${PROJECT_BINARY_DIR}/${TARGET}-config.cmake" @ONLY)
  export(TARGETS ${TARGET}
    FILE "${PROJECT_BINARY_DIR}/${TARGET}-targets.cmake")
endfunction()
