#include "Paragraph.hpp"
#include "IRenderer.hpp"

// Bridge Pattern: The draw implementation calls the appropriate method on the renderer.
void Paragraph::draw(IRenderer& renderer) const {
    renderer.renderParagraph(*this);
}
