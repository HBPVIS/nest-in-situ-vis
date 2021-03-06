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

set(PYTHON_DUMP_SOURCE dump_to_stdout.py)
set(PYTHON_VIS_SOURCE vis.py)

if(NOT CMAKE_MAKE_PROGRAM STREQUAL "/usr/bin/xcodebuild")
  
file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/run_dump.sh
  CONTENT "PYTHONPATH=${PYNIV_OUTPUT_DIR}/..:$<TARGET_FILE_DIR:pytest_utilities> ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${PYTHON_DUMP_SOURCE}"
  )

file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/run_vis.sh
  CONTENT "PYTHONPATH=${PYNIV_OUTPUT_DIR}/..:$<TARGET_FILE_DIR:pytest_utilities> ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${PYTHON_VIS_SOURCE}"
  )

endif()
