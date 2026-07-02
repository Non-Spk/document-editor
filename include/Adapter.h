#pragma once
#include "IRenderer.h"
#include <iostream>

// A legacy shape drawer with an incompatible interface
class LegacyShapeDrawer {
public:
    void drawCircle(int x, int y, int r) {
        std::cout << "LegacyShapeDrawer: drawCircle at (" << x << "," << y << ") r=" << r << "\n";
    }
    void drawRectangle(int x, int y, int w, int h) {
        std::cout << "LegacyShapeDrawer: drawRectangle at (" << x << "," << y << ") w=" << w << " h=" << h << "\n";
    }
};

// Adapter to allow LegacyShapeDrawer to be used as an IRenderer
class ShapeDrawerAdapter : public IRenderer {
public:
    ShapeDrawerAdapter(std::shared_ptr<LegacyShapeDrawer> legacy): legacy(legacy) {}
    void renderParagraph(const std::string& text) override {
        // Fallback: render as text
        std::cout << "[Adapted P] " << text << std::endl;
    }
    void renderImage(const std::string& path) override {
        // map an image to a rectangle draw
        if (legacy) legacy->drawRectangle(10, 10, 100, 50);
    }
    void renderTable(const std::string& desc) override {
        if (legacy) legacy->drawRectangle(0,0,200,100);
    }
private:
    std::shared_ptr<LegacyShapeDrawer> legacy;
};
