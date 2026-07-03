#ifndef IMAGE_PROXY_HPP
#define IMAGE_PROXY_HPP

#include "DocumentElement.h"
#include "RealImage.hpp"
#include <string>
#include <memory>
#include <utility>

// Virtual Proxy Pattern: stands in for RealImage and defers the expensive
// load until render() is actually called.
class ImageProxy : public DocumentElement
{
public:
    explicit ImageProxy(std::string filePath);
    ~ImageProxy() override;

    std::shared_ptr<DocumentElement> clone() const override
    {
        // Cloning the proxy does NOT force-load the real image.
        return std::make_shared<ImageProxy>(m_filePath);
    }

    void render(IRenderer &renderer) const override;
    void accept(IDocumentVisitor &visitor) override;

    const std::string &getFilePath() const { return m_filePath; }

private:
    std::string m_filePath;
    mutable std::unique_ptr<RealImage> m_realImage;

    void ensureImageLoaded() const;
};

#endif // IMAGE_PROXY_HPP
