#pragma once
#include "DocumentElement.h"
#include "IRenderer.h"
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Forward declarations
class Paragraph;
class Image;
class Table;

// Paragraph (leaf)
class Paragraph : public DocumentElement, public std::enable_shared_from_this<Paragraph> {
public:
    Paragraph() = default;
    Paragraph(const std::string& t): text(t) {}
    std::shared_ptr<DocumentElement> clone() const override {
        return std::make_shared<Paragraph>(*this);
    }
    void render(IRenderer& renderer) const override {
        renderer.renderParagraph(text);
    }
    void accept(IDocumentVisitor& visitor) override;
    std::string getText() const { return text; }
    void setText(const std::string& t) { text = t; }
    std::string serialize() const override {
        return "Paragraph:" + text;
    }
private:
    std::string text;
};

// Image (leaf) - will be used with proxy
class Image : public DocumentElement {
public:
    Image() = default;
    Image(const std::string& p): path(p) {}
    std::shared_ptr<DocumentElement> clone() const override {
        return std::make_shared<Image>(*this);
    }
    void render(IRenderer& renderer) const override {
        renderer.renderImage(path);
    }
    void accept(IDocumentVisitor& visitor) override;
    std::string serialize() const override {
        return "Image:" + path;
    }
    std::string path;
};

// Table (leaf)
class Table : public DocumentElement {
public:
    Table() = default;
    Table(const std::string& d): desc(d) {}
    std::shared_ptr<DocumentElement> clone() const override {
        return std::make_shared<Table>(*this);
    }
    void render(IRenderer& renderer) const override {
        renderer.renderTable(desc);
    }
    void accept(IDocumentVisitor& visitor) override;
    std::string serialize() const override {
        return "Table:" + desc;
    }
    std::string desc;
};

// Composite: Section
class Section : public DocumentElement {
public:
    Section() = default;
    Section(const std::string& t): title(t) {}
    void add(const std::shared_ptr<DocumentElement>& e) { children.push_back(e); }
    void remove(const std::shared_ptr<DocumentElement>& e) {
        children.erase(std::remove(children.begin(), children.end(), e), children.end());
    }
    std::shared_ptr<DocumentElement> clone() const override {
        auto s = std::make_shared<Section>(*this);
        s->children.clear();
        for (auto& c : children) s->children.push_back(c->clone());
        return s;
    }
    void render(IRenderer& renderer) const override {
        std::cout << "-- Section: " << title << " --\n";
        for (auto& c : children) c->render(const_cast<IRenderer&>(renderer));
    }
    void accept(IDocumentVisitor& visitor) override;
    std::string serialize() const override {
        std::ostringstream oss;
        oss << "Section:" << title << "{";
        for (auto& c : children) oss << c->serialize() << ";";
        oss << "}";
        return oss.str();
    }
    std::string title;
    std::vector<std::shared_ptr<DocumentElement>> children;
};

