#pragma once
#include <string>
#include <iostream>

class DocumentValidator {
public:
    virtual ~DocumentValidator() = default;
    bool validate(const Document& doc) {
        if (!checkStructure(doc)) return false;
        if (!checkSpelling(doc)) return false;
        if (!checkGrammar(doc)) return false;
        return true;
    }
protected:
    virtual bool checkStructure(const Document& doc) = 0;
    virtual bool checkSpelling(const Document& doc) = 0;
    virtual bool checkGrammar(const Document& doc) = 0;
};

class SimpleValidator : public DocumentValidator {
protected:
    bool checkStructure(const Document& doc) override {
        // simple check: document has a header
        return !doc.serialize().empty();
    }
    bool checkSpelling(const Document& doc) override {
        // placeholder: always true
        return true;
    }
    bool checkGrammar(const Document& doc) override {
        // placeholder
        return true;
    }
};
