#ifndef IMAGE_PROXY_HPP
#define IMAGE_PROXY_HPP

#include "DocumentElement.hpp"
#include <string>
#include <memory>
#include <utility>

// Forward declare RealImage to avoid including its full header here.
class RealImage;

// The Proxy class for RealImage (Virtual Proxy).
// It controls access to the RealImage object, creating it only when needed.
class ImageProxy : public DocumentElement {
public:
    explicit ImageProxy(std::string filePath) : m_filePath(std::move(filePath)), m_realImage(nullptr) {}

    // Prototype implementation for the proxy
    std::unique_ptr<DocumentElement> clone() const override {
        // Clones the proxy, not the real image yet. The new proxy will also lazy load.
        return std::make_unique<ImageProxy>(m_filePath);
    }
    
    void draw(IRenderer& renderer) const override;

    const std::string& getFilePath() const { return m_filePath; }

private:
    // The proxy maintains a reference to the real subject.
    // It's mutable so we can lazy-initialize it in the const 'draw' method.
    mutable std::unique_ptr<RealImage> m_realImage;
    std::string m_filePath;

    // Helper function to create the RealImage on demand.
    void ensureImageLoaded() const;
};

#endif // IMAGE_PROXY_HPP
