// Editor.cpp
//
// ICS 45C Fall 2014
// Project #4: People Just Love to Play with Words
//
// Implementation of the Editor class

#include "Editor.hpp"
#include "EditorException.hpp"


Editor::Editor()
{
    cursorLine_ = 1;
    cursorColumn_ = 1;
    content_.push_back("");
}

int Editor::cursorLine() const
{
    return cursorLine_;
}


int Editor::cursorColumn() const
{
    return cursorColumn_;
}


int Editor::lineCount() const
{
    return (int)content_.size();
}


const std::string& Editor::line(int lineNumber) const
{
    return content_.at(lineNumber - 1);
}

void Editor::moveCursorColumnTo(int x)
{
    if (x <= 0) {
        if (cursorLine_ <= 1) {
            throw EditorException("Already at the very begin");
        }
        cursorLine_--;
        cursorColumn_ = (int)line(cursorLine_).length() + 1;
    } else if (x > (int)line(cursorLine_).length() + 1) {
        if (cursorLine_ >= lineCount()) {
            throw EditorException("Already at the very end");
        }
        cursorLine_++;
        cursorColumn_ = 1;
    } else {
        cursorColumn_ = x;
    }
}

void Editor::moveCursorLineTo(int y)
{
    if (y <= 0) {
        throw EditorException("Already at the very top");
    } else if (y > lineCount()) {
        throw EditorException("Already at the very bottom");
    }
    int targetLineTextLength = (int)line(y).length();
    if (cursorColumn_ > targetLineTextLength) {
        cursorColumn_ = targetLineTextLength + 1;
    }
    cursorLine_ = y;
}

void Editor::moveCursorTo(int x, int y)
{
    cursorColumn_ = x;
    cursorLine_ = y;
}

void Editor::insertCharactorUnderCursor(char &charactor)
{
    content_.at(cursorLine_ - 1) = content_.at(cursorLine_ - 1).substr(0, cursorColumn_ - 1) + charactor + content_.at(cursorLine_ - 1).substr(cursorColumn_ - 1);
    cursorColumn_++;
}

void Editor::insertNewLineUnderCursor()
{
    content_.insert(content_.begin() + cursorLine_, content_.at(cursorLine_ - 1).substr(cursorColumn_ - 1));
    content_.at(cursorLine_ - 1) = content_.at(cursorLine_ - 1).substr(0, cursorColumn_ - 1);
    cursorLine_++;
    cursorColumn_ = 1;
}

void Editor::insertLine(std::string &str, int &lineNumber)
{
    content_.insert(content_.begin() + lineNumber - 1, str);
}

void Editor::replaceLine(std::string &str, int &lineNumber)
{
    content_.at(lineNumber - 1) = str;
}

char Editor::deleteCharactorBeforeCursor()
{
    if (cursorColumn_ == 1) {
        if (cursorLine_ == 1) {
            throw EditorException("Already delete to the very begin");
        } else {
            cursorLine_--;
            cursorColumn_ = (int)line(cursorLine_).length() + 1;
            content_.at(cursorLine_ - 1).append(content_.at(cursorLine_));
            content_.erase(content_.begin() + cursorLine_);
            return '\n';
        }
    } else {
        char deleted = content_.at(cursorLine_ - 1).at(cursorColumn_ - 2);
        content_.at(cursorLine_ - 1) = content_.at(cursorLine_ - 1).substr(0, cursorColumn_ - 2) + content_.at(cursorLine_ - 1).substr(cursorColumn_ - 1);
        cursorColumn_--;
        return deleted;
    }
}

std::string Editor::deleteLineLineUnderCursor()
{
    std::string deleted = content_.at(cursorLine_ - 1);
    if (content_.size() == 1 && deleted == "") {
        throw EditorException("Already empty");
    }
    content_.erase(content_.begin() + cursorLine_ - 1);
    if (content_.size() == 0) {
        content_.push_back("");
        cursorColumn_ = 1;
    } else {
        if (cursorLine_ > content_.size()) {
            moveCursorLineTo((int)content_.size());
        } else {
            moveCursorLineTo(cursorLine_);
        }
    }
    return deleted;
}

