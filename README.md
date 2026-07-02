# Document Editor Framework

This repository contains a minimal C++ framework for a structured document editor, implemented to demonstrate many classic Design Patterns and SOLID principles.

Overview of implemented patterns:

- Singleton: ApplicationSettings (global configuration)
- Builder: DocumentBuilder to construct Document with header/footer
- Factory Method: ElementFactory creates Paragraph, Image, Table, Section
- Prototype: DocumentElement::clone implemented on elements
- Composite: Section contains children DocumentElements
- Decorator: BoldDecorator, ItalicDecorator wrapping text elements
- Flyweight: FontFactory sharing Font instances
- Proxy: ImageProxy (virtual proxy for lazy image loading)
- Bridge: DocumentElement uses IRenderer implementations (ConsoleRenderer, HTMLRenderer)
- Facade: FileManagerFacade for save/load
- Adapter: (placeholder for integrating legacy drawer, can be extended)
- Command & Memento: AddElementCommand + Document Memento via serialization string
- Observer: StatusBar observes Document changes
- State: DraftState/ReviewState/PublishedState controlling editability
- Strategy: Export strategies (Markdown, PlainText)
- Iterator/Visitor: WordCountVisitor visits elements for word counting

Build & run

Requirements: CMake, C++17

Commands:

mkdir build && cd build
cmake ..
cmake --build .
./document-editor

Design notes

See include/ for header-only implementations. The code is intentionally simplified to focus on patterns rather than full product features.


