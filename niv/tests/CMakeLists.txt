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

file(GLOB NIV_TEST_SOURCES src/*.cpp)
file(GLOB NIV_TEST_HEADERS src/*.hpp)
file(GLOB NIV_TEST_UTILITIES_TEST_SOURCES test_utilities/tests/src/*.cpp)
file(GLOB NIV_TEST_UTILITIES_HEADERS test_utilities/*.hpp)


add_test_catch(NAME "niv-tests"
  SOURCES ${NIV_TEST_SOURCES} ${NIV_TEST_UTILITIES_TEST_SOURCES}
  HEADERS ${NIV_TEST_HEADERS} ${NIV_TEST_UTILITIES_HEADERS}
  CATCH_MAIN src/tests.cpp
  INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
  LINK_LIBRARIES niv
  PATH_TO_ADD ${PROJECT_BINARY_DIR}/niv
  )
add_test_cpplint(NAME "niv-tests--cpplint"
  ${NIV_TEST_SOURCES}
  ${NIV_TEST_HEADERS}
  ${NIV_TEST_UTILITIES_TEST_SOURCES}
  ${NIV_TEST_UTILITIES_HEADERS}
  )

