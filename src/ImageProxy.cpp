#include "ImageProxy.hpp"
#include "RealImage.hpp" // Needs the full definition to create the object
#include "IRenderer.hpp" // For the renderer interface
#include <iostream>

// The draw method is the trigger for loading the real object.
void ImageProxy::draw(IRenderer& renderer) const {
    std::cout << "ImageProxy: draw() called. ";
    ensureImageLoaded(); // Lazy initialization happens here.
    m_realImage->draw(renderer); // Delegate the draw call to the real object.
}

// Private helper to perform the lazy loading.
void ImageProxy::ensureImageLoaded() const {
    if (!m_realImage) {
        std::cout << "Instantiating RealImage for the first time." << std::endl;
        m_realImage = std::make_unique<RealImage>(m_filePath);
    } else {
        std::cout << "RealImage already loaded." << std::endl;
    }
}
