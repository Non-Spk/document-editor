#pragma once
#include <string>
#include <ostream>

struct IRenderer {
    virtual ~IRenderer() = default;
    virtual void renderParagraph(const std::string& text) = 0;
    virtual void renderImage(const std::string& path) = 0;
    virtual void renderTable(const std::string& desc) = 0;
};

class ConsoleRenderer : public IRenderer {
public:
    void renderParagraph(const std::string& text) override {
        std::cout << "[P] " << text << std::endl;
    }
    void renderImage(const std::string& path) override {
        std::cout << "[IMG] " << path << std::endl;
    }
    void renderTable(const std::string& desc) override {
        std::cout << "[TABLE] " << desc << std::endl;
    }
};

class HTMLRenderer : public IRenderer {
public:
    void renderParagraph(const std::string& text) override {
        std::cout << "<p>" << text << "</p>\n";
    }
    void renderImage(const std::string& path) override {
        std::cout << "<img src='" << path << "' />\n";
    }
    void renderTable(const std::string& desc) override {
        std::cout << "<table><caption>" << desc << "</caption></table>\n";
    }
};
