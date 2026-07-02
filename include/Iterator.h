#pragma once
#include "Builder.h"
#include <vector>
#include <memory>

// Simple DFS iterator that flattens the document elements in construction
class DocumentIterator {
public:
    DocumentIterator(std::shared_ptr<Document> doc) {
        if (doc) buildList(doc->getElements());
        index = 0;
    }
    bool hasNext() const { return index < list.size(); }
    std::shared_ptr<DocumentElement> next() { return hasNext() ? list[index++] : nullptr; }
private:
    void buildList(const std::vector<std::shared_ptr<DocumentElement>>& elems) {
        for (auto& e : elems) {
            list.push_back(e);
            // If section, recurse
            auto sec = std::dynamic_pointer_cast<Section>(e);
            if (sec) buildList(sec->children);
        }
    }
    std::vector<std::shared_ptr<DocumentElement>> list;
    size_t index{0};
};
