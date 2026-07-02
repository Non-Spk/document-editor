#include "RealImage.hpp"
#include "IRenderer.hpp"

// Bridge Pattern: The draw implementation calls the appropriate method on the renderer.
void RealImage::draw(IRenderer& renderer) const {
    // The RealImage tells the renderer to render an image using its file path.
    renderer.renderImage(m_filePath);
}
