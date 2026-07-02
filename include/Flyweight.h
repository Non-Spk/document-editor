#pragma once
#include <string>
#include <memory>
#include <unordered_map>

struct Font {
    std::string name;
    int size;
    std::string color;
};

class FontFactory {
public:
    std::shared_ptr<Font> get(const std::string& name, int size, const std::string& color) {
        std::string key = name + "|" + std::to_string(size) + "|" + color;
        auto it = pool.find(key);
        if (it != pool.end()) return it->second;
        auto f = std::make_shared<Font>();
        f->name = name; f->size = size; f->color = color;
        pool[key] = f;
        return f;
    }
private:
    std::unordered_map<std::string, std::shared_ptr<Font>> pool;
};
