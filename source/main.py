import sys
import os
import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile
from PyQt4 import QtGui, QtCore

class Window(QtGui.QMainWindow):
	def __init__(self):
		super(Window, self).__init__()
		self.setGeometry(100, 100, 500, 300)
		self.setWindowTitle("WAVER")

		extractAction = QtGui.QAction("&Exit", self)
		extractAction.setShortcut("Ctrl+Q")
		extractAction.setStatusTip("Leave the app.")
		extractAction.triggered.connect(self.close_app)

		openAction = QtGui.QAction("&Open file", self)
		openAction.setShortcut("Ctrl+O")
		openAction.setStatusTip("Open a WAV file.")
		openAction.triggered.connect(self.file_open)

		self.statusBar()
		mainMenu = self.menuBar()
		fileMenu = mainMenu.addMenu("&File")
		fileMenu.addAction(openAction)
		fileMenu.addAction(extractAction)

		label = QtGui.QLabel(self)
		label.setFixedWidth(385)
		label.setFixedHeight(162)
		label.move(50,50)
		pixmap = QtGui.QPixmap("../resources/waver.png")
		label.setPixmap(pixmap)
		label.show()

		self.home()

	def file_open(self):
		name = QtGui.QFileDialog.getOpenFileName(self, "Open File")
		if str(name).endswith(".wav"):
			#file = open(name, 'r')
			fs, data = wavfile.read(str(name))
			a = data.T[0]
			b = [(ele/2**8.)*2-1 for ele in a]
			c = fft(b)
			d = len(c)/2
			plt.plot(abs(c[:(d-1)]),'r')
			plt.show()
			os.system("../bin/app " + str(name))
			QtGui.QMessageBox.information(self, "SUCCESS!", "You can find all info in terminal or /tmp/info.dat")
		else:
			QtGui.QMessageBox.warning(self, "Warning!", "You can open only WAV files.")

	def home(self):
		btn = QtGui.QPushButton("Quit", self)
		btn.clicked.connect(self.close_app)
		btn.resize(btn.sizeHint())
		btn.move(self.frameGeometry().width()-btn.frameGeometry().width(),self.frameGeometry().height()-btn.frameGeometry().height())
		
		self.show()

	def close_app(self):
		choice = QtGui.QMessageBox.question(self, "Extract", "Do You really want to Quit?", QtGui.QMessageBox.Yes | QtGui.QMessageBox.No)
		if choice == QtGui.QMessageBox.Yes:
			sys.exit()
		else:
			pass

def run():
	app = QtGui.QApplication(sys.argv)
	GUI = Window()
	sys.exit(app.exec_())

run()


# app = QtGui.QApplication(sys.argv)
# window = QtGui.QWidget()
# window.resize(400, 200)
# window.setWindowTitle("WAVER")

# window.show()

# sys.exit(app.exec_())