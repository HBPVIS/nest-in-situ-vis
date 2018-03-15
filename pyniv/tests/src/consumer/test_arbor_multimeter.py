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

import numpy as np

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

def test_arbor_multimeter_retrieves_datum_for_time_attribute_neuron():
    multimeter, nest_data = setup_multimeter()
    datum = multimeter.GetDatum(pyniv.testing.ANY_TIME,
                                pyniv.testing.ANOTHER_ATTRIBUTE,
                                pyniv.testing.THIRD_ID)
    datum_offset = (pyniv.testing.ANY_TIME_OFFSET +
                    pyniv.testing.ANOTHER_ATTRIBUTE_OFFSET +
                    pyniv.testing.THIRD_ID_OFFSET);
    assert np.isclose(datum, pyniv.testing.ANY_VALUES[datum_offset])

    datum = multimeter.GetDatum(pyniv.testing.NOT_A_TIME,
                                pyniv.testing.ANOTHER_ATTRIBUTE,
                                pyniv.testing.THIRD_ID)
    assert np.isnan(datum)

    datum = multimeter.GetDatum(pyniv.testing.ANY_TIME,
                                pyniv.testing.NOT_AN_ATTRIBUTE,
                                pyniv.testing.THIRD_ID)
    assert np.isnan(datum)

    datum = multimeter.GetDatum(pyniv.testing.ANY_TIME,
                                pyniv.testing.ANOTHER_ATTRIBUTE,
                                pyniv.testing.NOT_AN_ID)
    assert np.isnan(datum)

    multimeter, nest_data = setup_multimeter(
        name = pyniv.testing.NOT_A_MULTIMETER_NAME)
    datum = multimeter.GetDatum(pyniv.testing.ANY_TIME,
                                pyniv.testing.ANOTHER_ATTRIBUTE,
                                pyniv.testing.THIRD_ID)
    assert np.isnan(datum)

def test_arbor_multimeter_provides_time_series_data():
    data_offsets = [(time_offset +
                     pyniv.testing.ANOTHER_ATTRIBUTE_OFFSET +
                     pyniv.testing.THIRD_ID_OFFSET)
                    for time_offset in pyniv.testing.TIME_OFFSETS()]
    expected = np.array([pyniv.testing.ANY_VALUES[o] for o in data_offsets])

    multimeter, nest_data = setup_multimeter()
    values = multimeter.GetTimeSeriesData(pyniv.testing.ANOTHER_ATTRIBUTE,
                                          pyniv.testing.THIRD_ID)
    assert (values == expected).all()

    values = multimeter.GetTimeSeriesData(pyniv.testing.NOT_AN_ATTRIBUTE,
                                          pyniv.testing.THIRD_ID)
    assert np.isnan(values).all()

    values = multimeter.GetTimeSeriesData(pyniv.testing.ANOTHER_ATTRIBUTE,
                                          pyniv.testing.NOT_AN_ID)
    assert np.isnan(values).all()

    multimeter, nest_data = setup_multimeter(
        name = pyniv.testing.NOT_A_MULTIMETER_NAME)
    values = multimeter.GetTimeSeriesData(pyniv.testing.ANOTHER_ATTRIBUTE,
                                          pyniv.testing.THIRD_ID)
    assert np.isnan(values).all()

def test_arbor_multimeter_provides_timestep_data_for_all_neurons():
    data_offsets = [(pyniv.testing.THIRD_TIME_OFFSET +
                     pyniv.testing.ANOTHER_ATTRIBUTE_OFFSET +
                     id_offset) for id_offset in pyniv.testing.ID_OFFSETS()]
    expected = np.array([pyniv.testing.ANY_VALUES[o] for o in data_offsets])

    multimeter, nest_data = setup_multimeter()
    values = multimeter.GetTimestepData(
        pyniv.testing.THIRD_TIME, pyniv.testing.ANOTHER_ATTRIBUTE)
    assert (values == expected).all()

    values = multimeter.GetTimestepData(
        pyniv.testing.NOT_A_TIME, pyniv.testing.ANOTHER_ATTRIBUTE)
    assert np.isnan(values).all()

    values = multimeter.GetTimestepData(
        pyniv.testing.THIRD_TIME, pyniv.testing.NOT_AN_ATTRIBUTE)
    assert np.isnan(values).all()

    multimeter, nest_data = setup_multimeter(
        name = pyniv.testing.NOT_A_MULTIMETER_NAME)
    values = multimeter.GetTimestepData(
        pyniv.testing.THIRD_TIME, pyniv.testing.ANOTHER_ATTRIBUTE)
    assert np.isnan(values).all()
