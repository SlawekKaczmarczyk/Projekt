import sys
import threading
from random import randint
from time import sleep

from connection import Connection
from display import MainWindow
from PyQt5.QtWidgets import QApplication

PORT = 12345
SERVER_PATH = '../server/cmake-build-debug/server'


class Client:
    UPDATE_DELAY = 0.02  # in seconds

    def __init__(self):
        self.connection = Connection(PORT, SERVER_PATH)
        self.connection.connect()
        self.app = QApplication([])
        self.window = MainWindow(1500, 810, "Game of Life [float]")
        self.running = False

    def run(self):
        """
        Launch GUI and run server connection thread
        """
        self.window.show()
        self.running = True
        thread = threading.Thread(target=self.update)
        thread.start()
        self.app.exec()
        self.running = False

    def update(self):
        """
        Set data from server to main window every UPDATE_DELAY seconds
        Has to be run in separate thread
        """
        while self.running:
            self.window.set_alive_cells(self.connection.get_alive_cells())
            stats = self.connection.get_stats()
            self.window.set_generation_count(stats['generation'])
            self.window.update()
            # sleep(Client.UPDATE_DELAY)
        print("Update thread closing")

    def draw(self):
        data = self.connection.get_alive_cells()


if __name__ == "__main__":
    Client().run()
