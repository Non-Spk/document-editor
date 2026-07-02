#ifndef ELEMENT_FACTORY_HPP
#define ELEMENT_FACTORY_HPP

#include "DocumentElement.hpp"
#include "Paragraph.hpp" // Include the concrete product
#include <memory>
#include <string>
#include <utility>

// Abstract factory (Factory Method Pattern)
class ElementFactory {
public:
    virtual ~ElementFactory() = default;
    virtual std::unique_ptr<DocumentElement> createElement() = 0;
};

// Concrete factory for creating Paragraphs
class ParagraphFactory : public ElementFactory {
public:
    explicit ParagraphFactory(std::string text) : m_text(std::move(text)) {}

    std::unique_ptr<DocumentElement> createElement() override {
        return std::make_unique<Paragraph>(m_text);
    }
private:
    std::string m_text;
};


#endif // ELEMENT_FACTORY_HPP
