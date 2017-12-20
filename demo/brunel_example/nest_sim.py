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

import sys
import nest
import numpy

from PyQt5.QtWidgets import QApplication, QPushButton
from PyQt5.QtCore import QTimer

import brunel_example

class Simulation:
    def __init__(self):
        self.SetupSim()
        
    def SetupSim(self):
        nest.ResetKernel()
        
        print('Making specifications')
        self.brunel = brunel_example.Brunel3D()
        self.brunel.make_layer_specs()
        self.brunel.make_connection_specs()

        print('Making layers')
        self.brunel.make_layers()
        nest.topology.DumpLayerNodes([l[0] for l in self.brunel.layer_dict.values()][:2],
                                     'brunel_nodes.txt')

        print('Making connections')
        self.brunel.make_connections()

    def Simulate(self, steps):
        nest.Simulate(steps)


class MainWindow:
    def __init__(self, screen_resolution):
        self.screen_resolution = screen_resolution
        self.SetupWindow()
        self.simulation = Simulation()

    def SetupWindow(self):
        self.simulate_button = QPushButton("nest.Simulate(1000)")
        self.simulate_button.clicked.connect(self.SimulateButtonClicked)

    def SimulateButtonClicked(self):
        self.simulate_button.setEnabled(False)
        QApplication.processEvents()

        self.simulation.Simulate(1000)

        QApplication.processEvents()
        self.simulate_button.setEnabled(True)

    def Show(self):
        self.simulate_button.show()
        button_geometry = self.simulate_button.geometry()
        self.simulate_button.setGeometry(
            self.screen_resolution.width() - button_geometry.width(),
            self.screen_resolution.height() - button_geometry.height(),
            button_geometry.width(),
            button_geometry.height())


def main(argv):
    app = QApplication(argv)
    screen_resolution = app.desktop().screenGeometry()

    w = MainWindow(screen_resolution)
    w.Show()

    return app.exec_()

if __name__ == "__main__":
    main(sys.argv)
