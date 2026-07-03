#ifndef IMAGE_PROXY_HPP
#define IMAGE_PROXY_HPP

#include "DocumentElement.hpp"
#include "RealImage.hpp"
#include <string>
#include <memory>
#include <utility>

// Virtual Proxy Pattern: stands in for RealImage and defers the expensive
// load until draw() is actually called.
class ImageProxy : public DocumentElement
{
public:
    // Both are declared here but defined in the .cpp (where RealImage is
    // a complete type). This keeps std::unique_ptr<RealImage>'s deleter
    // (and the exception-unwind cleanup code the compiler generates for
    // this constructor) from being instantiated against an incomplete
    // type at header-inclusion sites.
    explicit ImageProxy(std::string filePath);
    ~ImageProxy() override;

    std::unique_ptr<DocumentElement> clone() const override
    {
        // Cloning the proxy does NOT force-load the real image.
        return std::make_unique<ImageProxy>(m_filePath);
    }

    void draw(IRenderer &renderer) const override;
    void accept(IDocumentVisitor &visitor) const override;

    const std::string &getFilePath() const { return m_filePath; }

private:
    std::string m_filePath;
    mutable std::unique_ptr<RealImage> m_realImage;

    void ensureImageLoaded() const;
};

#endif // IMAGE_PROXY_HPP