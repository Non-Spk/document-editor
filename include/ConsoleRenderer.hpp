#ifndef CONSOLE_RENDERER_HPP
#define CONSOLE_RENDERER_HPP

#include "IRenderer.hpp"
#include <iostream>

// Concrete implementation of the IRenderer interface (Bridge Pattern).
// This renderer "draws" the elements to the standard console output.
class ConsoleRenderer : public IRenderer {
public:
    void renderParagraph(const Paragraph& paragraph) override;
    void renderImage(const std::string& imagePath) override;
};

#endif // CONSOLE_RENDERER_HPP
