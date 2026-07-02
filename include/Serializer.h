#pragma once
#include "Builder.h"
#include <vector>
#include <string>
#include <sstream>

// Simple parser for the Document serialization format used in Document::serialize()
// Format assumptions (from Document::serialize):
// Header:<header>\n
// Then each element on its own line, where elements are serialized as:
// Paragraph:<text>
// Image:<path>
// Table:<desc>
// Section:<title>{child1;child2;}

static std::vector<std::string> splitTopLevel(const std::string& s) {
    std::vector<std::string> parts;
    std::string cur;
    int depth = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '{') { depth++; cur.push_back(c); }
        else if (c == '}') { depth--; cur.push_back(c); }
        else if (c == ';' && depth == 0) {
            parts.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    if (!cur.empty()) parts.push_back(cur);
    return parts;
}

static std::shared_ptr<DocumentElement> parseElementString(const std::string& s);

static std::vector<std::shared_ptr<DocumentElement>> parseChildrenInsideBraces(const std::string& inner) {
    std::vector<std::shared_ptr<DocumentElement>> out;
    // children are separated by ';' at top level, but our helper expects to get raw children separated
    // We'll manually parse using stack method similar to splitTopLevel but for semicolons inside braces
    std::string cur;
    int depth = 0;
    for (size_t i = 0; i < inner.size(); ++i) {
        char c = inner[i];
        if (c == '{') { depth++; cur.push_back(c); }
        else if (c == '}') { depth--; cur.push_back(c); }
        else if (c == ';' && depth == 0) {
            if (!cur.empty()) {
                out.push_back(parseElementString(cur));
                cur.clear();
            }
        } else {
            cur.push_back(c);
        }
    }
    if (!cur.empty()) out.push_back(parseElementString(cur));
    return out;
}

static std::shared_ptr<DocumentElement> parseElementString(const std::string& s) {
    if (s.rfind("Paragraph:", 0) == 0) {
        return std::make_shared<Paragraph>(s.substr(std::string("Paragraph:").size()));
    }
    if (s.rfind("Image:", 0) == 0) {
        return std::make_shared<Image>(s.substr(std::string("Image:").size()));
    }
    if (s.rfind("Table:", 0) == 0) {
        return std::make_shared<Table>(s.substr(std::string("Table:").size()));
    }
    if (s.rfind("Section:", 0) == 0) {
        // find first '{'
        auto pos = s.find('{');
        std::string title;
        std::string inner;
        if (pos != std::string::npos) {
            title = s.substr(std::string("Section:").size(), pos - std::string("Section:").size());
            // find last '}'
            auto end = s.rfind('}');
            if (end != std::string::npos && end > pos) inner = s.substr(pos+1, end - pos -1);
            auto sec = std::make_shared<Section>(title);
            if (!inner.empty()) {
                auto children = parseChildrenInsideBraces(inner);
                for (auto& c : children) if (c) sec->add(c);
            }
            return sec;
        } else {
            return std::make_shared<Section>(s.substr(std::string("Section:").size()));
        }
    }
    return nullptr;
}

// Implement Document::deserialize using the above parser
inline void Document::deserialize(const std::string& data) {
    elements.clear();
    std::istringstream iss(data);
    std::string line;
    if (!std::getline(iss, line)) return;
    if (line.rfind("Header:", 0) == 0) {
        header = line.substr(std::string("Header:").size());
    }
    while (std::getline(iss, line)) {
        if (line.empty()) continue;
        auto e = parseElementString(line);
        if (e) elements.push_back(e);
    }
    notify();
}
