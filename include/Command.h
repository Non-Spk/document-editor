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
    // Declarations only; implementations live in CommandImpl.h to avoid duplicate definitions
    void executeCommand(std::unique_ptr<ICommand> cmd);
    void undo();
    void redo();
private:
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;
};
