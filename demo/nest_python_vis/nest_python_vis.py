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
        self.label = QLabel("V_m:")
        self.value = QLabel("{:0.3f} mV".format(0.0))

        self.start_button = QPushButton("Start")
        self.start_button.clicked.connect(self.StartButtonClicked)

        self.layout = QGridLayout()
        self.layout.addWidget(self.label, 0, 0)
        self.layout.addWidget(self.value, 0, 1)
 
        self.layout.addWidget(self.start_button, 1, 0, 1, 2)

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
        self.value.setText("{:0.3f} mV".format(self.receiver.Get("V_m")))
        self.value.update()
        self.window.update()

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
