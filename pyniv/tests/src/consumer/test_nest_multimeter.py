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

def test_nest_multimeter_provides_access_to_data_stored_in_a_conduit_node():
    nest_data = pyniv.testing.ANY_NEST_DATA
    multimeter = pyniv.consumer.NestMultimeter(pyniv.testing.AnyMultimeterName())
    multimeter.SetNode(nest_data)

    multimeter.SetTime(pyniv.testing.ANY_TIME)

    multimeter.SetAttribute(pyniv.testing.ANY_ATTRIBUTE)
    multimeter.Update()
    result = multimeter.GetValues()
    expected = [
        pyniv.testing.ValueAt(pyniv.testing.ANY_TIME_INDEX,
                              pyniv.testing.ANY_ATTRIBUTE_INDEX,
                              pyniv.testing.ANY_ID_INDEX),
        pyniv.testing.ValueAt(pyniv.testing.ANY_TIME_INDEX,
                              pyniv.testing.ANY_ATTRIBUTE_INDEX,
                              pyniv.testing.ANOTHER_ID_INDEX),
        pyniv.testing.ValueAt(pyniv.testing.ANY_TIME_INDEX,
                              pyniv.testing.ANY_ATTRIBUTE_INDEX,
                              pyniv.testing.THIRD_ID_INDEX)]
    assert (result == expected).all()

    multimeter.SetAttribute(pyniv.testing.ANOTHER_ATTRIBUTE)
    multimeter.Update()
    result = multimeter.GetValues()
    expected = [
        pyniv.testing.ValueAt(pyniv.testing.ANY_TIME_INDEX,
                              pyniv.testing.ANOTHER_ATTRIBUTE_INDEX,
                              pyniv.testing.ANY_ID_INDEX),
        pyniv.testing.ValueAt(pyniv.testing.ANY_TIME_INDEX,
                              pyniv.testing.ANOTHER_ATTRIBUTE_INDEX,
                              pyniv.testing.ANOTHER_ID_INDEX),
        pyniv.testing.ValueAt(pyniv.testing.ANY_TIME_INDEX,
                              pyniv.testing.ANOTHER_ATTRIBUTE_INDEX,
                              pyniv.testing.THIRD_ID_INDEX)]
    assert (result == expected).all()
    
