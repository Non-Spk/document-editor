#pragma once
#include "Builder.h"
#include <string>

class IExportStrategy {
public:
    virtual ~IExportStrategy() = default;
    virtual std::string exportDocument(const Document& doc) = 0;
};

class ExportAsMarkdown : public IExportStrategy {
public:
    std::string exportDocument(const Document& doc) override {
        std::string out = "# Document Export (Markdown)\n";
        for (auto& e : doc.getElements()) out += e->serialize() + "\n";
        return out;
    }
};

class ExportAsPlainText : public IExportStrategy {
public:
    std::string exportDocument(const Document& doc) override {
        std::string out;
        for (auto& e : doc.getElements()) out += e->serialize() + "\n";
        return out;
    }
};

inline std::string Document::exportDocument() const {
    if (!exportStrategy) return "";
    return exportStrategy->exportDocument(*this);
}
