#ifndef PARAGRAPH_HPP
#define PARAGRAPH_HPP

#include "DocumentElement.hpp"
#include <string>
#include <memory>
#include <utility>

// Concrete implementation of a DocumentElement (Paragraph).
class Paragraph : public DocumentElement {
public:
    explicit Paragraph(std::string text) : m_text(std::move(text)) {}

    // Prototype pattern implementation
    std::unique_ptr<DocumentElement> clone() const override {
        return std::make_unique<Paragraph>(*this);
    }

    void draw(IRenderer& renderer) const override;

    const std::string& getText() const {
        return m_text;
    }

private:
    std::string m_text;
};

#endif // PARAGRAPH_HPP
