#include "RealImage.hpp"
#include "IRenderer.hpp"

// Bridge Pattern: The render implementation calls the appropriate method on the renderer.
void RealImage::render(IRenderer& renderer) const {
    // The RealImage tells the renderer to render an image using its file path.
    renderer.renderImage(m_filePath);
}
