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

file(GLOB NIV_SOURCES src/*.cpp src/**/*.cpp)
file(GLOB NIV_HEADERS src/*.hpp src/**/*.hpp)
file(GLOB NIV_API_HEADERS include/niv/*.hpp include/niv/**/*.hpp)

add_library(niv
  ${NIV_SOURCES}
  ${NIV_HEADERS}
  ${NIV_API_HEADERS}
  )
target_include_directories(niv
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include
  PUBLIC ${Boost_INCLUDE_DIR}
  )

SET(ADDITIONAL_LINUX_LIBRARIES )
if(UNIX AND NOT APPLE)
  SET(ADDITIONAL_LINUX_LIBRARIES 
    pthread
    rt
    )
endif()
target_link_libraries(niv
  conduit
  ${ADDITIONAL_LINUX_LIBRARIES}
  )
target_compile_options(niv
  PRIVATE -fPIC
  )

generate_export_header(niv
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/niv/export.hpp
  )

set_warning_levels_RWTH(niv
  SUPPRESS_WARNINGS_HEADER ${CMAKE_CURRENT_BINARY_DIR}/include/niv/suppress_warnings.hpp
  )

add_test_cpplint(NAME "niv--cpplint"
  ${NIV_SOURCES}
  ${NIV_HEADERS}
  ${NIV_API_HEADERS}
  )

generate_configure_files(niv)

add_subdirectory(tests)
add_subdirectory(helper_apps)
