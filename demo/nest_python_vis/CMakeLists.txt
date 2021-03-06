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

set(NEST_PYTHON_VIS_SOURCE nest_python_vis.py)
set(NEST_SIM_SOURCE nest_sim.py)

if(NOT CMAKE_MAKE_PROGRAM STREQUAL "/usr/bin/xcodebuild")
  
file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/run_vis.sh
  CONTENT "PYTHONPATH=${PYNIV_OUTPUT_DIR}/..:$<TARGET_FILE_DIR:pytest_utilities> ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${NEST_PYTHON_VIS_SOURCE}"
  )

set(NEST_DIR
  CACHE PATH "Path to installed nest")
file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/run_sim.sh
  CONTENT
"source ${NEST_DIR}/bin/nest_vars.sh
PYTHONPATH=${PYNIV_OUTPUT_DIR}/..:$PYTHONPATH ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${NEST_SIM_SOURCE}"
  )

endif()
