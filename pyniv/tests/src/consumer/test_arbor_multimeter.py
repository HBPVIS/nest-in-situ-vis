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

def setup_multimeter(name = pyniv.testing.ANY_MULTIMETER_NAME,
                     data = pyniv.testing.ANY_NEST_DATA):
    multimeter = pyniv.consumer.ArborMultimeter(name)
    multimeter.SetNode(data)
    return multimeter, data

def test_arbor_multimeter_lists_the_timesteps():
    multimeter, nest_data = setup_multimeter()
    timesteps = multimeter.GetTimestepsString();
    assert timesteps == pyniv.testing.ANY_TIMES_STRING

    multimeter, nest_data = setup_multimeter(
        name = pyniv.testing.NOT_A_MULTIMETER_NAME)
    timesteps = multimeter.GetTimestepsString();
    assert timesteps == []

def test_arbor_multimeter_lists_attributes_for_a_timestep():
    multimeter, nest_data = setup_multimeter()
    attributes = multimeter.GetAttributes(pyniv.testing.ANY_TIME)
    assert attributes == pyniv.testing.ANY_ATTRIBUTES

    attributes = multimeter.GetAttributes(pyniv.testing.NOT_A_TIME)
    assert attributes == []

    multimeter, nest_data = setup_multimeter(
        name = pyniv.testing.NOT_A_MULTIMETER_NAME)
    attributes = multimeter.GetAttributes(pyniv.testing.ANY_TIME)
    assert attributes == []

def test_arbor_multimeter_lists_neuron_ids_for_an_attribute_in_a_timestep():
    multimeter, nest_data = setup_multimeter()
    ids = multimeter.GetNeuronIds(pyniv.testing.ANY_TIME,
                                  pyniv.testing.ANY_ATTRIBUTE)
    assert ids == pyniv.testing.ANY_IDS

    
    ids = multimeter.GetNeuronIds(pyniv.testing.NOT_A_TIME,
                                  pyniv.testing.ANY_ATTRIBUTE)
    assert ids == []
    
    ids = multimeter.GetNeuronIds(pyniv.testing.ANY_TIME,
                                  pyniv.testing.NOT_AN_ATTRIBUTE)
    assert ids == []
    
    multimeter, nest_data = setup_multimeter(
        name = pyniv.testing.NOT_A_MULTIMETER_NAME)
    ids = multimeter.GetNeuronIds(pyniv.testing.ANY_TIME,
                                  pyniv.testing.ANY_ATTRIBUTE)
    assert ids == []
