//
//  CursorCommand.cpp
//  app
//
//  Created by Edward Xia on 12/2/14.
//  Copyright (c) 2014 Edward Xia. All rights reserved.
//

#include "CursorCommand.hpp"

void CursorCommand::undo(Editor &editor)
{
    editor.moveCursorTo(cursorColumn_, cursorLine_);
}

void CursorRightCommand::execute(Editor &editor)
{
    cursorLine_ = editor.cursorLine();
    cursorColumn_ = editor.cursorColumn();
    editor.moveCursorColumnTo(cursorColumn_ + 1);
}

void CursorLeftCommand::execute(Editor &editor)
{
    cursorLine_ = editor.cursorLine();
    cursorColumn_ = editor.cursorColumn();
    editor.moveCursorColumnTo(cursorColumn_ - 1);
}

void CursorUpCommand::execute(Editor &editor)
{
    cursorLine_ = editor.cursorLine();
    cursorColumn_ = editor.cursorColumn();
    editor.moveCursorLineTo(cursorLine_ - 1);
}

void CursorDownCommand::execute(Editor &editor)
{
    cursorLine_ = editor.cursorLine();
    cursorColumn_ = editor.cursorColumn();
    editor.moveCursorLineTo(cursorLine_ + 1);
}

void CursorHomeCommand::execute(Editor &editor)
{
    cursorLine_ = editor.cursorLine();
    cursorColumn_ = editor.cursorColumn();
    editor.moveCursorColumnTo(1);
}

void CursorEndCommand::execute(Editor &editor)
{
    cursorLine_ = editor.cursorLine();
    cursorColumn_ = editor.cursorColumn();
    editor.moveCursorColumnTo((int)editor.line(cursorLine_).length() + 1);
}
