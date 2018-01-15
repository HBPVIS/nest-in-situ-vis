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

class Receiver(pyniv.ConsumerReceiver):
    def __init__(self):
        pyniv.ConsumerReceiver.__init__(self)
        self.count_receives = 0;

    def Receive(self):
        self.count_receives += 1;

class Device(pyniv.ConsumerDevice):
    def __init__(self):
        pyniv.ConsumerDevice.__init__(self)
        self.count_updates = 0;

    def Update(self):
        self.count_updates += 1;

def test_pyniv_consumer_backend():
    backend = pyniv.ConsumerBackend()

    receiver = Receiver()
    backend.Connect(receiver)
    backend.Receive()
    assert receiver.count_receives == 1

    device = Device()
    backend.Connect(device)
    backend.Receive()
    assert receiver.count_receives == 2
    assert device.count_updates == 1
