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

file(GLOB PYTEST_UTILITIES_SOURCES src/*.cpp)

find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonInterp)
find_package(PythonLibs)

python_add_module(pytest_utilities
  ${PYTEST_UTILITIES_SOURCES}
)

target_include_directories(pytest_utilities PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(pytest_utilities ${Boost_LIBRARIES})

target_include_directories(pytest_utilities PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(pytest_utilities ${PYTHON_LIBRARIES})

set_warning_levels_RWTH(pytest_utilities
  SUPPRESS_WARNINGS_HEADER ${CMAKE_CURRENT_BINARY_DIR}/include/pytest_utilities/suppress_warnings.hpp
)

add_test_cpplint(NAME "pytest_utilities--cpplint"
  ${PYTEST_UTILITIES_SOURCES}
)
