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

cmake_minimum_required(VERSION 3.8.2)

project(nest_in_situ_vis)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS python)
find_library(Boost_PYTHON_NUMPY_LIBRARY
  boost_numpy
  PATHS ${Boost_LIBRARY_DIRS}
  NO_DEFAULT_PATH
  )
set(Boost_LIBRARIES
  ${Boost_LIBRARIES}
  ${Boost_PYTHON_NUMPY_LIBRARY}
  )

find_package(PythonInterp)
find_package(PythonLibs)

include(catch)

include(ConfigureFiles)

include(cpplint)

include(CTest)
enable_testing()

include(GenerateExportHeader)

include(py.test)

include(python_module)

include(WarningLevels)

find_package(Conduit)
set_target_properties(conduit
  PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CONDUIT_INCLUDE_DIRS}/..")

add_subdirectory(niv)
add_subdirectory(pyniv)
add_subdirectory(pytest_utilities)
add_subdirectory(demo)
