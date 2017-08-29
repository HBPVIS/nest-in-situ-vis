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



file(GLOB PYNIV_SOURCES src/*.cpp)

find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonInterp)
find_package(PythonLibs)

python_add_module(pyniv
  ${PYNIV_SOURCES}
)
target_link_libraries(pyniv niv)

target_include_directories(pyniv
  PRIVATE ${Boost_INCLUDE_DIRS}
  PRIVATE ${PYTHON_INCLUDE_DIRS}
  )
target_link_libraries(pyniv
  ${Boost_LIBRARIES}
  ${PYTHON_LIBRARIES}
  )

set_warning_levels_RWTH(pyniv
  SUPPRESS_WARNINGS_HEADER ${CMAKE_CURRENT_BINARY_DIR}/include/pyniv/suppress_warnings.hpp
)

add_test_cpplint(NAME "pyniv--cpplint"
  ${PYNIV_SOURCES}
)

add_subdirectory(tests)
