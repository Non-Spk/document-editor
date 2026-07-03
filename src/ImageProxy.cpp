#include "ImageProxy.hpp"
#include "RealImage.hpp"
#include "IRenderer.hpp"
#include "IteratorVisitor.h"
#include <iostream>

ImageProxy::ImageProxy(std::string filePath) : m_filePath(std::move(filePath)), m_realImage(nullptr) {}

ImageProxy::~ImageProxy() = default;

void ImageProxy::draw(IRenderer &renderer) const
{
    std::cout << "ImageProxy: draw() called. ";
    ensureImageLoaded();
    m_realImage->draw(renderer);
}

void ImageProxy::accept(IDocumentVisitor &visitor) const
{
    // The proxy visits without forcing a load: most visitors (word count,
    // xml export) only need metadata like the file path.
    visitor.visit(*this);
}

void ImageProxy::ensureImageLoaded() const
{
    if (!m_realImage)
    {
        std::cout << "Instantiating RealImage for the first time." << std::endl;
        m_realImage = std::make_unique<RealImage>(m_filePath);
    }
    else
    {
        std::cout << "RealImage already loaded." << std::endl;
    }
}
