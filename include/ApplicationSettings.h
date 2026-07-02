#pragma once
#include <string>
#include <mutex>

class ApplicationSettings {
public:
    static ApplicationSettings& instance() {
        static ApplicationSettings inst;
        return inst;
    }

    void setDefaultFont(const std::string& f) { defaultFont = f; }
    std::string getDefaultFont() const { return defaultFont; }

    void setPageSize(const std::string& s) { pageSize = s; }
    std::string getPageSize() const { return pageSize; }

private:
    ApplicationSettings() : defaultFont("Times New Roman"), pageSize("A4") {}
    ~ApplicationSettings() = default;
    ApplicationSettings(const ApplicationSettings&) = delete;
    ApplicationSettings& operator=(const ApplicationSettings&) = delete;

    std::string defaultFont;
    std::string pageSize;
};
