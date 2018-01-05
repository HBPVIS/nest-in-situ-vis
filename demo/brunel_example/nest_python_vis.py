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
        
        self.multimeter = pyniv.ConsumerMultimeter("recordingNode51")
        self.multimeter.SetAttribute("V_m")

        self.backend = pyniv.AnalysisBackend();
        self.backend.Connect(self.receiver);
        self.backend.Connect(self.multimeter);

    def SetupWindow(self):
        self.visualize_button = QPushButton("Visualize")
        self.visualize_button.clicked.connect(self.VisualizeButtonClicked)

    def SetupUpdateTimer(self):
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.Visualize)

    def SetupPlot(self):
        sns.set_style("darkgrid")
        self.fig = plt.figure()
        self.ax1 = self.fig.add_subplot(1,1,1)


    def VisualizeButtonClicked(self):
        self.visualize_button.setEnabled(False)
        self.update_timer.start(0.5)
        self.Visualize()
        
    def Show(self):
        self.visualize_button.show()
        button_geometry = self.visualize_button.geometry()
        self.visualize_button.setGeometry(
            0, 0,
            button_geometry.width(),
            button_geometry.height())

    def Visualize(self):
        self.backend.Receive()
        plot_ts, plot_vs = self.GetValues(self.multimeter)
        self.Plot(plot_ts, plot_vs);

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
            plot_ts.append(t.tolist())
            plot_vs.append(vs.tolist())
        return plot_ts, plot_vs

    def Plot(self, ts, vs):
        values = []
        for i in range(0, 35):
            tmp = []
            for t in range(0, len(vs)):
                tmp.append(vs[t][i])
            values.append(tmp)
        
        self.ax1.clear()
        for i in range(0, len(values)):
            self.ax1.plot(ts, values[i])
        self.ax1.set_title("Brunel Example")
        self.ax1.set_xlabel("Time")
        self.ax1.set_ylabel("V_m")

        plt.show(block=False)
        self.fig.canvas.draw()
        

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
