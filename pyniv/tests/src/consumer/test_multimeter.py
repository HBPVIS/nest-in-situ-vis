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

import pyniv

def test_multimeter_provides_access_to_data_stored_in_a_conduit_node():
    nest_data = pyniv.TestingAnyNestData()
    multimeter = pyniv.ConsumerMultimeter(pyniv.TestingAnyMultimeterName())
    multimeter.SetNode(nest_data)

    multimeter.SetTime(pyniv.TestingAnyTime())

    multimeter.SetAttribute(pyniv.TestingAnyValueNames(0))
    multimeter.Update()
    result = multimeter.GetValues()
    assert (result == pyniv.TestingAnyAttributesValues()).all()

    multimeter.SetAttribute(pyniv.TestingAnyValueNames(1))
    multimeter.Update()
    result = multimeter.GetValues()
    assert (result == pyniv.TestingAnotherAttributesValues()).all()