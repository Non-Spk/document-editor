#include <iostream>
#include "ApplicationSettings.h"
#include "IRenderer.h"
#include "Elements.h"
#include "ElementFactory.h"
#include "Builder.h"
#include "Decorator.h"
#include "Flyweight.h"
#include "ImageProxy.h"
#include "FileManagerFacade.h"
#include "Command.h"
#include "CommandImpl.h"
#include "Observer.h"
#include "State.h"
#include "Strategy.h"
#include "IteratorVisitor.h"
#include "Iterator.h"
#include "Adapter.h"
#include "Chain.h"
#include "Validator.h"
#include "Interpreter.h"
#include "Mediator.h"

int main() {
    using namespace std;
    // Singleton
    ApplicationSettings::instance().setDefaultFont("Arial");

    // Build document
    DocumentBuilder builder;
    auto doc = builder.header("My Header").footer("Page 1").build();

    // Observer
    auto sb = make_shared<StatusBar>();
    doc->attach(sb.get());

    // Factory
    auto p1 = ElementFactory::create(ElementFactory::Type::ParagraphT, "Hello world from paragraph 1");
    auto p2 = ElementFactory::create(ElementFactory::Type::ParagraphT, "Another paragraph here");
    auto img = std::make_shared<ImageProxy>("/path/to/image.png");

    // Composite
    auto sec = std::make_shared<Section>("Introduction");
    sec->add(p1);
    sec->add(img);
    sec->add(p2);

    doc->addElement(sec);

    // Decorator
    auto boldP = std::make_shared<BoldDecorator>(p2);
    doc->addElement(boldP);

    // Flyweight
    FontFactory ff;
    auto f1 = ff.get("Arial", 12, "black");
    auto f2 = ff.get("Arial", 12, "black");
    cout << "Font instances same: " << (f1 == f2) << "\n";

    // Command + Memento
    CommandManager cm;
    auto p3 = ElementFactory::create(ElementFactory::Type::ParagraphT, "Inserted via command");
    cm.executeCommand(std::make_unique<AddElementCommand>(doc, p3));

    // Visitor
    WordCountVisitor wcv;
    for (auto& e : doc->getElements()) e->accept(wcv);
    cout << "Word count: " << wcv.getCount() << "\n";

    // Strategy
    doc->setExportStrategy(new ExportAsMarkdown());
    cout << "Export:\n" << doc->exportDocument() << "\n";

    // Rendering (Bridge)
    ConsoleRenderer cr;
    HTMLRenderer hr;
    cout << "Render with ConsoleRenderer:\n";
    for (auto& e : doc->getElements()) e->render(cr);

    cout << "Render with HTMLRenderer:\n";
    for (auto& e : doc->getElements()) e->render(hr);

    // Adapter (legacy drawer)
    auto legacy = make_shared<LegacyShapeDrawer>();
    ShapeDrawerAdapter adapter(legacy);
    adapter.renderImage("/path/to/image.png");

    // Chain of Responsibility
    auto h1 = make_shared<ClickParagraphHandler>();
    auto h2 = make_shared<ClickImageHandler>();
    h1->setNext(h2);
    Event ev{ "click", "Image", 15, 25 };
    h1->handle(ev);

    // Template Method (validator)
    SimpleValidator validator;
    cout << "Document valid: " << validator.validate(*doc) << "\n";

    // Interpreter (macro): BOLD ALL HEADINGS
    MacroInterpreter interp;
    interp.execute("BOLD ALL HEADINGS", doc);

    // Iterator
    DocumentIterator it(doc);
    cout << "Iterating document elements:\n";
    while (it.hasNext()) {
        auto e = it.next();
        if (e) cout << " - " << e->serialize() << "\n";
    }

    // Mediator (UI)
    UIMediator ui(doc);
    ui.setStatusBar(sb);
    ui.addParagraph("Added by mediator");
    ui.save("document.txt");

    // Facade: save
    FileManagerFacade::save(*doc, "document.txt");

    // Undo
    cm.undo();

    return 0;
}
