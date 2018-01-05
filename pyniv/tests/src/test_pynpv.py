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

import ctypes
import sys
import time

import pyniv

import pytest_utilities

def test_pypvt():
    assert True

def test_cout_capture(capsys):
    print("hello")
    sys.stderr.write("world\n")
    out, err = capsys.readouterr()
    assert out == "hello\n"
    assert err == "world\n"
    print ("next")
    out, err = capsys.readouterr()
    assert out == "next\n"

def test_pyniv_greet():
    assert pyniv.Greet() == "G'day!"

def test_pyniv_backend():
    backend = pyniv.AnalysisBackend()
    receiver = pyniv.SynchronizedAggregatingReceiver()
    multimeter = pyniv.VisMultimeter("Multimeter A")
    backend.Connect(receiver)
    backend.Connect(multimeter)
    multimeter.SetTime(0.0)
    multimeter.SetAttribute("A")
    backend.Receive()
    a = multimeter.GetValues()
    assert len(a) == 0

def test_pyniv_dummy_analysis_backend():
    backend = pyniv.DummyAnalysisBackend();
    multimeter = pyniv.VisMultimeter("multimeter A")
    multimeter.SetAttribute("V_m")
    backend.Connect(multimeter)
    multimeter.SetTime(0.0)
    backend.Receive()
    a = multimeter.GetValues()
    assert (a == [0.0, -0.1, 0.2, -0.3, 0.4, -0.5]).all()

def test_pyniv_dummy_vis_multimeter_timesteps():
    backend = pyniv.DummyAnalysisBackend();
    multimeter = pyniv.VisMultimeter("multimeter A")
    backend.Connect(multimeter)
    ts = multimeter.GetTimesteps();
    assert (ts == [0.0]).all()
