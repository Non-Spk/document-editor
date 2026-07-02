#ifndef REAL_IMAGE_HPP
#define REAL_IMAGE_HPP

#include "DocumentElement.hpp"
#include <string>
#include <iostream>
#include <utility>

// The "heavy" object that the proxy will stand in for.
class RealImage : public DocumentElement {
public:
    explicit RealImage(std::string filePath) : m_filePath(std::move(filePath)) {
        // Simulate loading a large image file from disk, which is a slow operation.
        std::cout << "   (Loading image from " << m_filePath << ")" << std::endl;
    }

    // Prototype implementation
    std::unique_ptr<DocumentElement> clone() const override {
        // Cloning a real image means creating another fully loaded image
        return std::make_unique<RealImage>(*this);
    }

    void draw(IRenderer& renderer) const override;

    const std::string& getFilePath() const { return m_filePath; }


private:
    std::string m_filePath;
};

#endif // REAL_IMAGE_HPP
