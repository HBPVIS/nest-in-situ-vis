#-------------------------------------------------------------------------------
# nest in situ vis
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

def test_pyniv_receive_via_shared_mem_segment_relay():
    r = pyniv.ConduitReceiver()

    d = pyniv.ConduitData()
    s = pyniv.ConduitDataSender()
    s.Send(d)

    r.Start()

    assert r.Get("V_m") == 1.2

    d.Set("V_m", 42.0)
    s.Send(d)

    assert r.Get("V_m") == 42.0

def test_pyniv_receive_via_sync_shared_mem_relay():
    receiver = pyniv.SynchronizedReceiver()

    data = pyniv.ConduitData()
    data.Set("V_m", 4.123)
    
    sender = pyniv.SynchronizedSender()
    sender.Send(data)

    received_data = receiver.Receive()
    assert received_data.Get("V_m") ==4.123
    
    
