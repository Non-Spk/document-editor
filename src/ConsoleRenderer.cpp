#include "ConsoleRenderer.hpp"
#include "Paragraph.hpp" // Needs the definition to get text

void ConsoleRenderer::renderParagraph(const Paragraph& paragraph) {
    std::cout << "[Paragraph]: " << paragraph.getText() << std::endl;
}

void ConsoleRenderer::renderImage(const std::string& imagePath) {
    std::cout << "[Image]: Displaying image from '" << imagePath << "'" << std::endl;
}
