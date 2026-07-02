#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "DocumentElement.hpp"
#include <vector>
#include <memory>
#include <string>

// The Document class, which acts as a Composite.
// It can contain other DocumentElements.
class Document {
public:
    Document() = default;

    void addElement(std::unique_ptr<DocumentElement> element) {
        m_elements.push_back(std::move(element));
    }

    void draw(IRenderer& renderer) const {
        for (const auto& element : m_elements) {
            element->draw(renderer);
        }
    }
    
    // --- Setters for Builder ---
    void setPageSize(const std::string& size) { m_pageSize = size; }
    void setMargins(const std::string& margins) { m_margins = margins; }
    void setHeader(const std::string& header) { m_header = header; }
    void setFooter(const std::string& footer) { m_footer = footer; }

    // --- Getters for demonstration ---
    const std::string& getPageSize() const { return m_pageSize; }
    const std::string& getMargins() const { return m_margins; }
    const std::string& getHeader() const { return m_header; }
    const std::string& getFooter() const { return m_footer; }


private:
    std::string m_pageSize;
    std::string m_margins;
    std::string m_header;
    std::string m_footer;
    std::vector<std::unique_ptr<DocumentElement>> m_elements;
};

#endif // DOCUMENT_HPP
