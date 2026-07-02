#pragma once
#include "Builder.h"
#include <iostream>

class IDocumentObserver {
public:
    virtual ~IDocumentObserver() = default;
    virtual void onDocumentChanged(const Document& doc) = 0;
};

class StatusBar : public IDocumentObserver {
public:
    void onDocumentChanged(const Document& doc) override {
        size_t words = 0;
        for (auto& e : doc.getElements()) {
            // rough approximation
            auto s = e->serialize();
            for (char c : s) if (c == ' ') ++words;
        }
        std::cout << "[StatusBar] Document changed. Approx words: " << words << "\n";
    }
};

inline void Document::notify() {
    for (auto o : observers) o->onDocumentChanged(*this);
}

