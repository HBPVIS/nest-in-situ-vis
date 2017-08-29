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

include(FindPythonInterp)
if(NOT PYTHON_EXECUTABLE)
  message(SEND_ERROR
    " ERROR: Could not find any python interpreter.
        Having a python interpreter is a mandatory requirement for cpplint.
        CMake will not generate the project without it. ")
endif()

find_file(CPPLINT_COMMAND cpplint.py
  PATHS $ENV{PATH} $ENV{CPPLINT_DIR}
)
if(NOT CPPLINT_COMMAND)
  message(SEND_ERROR
    " ERROR: Could not find cpplint.py.
        Having cpplint.py is a mandatory requirement.
        CMake will not generate the project without it.
        Add its location to the environments variables PATH or CPPLINT_DIR.")
endif()

function(ADD_TEST_CPPLINT)
  set(options )
  set(oneValueArgs NAME)
  set(multiValueArgs )
  cmake_parse_arguments(ADD_TEST_CPPLINT
    "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  if(MSVC)
    set(CPPLINT_OUTPUT "--output=vs7")
  else()
    set(CPPLINT_OUTPUT "")
  endif()

  add_test(NAME "${ADD_TEST_CPPLINT_NAME}"
    COMMAND ${PYTHON_EXECUTABLE} ${CPPLINT_COMMAND} ${CPPLINT_OUTPUT}
    ${ADD_TEST_CPPLINT_UNPARSED_ARGUMENTS}
  )
endfunction()
