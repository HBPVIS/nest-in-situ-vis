import sys

import pyniv

from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout, QPushButton

class MainWindow:
    def __init__(self):
        self.receiver = pyniv.ConduitReceiver()
        self.SetupWindow()

    def SetupWindow(self):
        self.label = QLabel("V_m:")
        self.value = QLabel("0.0")

        self.start_button = QPushButton("Start")
        self.start_button.clicked.connect(self.StartButtonClicked)

        self.layout = QGridLayout()
        self.layout.addWidget(self.label, 0, 0)
        self.layout.addWidget(self.value, 0, 1)
 
        self.layout.addWidget(self.start_button, 1, 0, 1, 2)

        self.window = QWidget()
        self.window.setLayout(self.layout)
        self.window.show()

    def StartButtonClicked(self):
        self.start_button.setEnabled(False)
        self.receiver.Start()
        self.UpdateValue()

    def Show(self):
        self.window.show()

    def UpdateValue(self):
        pass

def main(argv):
    app = QApplication(argv)

    w = MainWindow()
    w.Show()

    return app.exec_()
    
if __name__ == "__main__":
    main(sys.argv)
