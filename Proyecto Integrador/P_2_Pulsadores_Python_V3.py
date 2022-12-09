import serial as s
from pynput.keyboard import Key, Controller
from PyQt5 import QtCore, QtWidgets, uic
import sys

qtCreatorFile = "Gamepad_GUI.ui"
UiMainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

pulsadores = ["Key.up", "Key.down", "Key.right", "Key.left", "a", "s"]
keyboard = Controller()

class MyApp(QtWidgets.QMainWindow, UiMainWindow):

    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        UiMainWindow.__init__(self)
        self.setupUi(self)

        self.arduino = None

        self.btn_conectar.clicked.connect(self.conectar)
        self.btn_conectar.setText("CONECTAR")

        self.le_com.setFocus(True)

        self.segundoPlano = QtCore.QTimer()
        self.segundoPlano.timeout.connect(self.accion)

    def accion(self):

        valor = self.arduino.readline().decode()
        valor = valor.replace("\n", "")
        valor = valor.replace("\r", "")
        print(valor)

        if valor[0] == "r":
            bit_r = int(valor[1:])
            if bit_r == 0:
                keyboard.press(Key.right)
        if valor[0] == "l":
            bit_l = int(valor[1:])
            if bit_l == 0:
                keyboard.press(Key.left)

    def conectar(self):
        v = self.btn_conectar.text()
        if v == "CONECTAR":
            self.btn_conectar.setText("DESCONECTAR")

            if self.arduino is None:
                com = "COM" + self.le_com.text()
                self.arduino = s.Serial(com, baudrate=9600)
                self.lbl_estado.setText("INICIALIZADA")
                self.segundoPlano.start(1)

            elif not self.arduino.isOpen():
                self.arduino.open()
                self.lbl_estado.setText("REESTABLECIDA")
                self.segundoPlano.start(1)

        else:
            self.btn_conectar.setText("CONECTAR")
            self.arduino.close()
            self.lbl_estado.setText("CERRADA")
            self.segundoPlano.stop()


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())