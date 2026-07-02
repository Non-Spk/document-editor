#pragma once
#include "Builder.h"
#include <stack>

// Command
class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddElementCommand : public ICommand {
public:
    AddElementCommand(std::shared_ptr<Document> doc, std::shared_ptr<DocumentElement> elem)
        : doc(doc), elem(elem) {}
    void execute() override {
        backup = doc->createMemento();
        doc->addElement(elem);
    }
    void undo() override {
        doc->restoreMemento(backup);
    }
private:
    std::shared_ptr<Document> doc;
    std::shared_ptr<DocumentElement> elem;
    std::string backup;
};

class CommandManager {
public:
    void executeCommand(std::unique_ptr<ICommand> cmd) {
        cmd->execute();
        undoStack.push(std::move(cmd));
        // clear redo
        while (!redoStack.empty()) redoStack.pop();
    }
    void undo() {
        if (undoStack.empty()) return;
        auto& cmd = undoStack.top();
        cmd->undo();
        redoStack.push(std::move(undoStack.top()));
        undoStack.pop();
    }
    void redo() {
        if (redoStack.empty()) return;
        auto& cmd = redoStack.top();
        cmd->execute();
        undoStack.push(std::move(redoStack.top()));
        redoStack.pop();
    }
private:
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;
};
