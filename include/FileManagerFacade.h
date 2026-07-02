#pragma once
#include "Builder.h"
#include <fstream>
#include <iostream>

class FileManagerFacade {
public:
    static bool save(const Document& doc, const std::string& path) {
        std::ofstream ofs(path);
        if (!ofs) return false;
        ofs << doc.serialize();
        return true;
    }
    static std::shared_ptr<Document> load(const std::string& path) {
        std::ifstream ifs(path);
        if (!ifs) return nullptr;
        std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        auto db = DocumentBuilder();
        auto d = db.build();
        d->deserialize(data);
        return d;
    }
};
