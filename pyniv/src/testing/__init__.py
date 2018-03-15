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

from _testing import *

import numpy as np

ANY_TIMES = [ANY_TIME, ANOTHER_TIME, THIRD_TIME];
ANY_TIMES_STRING = [ANY_TIME_STRING, ANOTHER_TIME_STRING, THIRD_TIME_STRING];
ANY_ATTRIBUTES = [ANY_ATTRIBUTE, ANOTHER_ATTRIBUTE, THIRD_ATTRIBUTE];
ANY_IDS = [ANY_ID, ANOTHER_ID, THIRD_ID];
ANY_VALUES = np.array([
    0.111, 0.112, 0.113,  0.121, 0.122, 0.123,  0.131, 0.132, 0.133,
    0.211, 0.212, 0.213,  0.221, 0.222, 0.223,  0.231, 0.232, 0.233,
    0.311, 0.312, 0.313,  0.321, 0.322, 0.323,  0.331, 0.332, 0.333])
