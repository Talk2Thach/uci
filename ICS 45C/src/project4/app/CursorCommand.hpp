//
//  CursorCommand.hpp
//  app
//
//  Created by Edward Xia on 12/2/14.
//  Copyright (c) 2014 Edward Xia. All rights reserved.
//

#ifndef __app__CursorCommand__
#define __app__CursorCommand__

#include "Command.hpp"

class CursorCommand : public Command {
public:
    void undo(Editor& editor);
protected:
    int cursorLine_;
    int cursorColumn_;
};

class CursorRightCommand : public CursorCommand {
public:
    void execute(Editor& editor);
};

class CursorLeftCommand : public CursorCommand {
public:
    void execute(Editor& editor);
};

class CursorDownCommand : public CursorCommand {
public:
    void execute(Editor& editor);
};

class CursorUpCommand : public CursorCommand {
public:
    void execute(Editor& editor);
};

class CursorHomeCommand : public CursorCommand {
public:
    void execute(Editor& editor);
};

class CursorEndCommand : public CursorCommand {
public:
    void execute(Editor& editor);
};

#endif /* defined(__app__CursorCommand__) */
