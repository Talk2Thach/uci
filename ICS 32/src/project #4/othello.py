#!/usr/bin/env python3

# Edward Xia - 73387315

class InvalidMoveError(Exception):
    pass

class Game:

    # set colors as constant integer to save memory
    WHITE = 1
    BLACK = -1
    EMPTY = 0

    def __init__(self: object, rows_num: int, columns_num: int, first_move_color: int):
        """Init the class"""
        # assume rows & columns are even number and >= 4
        columns = []
        for i in range(rows_num):
            row = []
            for j in range(columns_num):
                row.append(self.EMPTY)
            columns.append(row)

        self.rows_num = rows_num
        self.columns_num = columns_num
        self.turn = first_move_color
        self.board = columns

        # Initialize first 4 pieces, minimized algorithm
        for x in [0, 1]:
            for y in [0, 1]:
                self._set(int(columns_num / 2 + x), int(rows_num / 2 + y), self.WHITE if x == y else self.BLACK)

    def _is_in_board(self: object, x: int, y: int):
        """Check if a piece is in board"""
        return 1 <= y <= self.rows_num and 1 <= x <= self.columns_num

    def _get(self: object, x: int, y: int) -> bool:
        """Get the piece in a position"""
        return self.board[y - 1][x - 1]

    def _set(self: object, x: int, y: int, color: int):
        """Set the piece in a position"""
        self.board[y - 1][x - 1] = color

    def _inverse_color(self: object, color: int):
        """Quick hack for inverse color by inverse the integer constant"""
        return -color

    def _can_move(self: object) -> bool:
        """Check if a player can still move"""
        for y in range(1, self.rows_num + 1):
            for x in range(1, self.columns_num + 1):
                try:
                    self.move(x, y, perform_action=False)
                    return True
                except:
                    pass
        return False

    def _next(self: object):
        """Switch to next turn"""
        self.turn = self._inverse_color(self.turn)
        if not self._can_move():
            self.turn = self._inverse_color(self.turn)
            if not self._can_move():
                self.turn =  self.EMPTY # Game Ended

    def _serialized_board(self: object) -> []:
        """Convert the board to a list for counting score"""
        result = []
        for i in self.board:
            result.extend(i)
        return result

    def score(self: object) -> {}:
        """Count the score"""
        serialized_board = self._serialized_board()
        return {
                self.WHITE: serialized_board.count(self.WHITE),
                self.BLACK: serialized_board.count(self.BLACK)
                }

    def winner(self: object) -> int:
        """Check the winner"""
        if self.turn == self.EMPTY:
            score = self.score()
            if score[self.WHITE] > score[self.BLACK]:
                return self.WHITE
            elif score[self.WHITE] < score[self.BLACK]:
                return self.BLACK
        return self.EMPTY

    def move(self: object, x: int, y: int, perform_action = True): # We can use this function to test any move by set perform = False
        """Perform a move or test a move"""
        valid = False

        if not self._is_in_board(x, y):
            raise InvalidMoveError
        if self._get(x, y) != self.EMPTY:
            raise InvalidMoveError

        for x_direction in [1, 0, -1]:
            for y_direction in [1, 0, -1]:
                if not (x_direction == 0 and y_direction == 0):
                    _x = x
                    _y = y
                    reverse_list = []
                    while self._is_in_board(_x, _y):
                        _x += x_direction
                        _y += y_direction
                        if not self._is_in_board(_x, _y):
                            break
                        if self._get(_x, _y) == self.EMPTY:
                            break
                        if self._get(_x, _y) == self.turn:
                            if len(reverse_list) >= 1:
                                valid = True
                                if perform_action:
                                    for coordinate in reverse_list:
                                        self._set(coordinate[0], coordinate[1], self.turn)
                            break
                            # When no oppisite in the middle (reverse_list is empty), break
                            # Or reverse then break
                        reverse_list.append( (_x, _y) )
                if (not perform_action) and valid:
                    break
            if (not perform_action) and valid:
                break
        if not valid:
            raise InvalidMoveError
        else:
            if perform_action:
                self._set(x, y, self.turn)
                self._next()
