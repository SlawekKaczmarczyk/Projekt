from typing import List, Tuple

from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPainter, QBrush
from PyQt5.QtWidgets import QLabel, QMainWindow, QWidget


class GOLBoard(QWidget):
    """
    Widget displaying Game of Life board
    """

    def __init__(self, parent: QWidget):
        super().__init__(parent)
        self.cells = []
        self.scaling = 3
        self.cell_color = Qt.black

    def paintEvent(self, event):
        """
        Draw alive cells to the widgets, called at every update()
        """
        qp = QPainter()
        qp.begin(self)
        qp.setPen(self.cell_color)
        qp.setBrush(QBrush(self.cell_color, Qt.SolidPattern))
        for cell in self.cells:
            rect = map(lambda x: x * self.scaling, (*cell, 1, 1))
            qp.drawRect(*rect)

        qp.end()


class MainWindow(QMainWindow):
    def __init__(self, width: int, height: int, title: str):
        super().__init__()
        self.setWindowTitle(title)
        self.resize(width, height)

        self.text_label = QLabel(self)
        self.text_label.setText("Current generation: 0")
        self.text_label.resize(width, 30)
        self.text_label.move(0, 0)
        self.text_label.setStyleSheet("*{background-color: #383838; color: white;}")

        self.board = GOLBoard(self)
        self.board.resize(width, height - self.text_label.height())
        self.board.move(0, self.text_label.height())

    def set_generation_count(self, count):
        self.text_label.setText("Current generation: {count}")

    def set_alive_cells(self, cells: List[Tuple[int, int]]):
        self.board.cells = cells
