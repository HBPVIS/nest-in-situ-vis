#-------------------------------------------------------------------------------
# nest python vis
#
# Copyright (c) 2017 RWTH Aachen University, Germany,
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

import pynpv

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

def test_pynpv_greet():
    assert pynpv.Greet() == "G'day!"

def test_pynpv_npv_ValueString():
    d = ctypes.c_double(42.0);
    ptr = ctypes.c_void_p.from_buffer(ctypes.pointer(d)).value
    v = pynpv.NestPythonVis(ptr);
    assert v.ValueString() == "42"

def test_pynpv_npv_StartStop():
    d = ctypes.c_double(42.0);
    ptr = ctypes.c_void_p.from_buffer(ctypes.pointer(d)).value
    v = pynpv.NestPythonVis(ptr);

    c = pytest_utilities.CoutCapture()

    v.Start()
    time.sleep(0.03)
    v.Stop()

    assert len(c.ToString().split('\n')) > 2
