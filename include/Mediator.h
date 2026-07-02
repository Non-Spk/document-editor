#pragma once
#include "Observer.h"
#include "Builder.h"
#include <memory>

class UIMediator {
public:
    UIMediator(std::shared_ptr<Document> d): doc(d) {}
    void setStatusBar(std::shared_ptr<StatusBar> sb) { statusBar = sb; if (statusBar) doc->attach(statusBar.get()); }
    void addParagraph(const std::string& text) {
        auto p = std::make_shared<Paragraph>(text);
        doc->addElement(p);
    }
    void save(const std::string& path) { FileManagerFacade::save(*doc, path); }
private:
    std::shared_ptr<Document> doc;
    std::shared_ptr<StatusBar> statusBar;
};
