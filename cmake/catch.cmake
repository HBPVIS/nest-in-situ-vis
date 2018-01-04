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

include(WarningLevels)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)


function(CONFIGURE_MSVC_USERFILE TARGET_NAME PATH_TO_ADD)
  file(TO_NATIVE_PATH "${PATH_TO_ADD}/Release" _DLL_PATH_RELEASE)
  file(TO_NATIVE_PATH "${PATH_TO_ADD}/Debug" _DLL_PATH_DEBUG)
  set(SOURCE_USER_FILE
    "${CMAKE_SOURCE_DIR}/cmake/VisualStudio2013.vcxproj.user.in")
  set(DESTINATION_USER_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.vcxproj.user")
  message("DESTINATION_USER_FILE: ${DESTINATION_USER_FILE}")
  configure_file(${SOURCE_USER_FILE} ${DESTINATION_USER_FILE} @ONLY)
endfunction()


function(ADD_TEST_CATCH_INTERNAL_
    NAME SOURCES HEADERS INCLUDE_DIRECTORIES LINK_LIBRARIES PATH_TO_ADD)
  STRING(REGEX REPLACE
    "^__" ""
    NAME "${NAME}"
    )
  add_executable(${NAME} ${SOURCES} ${HEADERS})
  target_include_directories(${NAME} PRIVATE ${INCLUDE_DIRECTORIES})
  target_link_libraries(${NAME} ${LINK_LIBRARIES})
  add_test(NAME ${NAME} COMMAND ${NAME})
  set_warning_levels_RWTH(${NAME})

  set_property(TARGET ${NAME} PROPERTY FOLDER "Tests")
  source_group("Sources" FILES ${SOURCES} ${HEADERS})

  if(WIN32 AND MSVC)
    configure_msvc_userfile(${NAME} ${PATH_TO_ADD})
  endif()
endfunction()


function(CREATE_CATCH_MAIN_INTERNAL_
    NAME SOURCE INCLUDE_DIRECTORIES)
  add_library(${NAME} ${SOURCE})
  target_include_directories(${NAME} PRIVATE ${INCLUDE_DIRECTORIES})
  set_property(TARGET ${NAME} PROPERTY FOLDER "Tests")
  source_group("Sources" FILES ${SOURCE})
endfunction()


function(ADD_TEST_CATCH)
  # parse arguments
  set(options )
  set(oneValueArgs NAME CATCH_MAIN)
  set(multiValueArgs
    SOURCES HEADERS INCLUDE_DIRECTORIES LINK_LIBRARIES PATH_TO_ADD)
  cmake_parse_arguments(ADD_TEST_CATCH
    "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  create_catch_main_internal_("${ADD_TEST_CATCH_NAME}_catch_main"
    ${ADD_TEST_CATCH_CATCH_MAIN}
    ${ADD_TEST_CATCH_INCLUDE_DIRECTORIES}
  )

  # remove catch_main file from sources
  file(GLOB ADD_TEST_CATCH_CATCH_MAIN_ABSOLUTE ${ADD_TEST_CATCH_CATCH_MAIN})
  list(REMOVE_ITEM ADD_TEST_CATCH_SOURCES ${ADD_TEST_CATCH_CATCH_MAIN_ABSOLUTE})

  # add test for each test source file
  foreach(TEST_SOURCE_FILE ${ADD_TEST_CATCH_SOURCES})
    get_filename_component(TEST_SUBDIR ${TEST_SOURCE_FILE} DIRECTORY)
    STRING(REGEX REPLACE
      "^${CMAKE_CURRENT_SOURCE_DIR}" ""
      TEST_SUBDIR "${TEST_SUBDIR}"
      )
    STRING(REGEX REPLACE
      "[/|\\]" "__"
      TEST_SUBDIR "${TEST_SUBDIR}"
      )
    get_filename_component(TEST_NAME ${TEST_SOURCE_FILE} NAME_WE)
    ADD_TEST_CATCH_INTERNAL_("${TEST_SUBDIR}__${TEST_NAME}"
      "${TEST_SOURCE_FILE}"
      ""
      "${ADD_TEST_CATCH_INCLUDE_DIRECTORIES}"
      "${ADD_TEST_CATCH_LINK_LIBRARIES};${ADD_TEST_CATCH_NAME}_catch_main"
      "${ADD_TEST_CATCH_PATH_TO_ADD}"
    )
  endforeach()
endfunction()
