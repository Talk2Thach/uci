#!/usr/bin/env python3

# Edward Xia - 73387315

import tkinter as tk
import math
import othello

class OthelloInitializer(tk.Frame):
    def __init__(self: object, master=None):
        """Init the class"""
        tk.Frame.__init__(self, master)

        self.master.wm_title("Othello")
        self.first = tk.IntVar()
        self.first.set(othello.Game.BLACK)
        self.rows = tk.IntVar()
        self.rows.set(8)
        self.columns = tk.IntVar()
        self.columns.set(8)
        self.piece_size = 40

        self.pack()
        self.createWidgets()
        self.setResizable(False)
        self.centerWindow()

    def setResizable(self: object, resizable=True):
        """Make the window resizable or not"""
        self.master.resizable(width=resizable, height=resizable)

    def centerWindow(self: object):
        """Center the window"""
        self.master.update()
        w = self.master.winfo_width()
        h = self.master.winfo_height()
        x = (self.master.winfo_screenwidth() - w) / 2
        y = (self.master.winfo_screenheight() - h) / 2
        self.master.geometry('%dx%d+%d+%d' % (w, h, x, y))

    def createWidgets(self: object):
        """Create the buttons"""
        size_option_frame = tk.Frame(self)
        rows_option_label = tk.Label(size_option_frame,
                text="Rows: ")
        rows_option_menu = tk.OptionMenu(size_option_frame,
                self.rows,
                4, 6, 8, 10, 12, 14, 16)
        columns_option_label = tk.Label(size_option_frame,
                text="Columns: ")
        columns_option_menu = tk.OptionMenu(size_option_frame,
                self.columns,
                4, 6, 8, 10, 12, 14, 16)

        rows_option_label.grid(row=0, sticky="W")
        columns_option_label.grid(row=1, sticky="W")
        rows_option_menu.grid(row=0, column=1)
        columns_option_menu.grid(row=1, column=1)

        first_option_frame = tk.Frame(self)
        black_first_button = tk.Radiobutton(first_option_frame,
                text="Black First",
                variable=self.first,
                value=othello.Game.BLACK)
        white_first_button = tk.Radiobutton(first_option_frame,
                text="White First",
                variable=self.first,
                value=othello.Game.WHITE)

        black_first_button.grid(row=0)
        white_first_button.grid(row=1)

        actions_frame = tk.Frame(self)
        start_button = tk.Button(actions_frame,
                text="Start",
                command=self.newGame)
        quit_button = tk.Button(actions_frame,
                text="Quit",
                command=self.master.destroy)
        start_button.grid(row=0, column=0, padx=10)
        quit_button.grid(row=0, column=1, padx=10)

        size_option_frame.grid(row=0, pady=5)
        first_option_frame.grid(row=1, pady=5)
        actions_frame.grid(row=2, pady=5)

    def newGame(self: object):
        """Create a new window for new game"""
        self.master.update()
        self.master.withdraw()

        def callback(options={}):
            """Callback function after a game window is closed"""
            self.master.update()
            self.master.deiconify()
            if "piece_size" in options:
                self.piece_size = options["piece_size"]

        Othello(master=tk.Toplevel(self.master),
                callback=callback,
                options={
                    "rows": self.rows.get(),
                    "columns": self.columns.get(),
                    "first": self.first.get(),
                    "piece_size": self.piece_size
                }).mainloop()

