//
//  EditCommand.cpp
//  app
//
//  Created by Edward Xia on 12/2/14.
//  Copyright (c) 2014 Edward Xia. All rights reserved.
//

#include "EditCommand.hpp"

InsertCharacterCommand::InsertCharacterCommand(char &charactor)
{
    charactor_ = charactor;
}

void InsertCharacterCommand::execute(Editor &editor)
{
    editor.insertCharactorUnderCursor(charactor_);
}

void InsertCharacterCommand::undo(Editor &editor)
{
    editor.deleteCharactorBeforeCursor();
}

void NewLineCommand::execute(Editor &editor)
{
    editor.insertNewLineUnderCursor();
}

void NewLineCommand::undo(Editor &editor)
{
    editor.deleteCharactorBeforeCursor();
}

void BackspaceCommand::execute(Editor &editor)
{
    charactor_ = editor.deleteCharactorBeforeCursor();
}

void BackspaceCommand::undo(Editor &editor)
{
    if (charactor_ == '\n') {
        editor.insertNewLineUnderCursor();
    } else {
        editor.insertCharactorUnderCursor(charactor_);
    }
}

void DeleteLineCommand::execute(Editor &editor)
{
    cursorColumn_ = editor.cursorColumn();
    cursorLine_ = editor.cursorLine();
    str_ = editor.deleteLineLineUnderCursor();
}

void DeleteLineCommand::undo(Editor &editor)
{
    if (editor.lineCount() == 1 && editor.line(1) == "") {
        editor.replaceLine(str_, cursorLine_);
    } else {
        editor.insertLine(str_, cursorLine_);
    }
    editor.moveCursorTo(cursorColumn_, cursorLine_);
}
