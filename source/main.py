import sys
import os
import random
import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile
from PyQt4 import QtGui, QtCore

class Window(QtGui.QMainWindow):
	def __init__(self):
		self.name = ""
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

		self.encodeAction = QtGui.QAction("&Encode file", self)
		self.encodeAction.setShortcut("Ctrl+E")
		self.encodeAction.setStatusTip("Encode file.")
		self.encodeAction.triggered.connect(self.file_encode)
		self.encodeAction.setDisabled(True)

		self.decodeAction = QtGui.QAction("&Decode file", self)
		self.decodeAction.setShortcut("Ctrl+D")
		self.decodeAction.setStatusTip("Decode file.")
		self.decodeAction.triggered.connect(self.file_decode)
		self.decodeAction.setDisabled(True)

		self.statusBar()
		mainMenu = self.menuBar()
		fileMenu = mainMenu.addMenu("&File")
		fileMenu.addAction(openAction)
		fileMenu.addAction(extractAction)
		fileMenu.addAction(self.encodeAction)
		fileMenu.addAction(self.decodeAction)

		label = QtGui.QLabel(self)
		label.setFixedWidth(385)
		label.setFixedHeight(162)
		label.move(50,50)
		pixmap = QtGui.QPixmap("../resources/waver.png")
		label.setPixmap(pixmap)
		label.show()

		self.labeltxt = QtGui.QLabel(self)
		self.labeltxt.setText("No file opened.")
		self.labeltxt.setFixedWidth(1000)
		self.labeltxt.move(10,20)
		self.labeltxt.show()

		self.home()

	def file_decode(self):
		os.system("app.exe " + str(self.name) + " " + "-decode -o decoded.wav")

	def file_encode(self):
		os.system("app.exe " + str(self.name) + " " + "-encode -o encoded.wav")

	def file_open(self):
		self.name = QtGui.QFileDialog.getOpenFileName(self, "Open File")

		if str(self.name).endswith(".wav"):
			self.labeltxt.setText("File opened: " + str(self.name))
			self.labeltxt.show()
			self.decodeAction.setEnabled(True)
			self.encodeAction.setEnabled(True)

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