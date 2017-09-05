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
        self.receiver = pyniv.ConduitReceiver()
        self.SetupWindow()
        self.SetupUpdateTimer()
        

    def SetupWindow(self):
        self.label_V_m = QLabel("V_m:")
        self.value_V_m = QLabel("{:0.3f} mV".format(0.0))

        self.label_g_ex = QLabel("g_ex:")
        self.value_g_ex = QLabel("{:0.3f}".format(0.0))

        self.label_g_in = QLabel("g_ex:")
        self.value_g_in = QLabel("{:0.3f}".format(0.0))

        self.start_button = QPushButton("Start")
        self.start_button.clicked.connect(self.StartButtonClicked)

        self.layout = QGridLayout()
        self.layout.addWidget(self.label_V_m, 0, 0)
        self.layout.addWidget(self.value_V_m, 0, 1)
        self.layout.addWidget(self.label_g_ex, 1, 0)
        self.layout.addWidget(self.value_g_ex, 1, 1)
        self.layout.addWidget(self.label_g_in, 2, 0)
        self.layout.addWidget(self.value_g_in, 2, 1)
 
        self.layout.addWidget(self.start_button, 3, 0, 1, 2)

        self.window = QWidget()
        self.window.setLayout(self.layout)
        self.window.show()

    def SetupUpdateTimer(self):
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.UpdateValue)


    def StartButtonClicked(self):
        self.start_button.setEnabled(False)
        self.receiver.Start()
        self.update_timer.start(0.01)
        self.UpdateValue()

    def Show(self):
        self.window.show()

    def UpdateValue(self):
        self.value_V_m.setText("{:0.3f} mV".format(self.receiver.Get("V_m")))
        self.value_g_ex.setText("{:0.3f}".format(self.receiver.Get("g_ex")))
        self.value_g_in.setText("{:0.3f}".format(self.receiver.Get("g_in")))

        self.value_V_m.update()
        self.window.update()

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
