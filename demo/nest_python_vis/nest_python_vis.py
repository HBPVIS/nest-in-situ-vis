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

import pyniv

from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout, QPushButton
from PyQt5.QtCore import QTimer

class MainWindow:
    def __init__(self):
        self.receiver = pyniv.SynchronizedReceiver()
        self.SetupWindow()

    def SetupWindow(self):
        self.visualize_button = QPushButton("Visualize")
        self.visualize_button.clicked.connect(self.VisualizeButtonClicked)

        self.layout = QGridLayout()
 
        self.layout.addWidget(self.visualize_button, 0, 0, 1, 1)

        self.window = QWidget()
        self.window.setLayout(self.layout)
        self.window.show()

    def VisualizeButtonClicked(self):
        data = self.receiver.Receive()
        data.Print()

    def Show(self):
        self.window.show()

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
