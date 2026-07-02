#pragma once
#include "Command.h"

// Fix CommandManager behavior: proper move semantics
inline void CommandManager::executeCommand(std::unique_ptr<ICommand> cmd) {
    if (!cmd) return;
    cmd->execute();
    undoStack.push(std::move(cmd));
    // clear redo
    while (!redoStack.empty()) redoStack.pop();
}

inline void CommandManager::undo() {
    if (undoStack.empty()) return;
    auto cmd = std::move(undoStack.top());
    undoStack.pop();
    if (cmd) {
        cmd->undo();
        redoStack.push(std::move(cmd));
    }
}

inline void CommandManager::redo() {
    if (redoStack.empty()) return;
    auto cmd = std::move(redoStack.top());
    redoStack.pop();
    if (cmd) {
        cmd->execute();
        undoStack.push(std::move(cmd));
    }
}
