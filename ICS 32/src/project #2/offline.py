#!/usr/bin/env python3

# Edward Xia - 73387315
# Jose Luis Vargas - 57291630

import connectfour

class ConnectFourGame:
    def __init__(self: object):
        """Init new game"""

        self.state = connectfour.new_game_state()

        while True:
            self.print_state()

            winner = connectfour.winning_player(self.state)
            if winner != connectfour.NONE:
                if winner == connectfour.RED:
                    print("Red is the winner!")
                elif winner == connectfour.YELLOW:
                    print("Yellow is the winner!")
                break


            input_is_vaild = False
            while not input_is_vaild:
                action = self._get_input()
                try:
                    if action["action"] == "d":
                        self.state = connectfour.drop_piece(self.state, action["column_number"] - 1)
                    elif action["action"] == "p":
                        self.state = connectfour.pop_piece(self.state, action["column_number"] - 1)
                    else:
                        raise connectfour.InvalidConnectFourMoveError()
                    input_is_vaild = True
                except:
                    print("Sorry, invalid move.")

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

        if self.state.turn == connectfour.RED:
            print("Red's turn.")
        elif self.state.turn == connectfour.YELLOW:
            print("Yellow's turn.")
        print()

    def _get_input(self: object) -> dict:
        """Get the user action for drop / pop / column number"""

        action = input("Drop or Pop (d/p)? ").strip().lower()
        while action not in ["d", "p"]:
            print("Invaild input.")
            action = input("Drop or Pop (d/p)? ").strip().lower()
        return { "action": action,
                 "column_number": self._get_int("Please input the column number: ") }

    def _get_int(self: object, message="Please input a number: ") -> int:
        """Get a integer from user input"""
        valid = False
        while not valid:
            try:
                number = int(input(message))
                valid = True
            except:
                print("Invaild input. Please try again.")
        return number

if __name__ == "__main__":
    ConnectFourGame()

