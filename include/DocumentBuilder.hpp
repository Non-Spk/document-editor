#ifndef DOCUMENT_BUILDER_HPP
#define DOCUMENT_BUILDER_HPP

#include "Document.hpp"
#include <memory>
#include <string>
#include <utility>

// Builder pattern for constructing a complex Document object.
class DocumentBuilder {
public:
    DocumentBuilder() {
        m_document = std::make_unique<Document>();
    }

    DocumentBuilder& setPageSize(const std::string& size) {
        m_document->setPageSize(size);
        return *this;
    }

    DocumentBuilder& setMargins(const std::string& margins) {
        m_document->setMargins(margins);
        return *this;
    }

    DocumentBuilder& setHeader(const std::string& header) {
        m_document->setHeader(header);
        return *this;
    }

    DocumentBuilder& setFooter(const std::string& footer) {
        m_document->setFooter(footer);
        return *this;
    }

    // Method to get the final product.
    // This transfers ownership of the document to the caller.
    std::unique_ptr<Document> getDocument() {
        return std::move(m_document);
    }

private:
    std::unique_ptr<Document> m_document;
};

#endif // DOCUMENT_BUILDER_HPP