class Othello(tk.Frame):
    def __init__(self: object, master=None, callback=None, options={}):
        """Init the class"""
        tk.Frame.__init__(self, master)

        self.callback = callback
        self.options = options
        self.options["border"] = math.ceil(self.options["piece_size"] * .05)

        self.master.wm_protocol("WM_DELETE_WINDOW", self.closeWindow)
        self.master.config(padx=2, pady=2)

        self.game = othello.Game(options["rows"], options["columns"], options["first"])
        self.status()

        self.pack()

        self.setResizable(False)
        minborder = math.ceil(20 * .05)
        self.master.minsize(self.size(self.options["columns"], 20, minborder), self.size(self.options["rows"], 20, minborder))
        maxborder = math.ceil(80 * .05)
        self.master.maxsize(self.size(self.options["columns"], 80, maxborder), self.size(self.options["rows"], 80, maxborder))
        self.master.aspect(options["columns"], options["rows"], options["columns"], options["rows"])
        self.setResizable(True)
        self.resizeAndCenterWindow(self.width(), self.height())

        self.canvas = tk.Canvas(self, highlightthickness=0, width=self.width(), height=self.height())
        self.canvas.pack(expand=True, fill=tk.BOTH)
        self.redrawCanvas()

        self.master.bind("<Configure>", self.onResize)

    def _print_name(self: object, color: int):
        """Return the print name for a color"""
        if color == othello.Game.WHITE:
            return "White"
        if color == othello.Game.BLACK:
            return "Black"

    def status(self: object):
        """Set the statusline"""
        statusline = "%s - %s (%d) vs %s (%d) - Othello"
        first = self.options["first"]
        second = self.game._inverse_color(first)
        score = self.game.score()

        if self.game.turn == self.game.EMPTY:
            winner = self.game.winner()
            if winner == self.game.EMPTY:
                self.master.wm_title(statusline % ("Draw!", self._print_name(first), score[first], self._print_name(second), score[second]))
            else:
                self.master.wm_title(statusline % ("%s Wins!" % self._print_name(winner), self._print_name(first), score[first], self._print_name(second), score[second]))
        else:
            self.master.wm_title(statusline % ("%s's Turn" % self._print_name(self.game.turn), self._print_name(first), score[first], self._print_name(second), score[second]))

    def size(self: object, pieces: int, piece_size: int, border: int) -> int:
        """Return the minium size for current setting"""
        return pieces * piece_size + (pieces + 1) * border

    def width(self: object) -> int:
        """Return the minium width for current setting"""
        return self.size(self.options["columns"], self.options["piece_size"], self.options["border"])

    def height(self: object) -> int:
        """Return the minium height for current setting"""
        return self.size(self.options["rows"], self.options["piece_size"], self.options["border"])

    def setResizable(self: object, resizable=True):
        """Make the window resizable or not"""
        self.master.resizable(width=resizable, height=resizable)

    def onResize(self: object, event: object):
        """Callback funtion on resize the window"""
        self.canvas.delete("all")
        self.canvas.config(width=self.master.winfo_width(), height=self.master.winfo_height())
        self.options["piece_size"] = math.floor(min(self.canvas.winfo_width() // self.options["columns"], self.canvas.winfo_height() // self.options["rows"]) / 1.05)
        self.options["border"] = math.ceil(self.options["piece_size"] * .05)
        while self.width() > self.canvas.winfo_width() or self.height() > self.canvas.winfo_height():
            self.options["piece_size"] -= 1
            self.options["border"] = math.ceil(self.options["piece_size"] * .05)
        self.redrawCanvas()

    def resizeAndCenterWindow(self: object, w: int, h: int):
        """Resize and center current window"""
        x = (self.master.winfo_screenwidth() - w) / 2
        y = (self.master.winfo_screenheight() - h) / 2
        self.master.geometry('%dx%d+%d+%d' % (w, h, x, y))

    def centerWindow(self: object):
        """Center current window"""
        self.master.update()
        w = self.master.winfo_width()
        h = self.master.winfo_height()
        x = (self.master.winfo_screenwidth() - w) / 2
        y = (self.master.winfo_screenheight() - h) / 2
        self.master.geometry('%dx%d+%d+%d' % (w, h, x, y))

    def closeWindow(self: object):
        """Handle closeWindow event and run the callback function"""
        self.master.destroy()
        self.callback(self.options)

    def onClick(self: object, event: object):
        """Handle the click event"""
        r = event.x // (self.options["piece_size"] + self.options["border"]) + 1
        c = event.y // (self.options["piece_size"] + self.options["border"]) + 1
        try:
            self.game.move(r, c)
            self.redrawCanvas()
            self.status()
        except:
            pass

    def redrawCanvas(self: object):
        """Refresh the canvas"""
        self.canvas.delete("all")

        backgroud = self.canvas.create_rectangle(0, 0, self.size(self.options["columns"], self.options["piece_size"], self.options["border"]), self.size(self.options["rows"], self.options["piece_size"], self.options["border"]), fill="#3E910F")
        self.canvas.tag_bind(backgroud, "<Button-1>", self.onClick)

        for i in range(self.options["columns"] + 1):
            x = i * (self.options["piece_size"] + self.options["border"])
            y = self.size(self.options["rows"], self.options["piece_size"], self.options["border"])
            self.canvas.create_rectangle(x, 0, x + self.options["border"], y, fill="black")
        for i in range(self.options["rows"] + 1):
            y = i * (self.options["piece_size"] + self.options["border"])
            x = self.size(self.options["columns"], self.options["piece_size"], self.options["border"])
            self.canvas.create_rectangle(0, y, x, y + self.options["border"], fill="black")

        for r in range(self.game.rows_num):
            for c in range(self.game.columns_num):
                self.drawPiece(c, r, self.game._get(c + 1, r + 1))

    def drawPiece(self: object, x_id: int, y_id: int, color_id: int):
        """Draw a piece on canvas"""
        if color_id == othello.Game.EMPTY:
            return
        elif color_id == othello.Game.BLACK:
            color="black"
        elif color_id == othello.Game.WHITE:
            color="white"
        self.canvas.create_oval(
                x_id * self.options["piece_size"] + (x_id + 2) * self.options["border"],
                y_id * self.options["piece_size"] + (y_id + 2) * self.options["border"],
                (x_id + 1) * self.options["piece_size"] + x_id * self.options["border"],
                (y_id + 1) * self.options["piece_size"] + y_id * self.options["border"],
                fill=color,
                outline=color)

if __name__ == "__main__":
    OthelloInitializer(master=tk.Tk()).mainloop()
