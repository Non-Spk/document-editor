#include <iostream>
#include <memory>

#include "ApplicationSettings.hpp"
#include "DocumentBuilder.hpp"
#include "Document.hpp"
#include "ElementFactory.hpp"
#include "ImageProxy.hpp"
#include "ConsoleRenderer.hpp"
#include "Paragraph.hpp" // Required for ParagraphFactory & clone demo

void printSeparator() {
    std::cout << "\n----------------------------------------\n" << std::endl;
}

int main() {
    std::cout << "Initializing Document Editor Framework..." << std::endl;
    printSeparator();

    // --- Creational Patterns Demo ---
    std::cout << "1. Creational Patterns Demo" << std::endl;

    // Singleton
    ApplicationSettings& settings = ApplicationSettings::getInstance();
    settings.setDefaultFont("Times New Roman");
    std::cout << " - Default font from Singleton: " << settings.getDefaultFont() << std::endl;

    // Builder
    DocumentBuilder builder;
    std::unique_ptr<Document> doc = builder.setPageSize("A4")
                                        .setMargins("2.5cm")
                                        .getDocument();
    std::cout << " - Document created with Page Size: " << doc->getPageSize() << std::endl;

    // Factory Method to create elements
    ParagraphFactory pFactory("This is a paragraph created by a factory.");
    doc->addElement(pFactory.createElement());
    
    // Add a proxy for an image. The real image is not loaded yet.
    doc->addElement(std::make_unique<ImageProxy>("logo.png"));
    
    // Prototype: Clone an element.
    auto p_original = std::make_unique<Paragraph>("This is the original paragraph to be cloned.");
    auto p_clone = p_original->clone(); // Using the Prototype pattern
    std::cout << " - Successfully cloned a paragraph element." << std::endl;
    doc->addElement(std::move(p_original));
    doc->addElement(std::move(p_clone));

    printSeparator();

    // --- Structural Patterns Demo ---
    std::cout << "2. Structural Patterns Demo" << std::endl;
    
    // Bridge, Proxy, and Composite
    ConsoleRenderer renderer;
    std::cout << " - Drawing document using ConsoleRenderer..." << std::endl;

    // The Document acts as a Composite. Drawing it will draw all its children.
    // The draw call on the ImageProxy will trigger the Proxy pattern's lazy loading.
    doc->draw(renderer);

    printSeparator();
    
    // Draw the document again to show the proxy doesn't load the image a second time.
    std::cout << " - Drawing document again..." << std::endl;
    doc->draw(renderer);
    
    printSeparator();

    std::cout << "Framework demonstration complete." << std::endl;

    return 0;
}