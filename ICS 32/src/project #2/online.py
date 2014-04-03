#!/usr/bin/env python3

# Edward Xia - 73387315
# Jose Luis Vargas - 57291630

import connectfour
import socket

class ConnectFourGameOnline:
    def __init__(self: object):
        """Init new game"""

        connected = False
        while not connected:
            # test server infomation:
            """
            host = "woodhouse.ics.uci.edu"
            port = 4444
            """

            host = input("Please input the server address: ").strip()
            port = self._get_int("Please input the server port: ")
            self.user = "".join(input("Please input you name: ").split())
            self.server = (host, port)

            try:
                self.connect()
                connected = True
            except:
                print("Failed to connect to server. Please try again.")
                self.disconnect()

        self._send("AI_GAME")
        self.state = connectfour.new_game_state()
        print()
        print("You are RED (R).")

        while True:
            message = self._recieve()
            if message == "READY":
                self.print_state()
                pending_action = self._get_input()
                if pending_action["action"] == "d":
                    self._send("DROP %d" % pending_action["column_number"])
                elif pending_action["action"] == "p":
                    self._send("POP %d" % pending_action["column_number"])
            elif message == "OKAY" or message == "WINNER_RED" or message == "WINNER_YELLOW":
                if pending_action != None:
                    if pending_action["action"] == "d":
                        self.state = connectfour.drop_piece(self.state, pending_action["column_number"] - 1)
                    elif pending_action["action"] == "p":
                        self.state = connectfour.pop_piece(self.state, pending_action["column_number"] - 1)
                    pending_action = None
            elif message == "INVALID":
                print("Invaild move!")
            elif message[0:4] == "DROP" or message[0:3] == "POP":
                try:
                    if message[0:4] == "DROP":
                        self.state = connectfour.drop_piece(self.state, int(message[4:].strip()) - 1)
                    elif message[0:3] == "POP":
                        self.state = connectfour.pop_piece(self.state, int(message[3:].strip()) - 1)
                except:
                    print("Server made a funny move.")
                    break
            else:
                print("Server sent an unknown command.")
                break

            if message == "WINNER_RED":
                self.print_state()
                print("You win!")
                break
            elif message == "WINNER_YELLOW":
                self.print_state()
                print("AI wins!")
                break

        self.disconnect()

    def connect(self: object):
        """Try to connect to the server"""
        print("Connecting...")
        self.so = socket.socket()
        self.so.connect(self.server)
        self.so_in = self.so.makefile("r")
        self.so_out = self.so.makefile("w")
        self._send("I32CFSP_HELLO %s" % self.user)
        if self._recieve() == "WELCOME %s" % self.user:
            print("Connected.")
        else:
            raise Exception

    def disconnect(self: object):
        """Disconnect from the server"""
        for i in ["so_out", "so_in", "so"]:
            if hasattr(self, i):
                getattr(self, i).close()

    def _send(self: object, message: str):
        """Send a message to server"""
        self.so_out.write("%s\r\n" % message)
        self.so_out.flush()

    def _recieve(self: object) -> str:
        """Recieve a message from server"""
        return self.so_in.readline().rstrip("\n").rstrip("\r")

    def print_state(self: object):
        """Print game state"""
        print()
        line = ""
        for j in range(connectfour.BOARD_COLUMNS):
            line += " %d " % (j + 1)
        print(line)
        for j in range(connectfour.BOARD_ROWS):
            line = ""
            for i in range(connectfour.BOARD_COLUMNS):
                piece = self.state.board[i][j]
                if piece == connectfour.NONE:
                    piece = "."
                line += " %s " % piece
            print(line)
        print()

    def _get_input(self: object) -> dict:
        """Get the user action"""
        action = input("Drop or Pop (d/p)? ").strip().lower()
        while action not in ["d", "p"]:
            print("Invaild input.")
            action = input("Drop or Pop (d/p)? ").strip().lower()
        return { "action": action,
                 "column_number": self._get_int("Please input the column number: ") }

    def _get_int(self: object, message="Please input a number: ") -> int:
        """Get an integer"""
        valid = False
        while not valid:
            try:
                number = int(input(message))
                valid = True
            except:
                print("Invaild input. Please try again.")
        return number

if __name__ == "__main__":
    ConnectFourGameOnline()

