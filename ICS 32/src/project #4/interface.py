#!/usr/bin/env python3

# Edward Xia - 73387315

import othello

class OthelloInterface:
    def __init__(self: object):
        """Init the class"""
        size = self._get_board_size()
        first = self._get_first_move()
        if first == "black":
            self.first = othello.Game.BLACK
        elif first == "white":
            self.first = othello.Game.WHITE
        self.game = othello.Game(size, size, self.first)

        while True:
            self.print_board()
            self.print_score()

            if self.game.turn == othello.Game.EMPTY: # no next turn
                winner = self.game.winner()
                if winner == othello.Game.EMPTY:
                    print("Draw!")
                    break
                print("{:s} is the winner!".format(self._print_name(winner)))
                break

            print("{:s}'s move".format(self._print_name(self.game.turn)))
            move = self._get_move()
            self.game.move(move[0], move[1])

    def _get_move(self: object) -> (int, int):
        """Get the move from user"""
        while True:
            try:
                coordinate = input("Please input the coordinate (e.g 1a, 2b, ...): ").strip().lower()
                if len(coordinate) > 3:
                    raise
                else:
                    x = "abcdefghijklmnop".find(coordinate[-1]) + 1
                    y = int(coordinate[:-1])
                    if x == 0:
                        raise
                    self.game.move(x, y, perform_action=False)
                    return (x,y)
            except:
                print("Sorry, invalid move...")

    def _print_name(self: object, color: int):
        """return the print name for color"""
        if color == othello.Game.WHITE:
            return "White"
        if color == othello.Game.BLACK:
            return "Black"

    def _print_char(self: object, color: int):
        """return the print character for color"""
        if color == othello.Game.EMPTY:
            return " "
        if color == othello.Game.WHITE:
            return "W"
        if color == othello.Game.BLACK:
            return "B"

    def print_board(self: object):
        """Print out the game board"""
        result = ("{:" + str(len(str(self.game.columns_num))) + "} ").format("")
        for x in range(self.game.rows_num):
            result += ("{:" + str(len(str(self.game.rows_num))) + "} ").format(x + 1)
        result += "\n"
        for y in range(self.game.columns_num):
            result += ("{:" + str(len(str(self.game.columns_num))) + "} ").format("abcdefghijklmnop"[y])
            for x in range(self.game.rows_num):
                result += ("{:" + str(len(str(self.game.rows_num))) + "} ").format(self._print_char(self.game.board[x][y]))
            result += ("{:" + str(len(str(self.game.columns_num))) + "} ").format("abcdefghijklmnop"[y])
            result += "\n"
        result += ("{:" + str(len(str(self.game.columns_num))) + "} ").format("")
        for x in range(self.game.rows_num):
            result += ("{:" + str(len(str(self.game.rows_num))) + "} ").format(x + 1)
        result += "\n"
        result += "\n"
        print(result)

    def print_score(self: object):
        """Print out the score"""
        score = self.game.score()
        black = "{}: {}".format(self._print_name(othello.Game.BLACK), score[othello.Game.BLACK])
        white = "{}: {}".format(self._print_name(othello.Game.WHITE), score[othello.Game.WHITE])
        if self.first == othello.Game.BLACK:
            print("{} vs {}".format(black, white))
        elif self.first == othello.Game.WHITE:
            print("{} vs {}".format(white, black))

    def _get_board_size(self: object) -> int:
        """Let user input the board size"""
        valid = False
        while not valid:
            try:
                size = int(input("Please input the board size (even interger between 4 - 16): "))
                if (size % 2 != 0 or size < 4 or size > 16):
                    raise
                valid = True
            except:
                print("Invaild size. Please try again.")
        return size

    def _get_first_move(self: object) -> str:
        """Let the use pick who will move first"""
        first = input("Please input who move first (black or white): ").strip().lower()
        while first not in ["black", "white"]:
            print("Invaild input. Please try again.")
            first = input("Please input who move first (black or white): ").strip().lower()
        return first

if __name__ == "__main__":
    OthelloInterface()

