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

import numpy as np

import pyniv

class Device(pyniv.consumer.Device):
    def __init__(self, name):
        pyniv.consumer.Device.__init__(self, name)

def test_consumer_device_lists_timesteps():
    any_data = pyniv.testing.AnyNestData()
    device = Device(pyniv.testing.AnyMultimeterName())
    device.SetNode(any_data)
    timesteps = device.GetTimesteps()
    assert len(timesteps) == 2
    expected_timesteps = [pyniv.testing.AnyTime(), pyniv.testing.AnotherTime()]
    assert np.isclose(timesteps, expected_timesteps).all()
