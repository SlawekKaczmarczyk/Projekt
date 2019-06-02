import socket
import json
import struct
import os
from threading import Thread

from typing import List, Tuple, Dict


class Connection:
    def __init__(self, port: int, server_path: str):
        self.port = port
        self.socket = None
        self.connection = None
        self.server_addr = None
        self.server_path = server_path

    def connect(self, board_width=500, board_height=280, delay=1):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind(("localhost", self.port))
        self.socket.listen()
        # TODO: Start server
        print("Waiting for server...")
        cmd = '{} {} {} {} {}'.format(self.server_path, board_width, board_height, delay, self.port)
        server_thread = Thread(target=os.system, args=(cmd,))
        server_thread.start()
        self.connection, self.server_addr = self.socket.accept()

    def send_command(self, cmd: Dict[str, str]):
        data = json.dumps(cmd).encode()
        # send size of data
        size_bytes = struct.pack("Q", len(data))
        self.connection.sendall(size_bytes)
        # send command data
        self.connection.sendall(data)

    def receive_data(self) -> bytes:
        size_bytes = self.connection.recv(8)
        size = struct.unpack("Q", size_bytes)[0]
        data = b''
        while len(data) < size:
            data += self.connection.recv(size - len(data))
        return data

    def get_stats(self) -> dict:
        self.send_command({"cmd": "stats"})
        data = self.receive_data()
        return json.loads(data.decode())

    def get_alive_cells(self) -> List[Tuple[int, int]]:
        result = []
        self.send_command({"cmd": "data"})
        data = self.receive_data()
        # parse bytes as (uint32_t, uint32_t) array
        for i in range(len(data) // 8):
            result.append(struct.unpack("II", data[i * 8:(i + 1) * 8]))
        return result
