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

def test_integration_consumer():
    backend = pyniv.consumer.Backend()

    receiver = pyniv.consumer.Receiver()
    backend.Connect(receiver)

    multimeter = pyniv.consumer.Multimeter(pyniv.testing.AnyMultimeterName())
    multimeter.SetAttribute(pyniv.testing.AnyValueNames(0))
    backend.Connect(multimeter)

    pyniv.testing.Send(pyniv.testing.AnyNestData())

    backend.Receive()
    
    multimeter.SetTime(pyniv.testing.AnyTime())
    multimeter.Update()
    values_at_t0 = multimeter.GetValues()
    assert np.isclose(values_at_t0, pyniv.testing.AnyAttributesValues()).all()

    multimeter.SetTime(pyniv.testing.AnotherTime())
    multimeter.Update()
    values_at_t1 = multimeter.GetValues()
    assert np.isclose(values_at_t1, pyniv.testing.AnyAttributesValues(pyniv.testing.AnotherTime())).all()
