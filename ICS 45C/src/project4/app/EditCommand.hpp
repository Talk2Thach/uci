//
//  EditCommand.hpp
//  app
//
//  Created by Edward Xia on 12/2/14.
//  Copyright (c) 2014 Edward Xia. All rights reserved.
//

#ifndef __app__EditCommand__
#define __app__EditCommand__

#include "Command.hpp"

class InsertCharacterCommand : public Command {
public:
    InsertCharacterCommand(char &charactor);
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    char charactor_;
};

class NewLineCommand : public Command {
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
};

class BackspaceCommand : public Command {
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    char charactor_;
};

class DeleteLineCommand : public Command {
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    std::string str_;
    int cursorLine_;
    int cursorColumn_;
};

#endif /* defined(__app__EditCommand__) */
