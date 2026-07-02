#pragma once
#include "Builder.h"
#include <string>

class DocumentState {
public:
    virtual ~DocumentState() = default;
    virtual bool canEdit() const = 0;
    virtual std::string name() const = 0;
};

class DraftState : public DocumentState {
public:
    bool canEdit() const override { return true; }
    std::string name() const override { return "Draft"; }
};
class ReviewState : public DocumentState {
public:
    bool canEdit() const override { return false; }
    std::string name() const override { return "Review"; }
};
class PublishedState : public DocumentState {
public:
    bool canEdit() const override { return false; }
    std::string name() const override { return "Published"; }
};

inline bool Document::canEdit() const {
    if (!state) return true; return state->canEdit();
}
