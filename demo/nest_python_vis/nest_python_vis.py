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

import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

import pyniv

from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout, QPushButton
from PyQt5.QtCore import QTimer

class MainWindow:
    def __init__(self):
        self.SetupStreaming()
        self.SetupWindow()
        self.SetupPlot()
        self.SetupUpdateTimer()
        
    def SetupStreaming(self):
        self.receiver = pyniv.consumer.Receiver()

        self.multimeters = [pyniv.consumer.NestMultimeter("multimeter A"),
                            pyniv.consumer.NestMultimeter("multimeter B")]

        self.backend = pyniv.consumer.Backend();
        self.backend.Connect(self.receiver);
        for multimeter in self.multimeters:
            self.backend.Connect(multimeter);

    def SetupWindow(self):
        self.visualize_button = QPushButton("Visualize")
        self.visualize_button.clicked.connect(self.VisualizeButtonClicked)

        self.layout = QGridLayout()
 
        self.layout.addWidget(self.visualize_button, 0, 0, 1, 1)

        self.window = QWidget()
        self.window.setLayout(self.layout)
        self.window.show()

    def SetupUpdateTimer(self):
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.Visualize)

    def SetupPlot(self):
        self.fig = plt.figure()
        self.ax1 = self.fig.add_subplot(1,1,1)

    def VisualizeButtonClicked(self):
        self.visualize_button.setEnabled(False)
        self.update_timer.start(250)
        self.Visualize()
        
    def Show(self):
        self.window.show()

    def Visualize(self):
        self.backend.Receive()
        self.Plot();

    def Plot(self):
        self.ax1.clear()

        for multimeter in self.multimeters:
            self.MultimeterPlot(multimeter)

        plt.show(block=False)
        self.fig.canvas.draw()

    def MultimeterPlot(self, multimeter):
        timesteps = multimeter.GetTimestepsString()
        attribute = 'V_m'
        neuron_ids = []
        if len(timesteps) > 0:
            neuron_ids = multimeter.GetNeuronIds(timesteps[0], attribute)

        for neuron_id in neuron_ids:
            values = multimeter.GetTimeSeriesData(attribute, neuron_id)
            times = [float(t) for t in timesteps]
            self.ax1.plot(times, values)

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
