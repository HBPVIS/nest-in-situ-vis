#-------------------------------------------------------------------------------
# nest python vis
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

file(GLOB NPV_SOURCES src/*.cpp)
file(GLOB NPV_HEADERS src/*.hpp)
file(GLOB NPV_API_HEADERS include/npv/*.hpp)

add_library(npv
  ${NPV_SOURCES}
  ${NPV_HEADERS}
  ${NPV_API_HEADERS}
)
target_include_directories(npv
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  )
target_link_libraries(npv
  conduit
  Qt5::Core
  Qt5::Widgets
  )

generate_export_header(npv
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/npv/export.hpp
)

set_warning_levels_RWTH(npv
  SUPPRESS_WARNINGS_HEADER ${CMAKE_CURRENT_BINARY_DIR}/include/npv/suppress_warnings.hpp
)

add_test_cpplint(NAME "npv--cpplint"
  ${NPV_SOURCES}
  ${NPV_HEADERS}
  ${NPV_API_HEADERS}
)

generate_configure_files(npv)

add_subdirectory(tests)
