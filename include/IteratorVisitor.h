#pragma once
#include "Elements.h"
#include <stack>

class ImageProxy; // forward for visitor overload

class IDocumentVisitor {
public:
    virtual ~IDocumentVisitor() = default;
    virtual void visit(Paragraph& p) = 0;
    virtual void visit(Image& i) = 0;
    virtual void visit(Table& t) = 0;
    virtual void visit(Section& s) = 0;
    virtual void visit(ImageProxy& p) = 0;
};

class WordCountVisitor : public IDocumentVisitor {
public:
    void visit(Paragraph& p) override {
        std::istringstream iss(p.getText());
        std::string w;
        while (iss >> w) ++count;
    }
    void visit(Image&) override {}
    void visit(Table&) override {}
    void visit(Section& s) override {
        for (auto& c : s.children) c->accept(*this);
    }
    void visit(ImageProxy&) override {}
    int getCount() const { return count; }
private:
    int count = 0;
};

// Implement accept methods
inline void Paragraph::accept(IDocumentVisitor& visitor) { visitor.visit(*this); }
inline void Image::accept(IDocumentVisitor& visitor) { visitor.visit(*this); }
inline void Table::accept(IDocumentVisitor& visitor) { visitor.visit(*this); }
inline void Section::accept(IDocumentVisitor& visitor) { visitor.visit(*this); }

