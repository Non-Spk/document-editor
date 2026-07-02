#pragma once
#include "Elements.h"
#include <memory>
#include <iostream>

// Real image heavy object
class RealImage {
public:
    RealImage(const std::string& path): path(path) {
        // Simulate expensive load
        std::cout << "Loading image from " << path << "...\n";
    }
    void draw(IRenderer& renderer) { renderer.renderImage(path); }
private:
    std::string path;
};

// Virtual Proxy
class ImageProxy : public Image {
public:
    ImageProxy(const std::string& p): Image(p), real(nullptr) {}
    void render(IRenderer& renderer) const override {
        if (!real) {
            // const_cast to mutate lazy-loaded real image
            const_cast<ImageProxy*>(this)->real = std::make_shared<RealImage>(path);
        }
        real->draw(const_cast<IRenderer&>(renderer));
    }
private:
    mutable std::shared_ptr<RealImage> real;
};
