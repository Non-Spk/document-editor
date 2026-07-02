#pragma once
#include "Elements.h"
#include "Decorator.h"
#include <string>
#include <sstream>
#include <algorithm>

class MacroInterpreter {
public:
    // Supports a simple command: "BOLD ALL HEADINGS"
    void execute(const std::string& command, std::shared_ptr<Document> doc) {
        std::istringstream iss(command);
        std::string cmd, all, target;
        iss >> cmd >> all >> target; // e.g., BOLD ALL HEADINGS
        if (cmd == "BOLD" && all == "ALL" && target == "HEADINGS") {
            // for simplicity, treat each Section's title as a heading and bold all paragraph children
            for (auto& e : doc->getElements()) {
                if (auto sec = std::dynamic_pointer_cast<Section>(e)) {
                    for (size_t i = 0; i < sec->children.size(); ++i) {
                        if (auto p = std::dynamic_pointer_cast<Paragraph>(sec->children[i])) {
                            sec->children[i] = std::make_shared<BoldDecorator>(sec->children[i]);
                        }
                    }
                }
            }
        }
    }
};
