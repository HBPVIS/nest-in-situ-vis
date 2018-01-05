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
        self.receiver = pyniv.ConsumerReceiver()
        
        self.multimeter_a = pyniv.ConsumerMultimeter("multimeter A")
        self.multimeter_a.SetAttribute("V_m")

        self.multimeter_b = pyniv.ConsumerMultimeter("multimeter B")
        self.multimeter_b.SetAttribute("V_m")

        self.backend = pyniv.AnalysisBackend();
        self.backend.Connect(self.receiver);
        self.backend.Connect(self.multimeter_a);
        self.backend.Connect(self.multimeter_b);

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
        self.update_timer.start(0.5)
        self.Visualize()
        
    def Show(self):
        self.window.show()

    def Visualize(self):
        self.backend.Receive()
        plot_ts_a, plot_vs_a = self.GetValues(self.multimeter_a)
        plot_ts_b, plot_vs_b = self.GetValues(self.multimeter_b)
        self.Plot([[plot_ts_a, plot_vs_a], [plot_ts_b, plot_vs_b]]);

    def GetValues(self, multimeter):
        ts = multimeter.GetTimesteps()
        ts.sort()
        plot_ts = []
        plot_vs = []
        for t in ts:
          multimeter.SetTime(t)
          multimeter.Update()
          vs = multimeter.GetValues()
          if len(vs) > 0:
            plot_ts.append(t)
            plot_vs.append(vs[0])
        return plot_ts, plot_vs

    def Plot(self, values):
        self.ax1.clear()
        for [ts, vs] in values:
            self.ax1.plot(ts, vs)
        plt.show(block=False)
        self.fig.canvas.draw()
        

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
