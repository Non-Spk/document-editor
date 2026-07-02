#ifndef DOCUMENT_ELEMENT_HPP
#define DOCUMENT_ELEMENT_HPP

#include <memory>

// Abstract base class for all document elements (Prototype Pattern).
// It provides an interface for cloning itself. This is essential for
// features like copy-paste.
class DocumentElement {
public:
    virtual ~DocumentElement() = default;

    // The 'clone' method is the core of the Prototype pattern.
    // We use std::unique_ptr for modern C++ memory management.
    virtual std::unique_ptr<DocumentElement> clone() const = 0;

    // A virtual method for rendering, to be used later with the Bridge pattern.
    // Forward declaration of IRenderer to avoid circular dependency.
    class IRenderer;
    virtual void draw(IRenderer& renderer) const = 0;
};

#endif // DOCUMENT_ELEMENT_HPP
