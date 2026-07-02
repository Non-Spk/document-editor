#ifndef IRENDERER_HPP
#define IRENDERER_HPP

// Forward declarations for concrete elements.
// This avoids including the full header for each element.
class Paragraph;
class ImageProxy; // We will create this later for the Proxy pattern

// Interface for the Renderer (Bridge Pattern).
// This decouples the document model from its representation.
class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void renderParagraph(const Paragraph& paragraph) = 0;
    virtual void renderImage(const std::string& imagePath) = 0;

    // --- Formatting Methods for Decorator Pattern ---
    virtual void beginBold() = 0;
    virtual void endBold() = 0;
    virtual void beginItalic() = 0;
    virtual void endItalic() = 0;
};

#endif // IRENDERER_HPP
