#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

class IDocumentVisitor;
struct IRenderer;

class DocumentElement {
public:
    virtual ~DocumentElement() = default;
    virtual std::shared_ptr<DocumentElement> clone() const = 0; // Prototype
    virtual void render(IRenderer& renderer) const = 0; // Bridge
    virtual void accept(IDocumentVisitor& visitor) = 0; // Visitor
    virtual std::string serialize() const = 0;
};

