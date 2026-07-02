#pragma once
#include <string>
#include <memory>
#include <iostream>

struct Event {
    std::string type;
    std::string target; // optional target type (e.g., "Image", "Paragraph")
    int x{0}, y{0};
};

class EventHandler {
public:
    virtual ~EventHandler() = default;
    void setNext(std::shared_ptr<EventHandler> n) { next = n; }
    bool handle(const Event& ev) {
        if (canHandle(ev)) {
            process(ev);
            return true;
        } else if (next) {
            return next->handle(ev);
        }
        return false;
    }
protected:
    virtual bool canHandle(const Event& ev) = 0;
    virtual void process(const Event& ev) = 0;
private:
    std::shared_ptr<EventHandler> next;
};

class ClickImageHandler : public EventHandler {
protected:
    bool canHandle(const Event& ev) override {
        return ev.type == "click" && ev.target == "Image";
    }
    void process(const Event& ev) override {
        std::cout << "ClickImageHandler handled click on image at (" << ev.x << "," << ev.y << ")\n";
    }
};

class ClickParagraphHandler : public EventHandler {
protected:
    bool canHandle(const Event& ev) override {
        return ev.type == "click" && ev.target == "Paragraph";
    }
    void process(const Event& ev) override {
        std::cout << "ClickParagraphHandler handled click on paragraph at (" << ev.x << "," << ev.y << ")\n";
    }
};
