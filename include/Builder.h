#pragma once
#include "Elements.h"
#include <memory>

class Document {
public:
    Document() = default;
    void setHeader(const std::string& h) { header = h; }
    void setFooter(const std::string& f) { footer = f; }
    void addElement(const std::shared_ptr<DocumentElement>& e) { elements.push_back(e); notify(); }
    const std::vector<std::shared_ptr<DocumentElement>>& getElements() const { return elements; }

    std::string serialize() const {
        std::ostringstream oss;
        oss << "Header:" << header << "\n";
        for (auto& e : elements) oss << e->serialize() << "\n";
        return oss.str();
    }
    void deserialize(const std::string& /*data*/) {
        // Simple placeholder: real implementation would parse and rebuild tree
        notify();
    }

    // Memento
    std::string createMemento() const { return serialize(); }
    void restoreMemento(const std::string& state) { deserialize(state); }

    // Observers
    void attach(class IDocumentObserver* obs) { observers.push_back(obs); }
    void notify();

    // State
    void setState(class DocumentState* s) { state.reset(s); }
    bool canEdit() const;

    // Export strategy
    void setExportStrategy(class IExportStrategy* s) { exportStrategy.reset(s); }
    std::string exportDocument() const;

private:
    std::string header, footer;
    std::vector<std::shared_ptr<DocumentElement>> elements;
    std::vector<class IDocumentObserver*> observers;
    std::unique_ptr<class DocumentState> state{nullptr};
    std::unique_ptr<class IExportStrategy> exportStrategy{nullptr};
};

class DocumentBuilder {
public:
    DocumentBuilder() { doc = std::make_shared<Document>(); }
    DocumentBuilder& header(const std::string& h) { doc->setHeader(h); return *this; }
    DocumentBuilder& footer(const std::string& f) { doc->setFooter(f); return *this; }
    std::shared_ptr<Document> build() { return doc; }
private:
    std::shared_ptr<Document> doc;
};
