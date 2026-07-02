#pragma once
#include "Elements.h"
#include <memory>

// Decorator for Paragraph-like elements
class TextDecorator : public DocumentElement {
public:
    TextDecorator(std::shared_ptr<DocumentElement> base): base(base) {}
    std::shared_ptr<DocumentElement> clone() const override { return std::make_shared<TextDecorator>(base->clone()); }
    void render(IRenderer& renderer) const override { base->render(renderer); }
    void accept(IDocumentVisitor& visitor) override { base->accept(visitor); }
    std::string serialize() const override { return base->serialize(); }
protected:
    std::shared_ptr<DocumentElement> base;
};

class BoldDecorator : public TextDecorator {
public:
    BoldDecorator(std::shared_ptr<DocumentElement> b): TextDecorator(b) {}
    void render(IRenderer& renderer) const override {
        std::cout << "<b>";
        base->render(const_cast<IRenderer&>(renderer));
        std::cout << "</b>" << std::endl;
    }
};

class ItalicDecorator : public TextDecorator {
public:
    ItalicDecorator(std::shared_ptr<DocumentElement> b): TextDecorator(b) {}
    void render(IRenderer& renderer) const override {
        std::cout << "<i>";
        base->render(const_cast<IRenderer&>(renderer));
        std::cout << "</i>" << std::endl;
    }
};
