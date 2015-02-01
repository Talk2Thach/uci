// Editor.hpp
//
// ICS 45C Fall 2014
// Project #4: People Just Love to Play with Words
//
// The Editor class implements the "model" of BooEdit.  In other words, its
// job is to maintain the underlying data -- the current lines of text, where
// the cursor is supposed to be, etc. -- providing operations that allow the
// EditorView to access that data and also providing basic operations that
// allow the various Command objects to make necessary changes.
//
// The member functions already declared in the Editor class are absolutely
// necessary for EditorView to work, so they cannot be removed or have their
// declarations changed (though you may need to implement them; see
// Editor.cpp).
//
// You will absolutely need to implement additional member functions, because I
// haven't declared any functions that change the editor's data (e.g.,
// inserting characters, moving the cursor), which you'll need in order to
// implement the various Command objects.  You may also need additional member
// functions that access the editor's data in ways not provided here.
//
// When adding member functions, focus on adding "primitive" tools that you
// might be able to use in multiple command implementations, as opposed to
// just writing a member function for each commmand.
//
// The Editor class is unaware of the concept of "undo"; it is the job of the
// Command objects to know what they need to do in order to undo a Command.
//
// Note that the notion of "line number" and "column number" here is one-based,
// not zero-based, which means that the top left corner of the file is line 1
// column 1.  You can handle this however you'd like inside of your class, but
// the rest of BooEdit expects Editor objects to take and return one-based
// line and column numbers.

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <vector>


struct Line {
    std::string text;
    Line *next;
};

class Editor
{
public:
    // Initializes the editor.  Initially, the cursor is on line 1 column 1
    // and there is one empty line of text in the editor.
    Editor();
    // Returns the line number where the cursor currently should reside.
    int cursorLine() const;

    // Returns the column number where the cursor currently should reside.
    int cursorColumn() const;

    // Returns the number of lines of text currently in the editor.
    int lineCount() const;

    // Returns the text on the given line number.
    const std::string& line(int lineNumber) const;

    void moveCursorColumnTo(int x);
    void moveCursorLineTo(int y);
    void moveCursorTo(int x, int y);

    void insertCharactorUnderCursor(char &charactor);
    void insertNewLineUnderCursor();
    void insertLine(std::string &str, int &lineNumber);
    void replaceLine(std::string &str, int &lineNumber);

    char deleteCharactorBeforeCursor();
    std::string deleteLineLineUnderCursor();

private:
    std::vector<std::string> content_;
    int cursorLine_;
    int cursorColumn_;
};



#endif // EDITOR_HPP

