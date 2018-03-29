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
        self.SetupUpdateTimer()
        
    def SetupStreaming(self):
        self.receiver = pyniv.consumer.Receiver()
        
        self.multimeter = pyniv.consumer.NestMultimeter("recordingNode51")
        self.multimeter.SetAttribute("V_m")

        self.backend = pyniv.consumer.Backend();
        self.backend.Connect(self.receiver);
        self.backend.Connect(self.multimeter);

    def SetupWindow(self):
        self.print_button = QPushButton("Print")
        self.print_button.clicked.connect(self.PrintButtonClicked)

    def SetupUpdateTimer(self):
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.Receive)
        self.update_timer.start(1)

    def PrintButtonClicked(self):
        self.multimeter.Print()
        
    def Show(self):
        self.print_button.show()
        button_geometry = self.print_button.geometry()
        self.print_button.setGeometry(
            0, 0,
            button_geometry.width(),
            button_geometry.height())

    def Receive(self):
        self.backend.Receive()

    def Dump(self):
        print("DUMP")
        

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
