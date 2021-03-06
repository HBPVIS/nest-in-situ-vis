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

import sys
import nest
import numpy

from PyQt5.QtWidgets import QApplication, QPushButton
from PyQt5.QtCore import QTimer

class Simulation:
    def __init__(self):
        self.ConfigureNest()
        self.CreateAndConnectNeurons()
        self.CreateAndConnectRecordingDevices()
        self.CreateAndConnectSpikeGenerators()

    def ConfigureNest(self):
        nest.ResetKernel()
        nest.SetKernelStatus({"overwrite_files": True,
                              "data_path": "",
                              "data_prefix": ""})
        nest.SetDefaults('static_synapse', {'delay': 0.1})

    def CreateAndConnectNeurons(self):
        neuron_params={"tau_syn_ex": 1.0,
                       "V_reset": -70.0}
        self.populationA = nest.Create("iaf_cond_alpha",
                                       params=neuron_params)
        self.populationB = nest.Create("iaf_cond_alpha", 2,
                                       params=neuron_params)
        nest.Connect(self.populationA, self.populationB, syn_spec={"weight": 100.0});

    def CreateAndConnectRecordingDevices(self):
        self.CreateAndConnectConduitMultimeter(self.populationA, "multimeter A")
        self.CreateAndConnectConduitMultimeter(self.populationB, "multimeter B")

        self.CreateAndConnectConduitSpikeDetector(self.populationA, "spikes A")
        self.CreateAndConnectConduitSpikeDetector(self.populationB, "spikes B")

        self.CreateAndConnectScreenMultimeter(self.populationA, "screen MM A")

    def CreateAndConnectConduitMultimeter(self, population, label):
        multimeter_conduit = nest.Create("multimeter",
                                         params={"interval": 0.1,
                                                 "record_from": ["V_m", "g_ex", "g_in"],
                                                 "record_to": ["stream"],
                                                 "label": label})
        nest.Connect(multimeter_conduit, population)

    def CreateAndConnectConduitSpikeDetector(self, population, label):
        spike_detector_conduit = nest.Create("spike_detector",
                                             params={"record_to": ["stream"],
                                                     "label": label})
        nest.Connect(population, spike_detector_conduit)

    def CreateAndConnectScreenMultimeter(self, population, label):
        multimeter_screen = nest.Create("multimeter",
                                        params={"interval": 0.1,
                                                "record_from": ["V_m", "g_ex", "g_in"],
                                                "record_to": ["screen"],
                                                "label": label})
        nest.Connect(multimeter_screen, population)

    def CreateAndConnectSpikeGenerators(self):
        self.CreateAndConnectExitatorySpikeGenerator()
        self.CreateAndConnectInhibitorySpikeGenerator()

    def CreateAndConnectExitatorySpikeGenerator(self):
        spikes_ex_params = {"spike_times": numpy.array([1.0, 5.0, 10.0, 15.0, 20.0, 50.0])}
        spikes_ex = nest.Create("spike_generator",
                                params=spikes_ex_params)
        nest.Connect(spikes_ex, self.populationA, syn_spec={"weight": 40.0})

    def CreateAndConnectInhibitorySpikeGenerator(self):
        spikes_in_params = {"spike_times": numpy.array([4.0, 8.0, 13.0, 18.0, 23.0, 53.0])}
        spikes_in = nest.Create("spike_generator",
                                params=spikes_in_params)
        nest.Connect(spikes_in, self.populationA, syn_spec={"weight": -20.0})

    def Simulate(self, time):
        nest.Simulate(time)


class MainWindow:
    def __init__(self):
        self.SetupWindow()
        self.simulation = Simulation()
        self.simulation.Simulate(0.2)

    def SetupWindow(self):
        self.simulate_button = QPushButton("nest.Simulate(20)")
        self.simulate_button.clicked.connect(self.SimulateButtonClicked)

    def SimulateButtonClicked(self):
        self.simulate_button.setEnabled(False)
        QApplication.processEvents()

        self.simulation.Simulate(20)

        QApplication.processEvents()
        self.simulate_button.setEnabled(True)

    def Show(self):
        self.simulate_button.show()


def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()

if __name__ == "__main__":
    main(sys.argv)
