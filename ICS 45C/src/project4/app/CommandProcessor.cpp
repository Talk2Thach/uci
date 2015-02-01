// CommandProcessor.cpp
//
// ICS 45C Fall 2014
// Project #4: People Just Love to Play with Words
//
// Implementation of the CommandProcessor class

#include <vector>
#include "CommandProcessor.hpp"
#include "EditorException.hpp"
#include "Keypress.hpp"


CommandProcessor::CommandProcessor(Editor& editor, EditorView& view)
: editor{editor}, view{view}
{
}


namespace {
    // An "enum class" defines a type that has one of the constant values
    // specified.  So, in this case, a variable of type UserInteractionType
    // could have the value UserInteractionType::command,
    // UserInteractionType::undo, etc.
    enum class UserInteractionType {
        command,
        undo,
        redo,
        quit
    };


    // A UserInteraction describes one interaction that the user undertakes
    // with BooEdit.  There are four different kinds of interactions:
    //
    // * Commands, which attempt to affect some kind of change on the editor
    // * Undo, which asks for the previous change to be undone
    // * Redo, which asks for the most-recently undone change to be redone
    // * Quit, which asks for the editor to be stopped altogether
    //
    // A Command* is included for the case where UserInteractionType::command
    // is the specified type; otherwise, it will be nullptr.
    struct UserInteraction {
        UserInteractionType type;
        Command* command;
    };



    // You'll want these three functions, but I'm commenting them out for now,
    // so that this will compile without warnings.

    UserInteraction makeCommandInteraction(Command* command) {
        return UserInteraction{UserInteractionType::command, command};
    }

    UserInteraction makeUndoInteraction() {
        return UserInteraction{UserInteractionType::undo, nullptr};
    }


    UserInteraction makeRedoInteraction() {
        return UserInteraction{UserInteractionType::redo, nullptr};
    }


    UserInteraction makeQuitInteraction()
    {
        return UserInteraction{UserInteractionType::quit, nullptr};
    }


    // You will need to update this function to watch for the right keypresses
    // and build the right kinds of user interactions.  I've added handling
    // for "quit" here, but you'll need to add the others.
    UserInteraction nextUserInteraction() {
        while (true) {
            Keypress keypress = nextKeypress();

            if (keypress.ctrl) {
                // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

                switch (keypress.c) {
                    case 'Z':
                        return makeUndoInteraction();
                    case 'A':
                        return makeRedoInteraction();
                    case 'X':
                        return makeQuitInteraction();
                    case 'I':
                        return makeCommandInteraction(new CursorUpCommand);
                    case 'O':
                        return makeCommandInteraction(new CursorRightCommand);
                    case 'K':
                        return makeCommandInteraction(new CursorDownCommand);
                    case 'U':
                        return makeCommandInteraction(new CursorLeftCommand);
                    case 'Y':
                        return makeCommandInteraction(new CursorHomeCommand);
                    case 'P':
                        return makeCommandInteraction(new CursorEndCommand);
                    case 'J':
                    case 'M':
                        return makeCommandInteraction(new NewLineCommand);
                    case 'H':
                        return makeCommandInteraction(new BackspaceCommand);
                    case 'D':
                        return makeCommandInteraction(new DeleteLineCommand);
                }
            } else {
                return makeCommandInteraction(new InsertCharacterCommand(keypress.c));
            }
        }
    }
}

void CommandProcessor::run() {
    view.refresh();
    std::vector<UserInteraction> userInteractions;
    std::vector<UserInteraction> undoInteractions;
    while (true) {
        UserInteraction interaction = nextUserInteraction();

        if (interaction.type == UserInteractionType::quit) {
            break;
        } else if (interaction.type == UserInteractionType::undo) {
            if (userInteractions.size() != 0) {
                userInteractions.back().command->undo(editor);
                undoInteractions.push_back(userInteractions.back());
                userInteractions.pop_back();
                view.clearErrorMessage();
            }
        } else if (interaction.type == UserInteractionType::redo) {
            if (undoInteractions.size() != 0) {
                userInteractions.push_back(undoInteractions.back());
                undoInteractions.pop_back();
                userInteractions.back().command->execute(editor);
                view.clearErrorMessage();
            }
        } else if (interaction.type == UserInteractionType::command) {
            try {
                interaction.command->execute(editor);
                view.clearErrorMessage();
                userInteractions.push_back(interaction);
                for (auto & undoInteraction : undoInteractions) {
                    delete undoInteraction.command;
                }
                undoInteractions.clear();
            } catch (EditorException& e) {
                view.showErrorMessage(e.getReason());
                delete interaction.command;
            }
        }
        view.refresh();
    }
    for (auto & userInteraction : userInteractions) {
        delete userInteraction.command;
    }
    for (auto & undoInteraction : undoInteractions) {
        delete undoInteraction.command;
    }
}

