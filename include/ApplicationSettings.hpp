#ifndef APPLICATION_SETTINGS_HPP
#define APPLICATION_SETTINGS_HPP

#include <string>

// Using the Singleton pattern to ensure there's only one instance
// of application settings throughout the program.
class ApplicationSettings {
public:
    // Deleted copy constructor and assignment operator to prevent duplication
    ApplicationSettings(const ApplicationSettings&) = delete;
    ApplicationSettings& operator=(const ApplicationSettings&) = delete;

    // Static method to get the single instance of the class
    static ApplicationSettings& getInstance() {
        // Meyers' Singleton: The instance is created when this function is first called
        // and is guaranteed to be destroyed correctly. It's thread-safe in C++11+.
        static ApplicationSettings instance;
        return instance;
    }

    // --- Example Settings ---
    void setDefaultFont(const std::string& font) {
        m_defaultFont = font;
    }

    const std::string& getDefaultFont() const {
        return m_defaultFont;
    }

    void setPageSize(const std::string& size) {
        m_pageSize = size;
    }

    const std::string& getPageSize() const {
        return m_pageSize;
    }

private:
    // Private constructor to prevent instantiation from outside
    ApplicationSettings() : m_defaultFont("Arial"), m_pageSize("A4") {}

    // --- Member variables for settings ---
    std::string m_defaultFont;
    std::string m_pageSize;
};

#endif // APPLICATION_SETTINGS_HPP
