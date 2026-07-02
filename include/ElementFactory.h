#pragma once
#include "Elements.h"
#include <memory>

class ElementFactory {
public:
    enum class Type { ParagraphT, ImageT, TableT, SectionT };
    static std::shared_ptr<DocumentElement> create(Type t, const std::string& content = "") {
        switch (t) {
            case Type::ParagraphT: return std::make_shared<Paragraph>(content);
            case Type::ImageT: return std::make_shared<Image>(content);
            case Type::TableT: return std::make_shared<Table>(content);
            case Type::SectionT: return std::make_shared<Section>(content);
        }
        return nullptr;
    }
};
