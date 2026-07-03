# Structured Document Editor — Core Framework

A C++17 core library for a structured document editor. It is intentionally
**not** an application — it's a reusable engine that a Console app, GUI, or
Web backend could all be built on top of. The focus of this project is the
internal architecture: every one of the required Design Patterns is
implemented for real (not just named in a comment), and several of them are
deliberately wired together so you can see how they collaborate in a real
system.

## Build & Run

Requirements: a C++17 compiler (g++/clang++) and, optionally, CMake ≥ 3.10.

```bash
mkdir build && cd build
cmake ..
cmake --build .
./DocumentEditor
```

Or directly with g++, no CMake needed:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o DocumentEditor
./DocumentEditor
```

`main.cpp` runs a guided tour that exercises every pattern in sequence and
prints what's happening at each step.

## Architecture at a Glance

``` sh
DocumentElement (abstract)
 ├── Paragraph                (leaf)
 ├── RealImage                (leaf, "heavy" real subject)
 ├── ImageProxy                (leaf, Proxy for RealImage)
 ├── Section                  (composite: holds children, incl. sub-Sections)
 └── TextDecorator (abstract) (wraps a DocumentElement)
      ├── BoldDecorator
      └── ItalicDecorator

Document                       (root aggregate; owns a Section as its tree)
 ├── uses DocumentBuilder       (Builder)      to get constructed
 ├── implements IObservable     (Observer)     -> notifies StatusBar
 ├── holds a DocumentState      (State)        -> Draft/Review/Published
 ├── holds an IExportStrategy   (Strategy)     -> Markdown/PDF
 └── is the Memento Originator  (Memento)      -> createMemento/restoreMemento

IRenderer (abstract)           (Bridge target)
 ├── ConsoleRenderer

IDocumentVisitor (abstract)    (Visitor)
 ├── WordCountVisitor
 ├── XMLExportVisitor
 └── MarkdownExportVisitor      (used internally by the Strategy classes)
```

## Design Pattern Notes

### Creational

| Pattern | Where | Why |
| --- | --- | --- |
| **Singleton** | `ApplicationSettings` | One global source of truth for default font/page size. Meyers' singleton (function-local `static`) — lazy-initialized and thread-safe in C++11+, no manual lifetime management needed. |
| **Builder** | `DocumentBuilder` | `Document` construction involves several optional, order-independent fields (page size, margins, header, footer). The fluent builder keeps `Document`'s constructor simple and makes call sites self-documenting. |
| **Factory Method** | `ElementFactory` + `ParagraphFactory` / `ImageFactory` / `SectionFactory` | Client code creates elements through a common interface (`createElement()`); adding a new element type only means adding a new factory subclass, never touching existing call sites (Open/Closed Principle). |
| **Prototype** | `DocumentElement::clone()`, implemented by every concrete element (incl. deep-clone in `Section`) | Enables copy/paste and is directly reused as the mechanism behind the Memento snapshots — cloning a `Section` clones its whole subtree. |

### Structural

| Pattern | Where | Why |
| --- | --- | --- |
| **Composite** | `Section` | A `Section` *is* a `DocumentElement` and *contains* `DocumentElement`s (including nested `Section`s), so client code (rendering, word-counting, exporting) treats a single paragraph and a whole nested section identically. |
| **Decorator** | `TextDecorator` (abstract) → `BoldDecorator`, `ItalicDecorator` | Formatting is optional and combinable (`Bold(Italic(paragraph))`) without an explosion of subclasses like `BoldItalicParagraph`. Decorators forward `accept()` straight to the wrapped element, so a `WordCountVisitor` still "sees through" the formatting to the underlying text. |
| **Flyweight** | `CharacterFormat` + `CharacterFormatFactory` | Character-level formatting (font/size/color) repeats constantly across a document. The factory caches instances by intrinsic state so identical requests share one object instead of allocating a new one every time — demonstrated in `main.cpp` by comparing pointers. |
| **Proxy** | `ImageProxy` (virtual proxy for `RealImage`) | `RealImage`'s constructor simulates an expensive disk load. `ImageProxy` defers that cost until `.draw()` is actually called, and cloning a proxy doesn't force a load either. |
| **Bridge** | `IRenderer` (abstraction target) vs. `DocumentElement` hierarchy (the "model") | `DocumentElement::draw(IRenderer&)` never depends on a concrete renderer. Adding `HTMLRenderer` or a future `PDFRenderer` requires zero changes to `Paragraph`, `Section`, etc. |
| **Facade** | `FileManagerFacade` | `.save(doc, path)` / `.load(path)` hide the two-step process of (1) walking the tree with an `XMLExportVisitor` and (2) doing file I/O. Callers never see either step. |
| **Adapter** | `ShapeAdapter` wrapping `LegacyShapeDrawer` | `LegacyShapeDrawer` represents a pre-existing third-party API with an incompatible signature (`drawShapeAtLegacyCoords`). `ShapeAdapter` implements our `IShape` interface and translates calls, so the legacy library integrates without being modified. |

### Behavioral

| Pattern | Where | Why |
| --- | --- | --- |
| **Command + Memento** | `ICommand` / `AddElementCommand` / `CommandManager`, `DocumentMemento` | Every edit is an `ICommand` object so it can be executed, queued, and undone uniformly. `AddElementCommand::execute()` takes a `DocumentMemento` snapshot (via `Document::createMemento()`, itself built on `Section::clone()` — Prototype in action) *before* mutating; `undo()` restores it. `CommandManager` is the caretaker holding undo/redo stacks. |
| **Observer** | `IObservable`/`IObserver`, `Document` (subject) / `StatusBar` (observer) | `Document::addElement()` calls `notifyObservers()`; `StatusBar` reacts by recomputing word count via a `WordCountVisitor`. Adding more observers (e.g. a page-count widget) needs no changes to `Document`. |
| **State** | `DocumentState` → `DraftState` / `ReviewState` / `PublishedState` | `Document::edit()` delegates to the current state object instead of branching on an enum; transitioning `setState(...)` changes behavior at runtime without `Document` knowing the rules for each phase. |
| **Strategy** | `IExportStrategy` → `ExportAsMarkdown` / `ExportAsPDF` | Export format is swappable at runtime (`document->setExportStrategy(...)`). Both strategies reuse a `MarkdownExportVisitor` internally — a second example of Strategy + Visitor collaborating rather than duplicating traversal logic. |
| **Iterator** | `DocumentIterator`, `Section::createIterator()` | Flattens the composite tree into a pre-order sequence (`hasNext()`/`next()`) without exposing `Section`'s internal `std::vector`. |
| **Visitor** | `IDocumentVisitor` → `WordCountVisitor`, `XMLExportVisitor`, `MarkdownExportVisitor` | New whole-tree operations (counting words, exporting XML/Markdown) are added as new visitor classes, with zero changes to `Paragraph`/`Section`/etc. Decorators forward `accept()` to the wrapped element so visitors always see real content. |
| **Template Method** *(bonus)* | `DocumentValidator` → `BasicDocumentValidator` | `validate()` fixes the sequence `checkStructure → checkSpelling → checkGrammar`; subclasses only supply the individual checks. |

**Not implemented** (listed as optional "ส่วนเสริม" in the brief): Chain of
Responsibility, Mediator, Interpreter. The architecture doesn't preclude
adding them later — e.g. Chain of Responsibility would slot in naturally
as an event-handling layer once a real UI exists, and Mediator would
coordinate that UI's widgets.

## SOLID & Modern C++ Notes

- **SRP**: rendering (`IRenderer`), persistence (`FileManagerFacade`),
  traversal (`DocumentIterator`), and analysis (`*Visitor`) are all separate
  classes rather than bloating `Document` or `DocumentElement`.
- **OCP**: new element types (Factory Method), new renderers (Bridge), new
  export formats (Strategy), and new tree-wide operations (Visitor) are all
  additions, not modifications, to existing classes.
- **LSP**: every `DocumentElement` subclass (including decorators and the
  composite `Section`) can be used anywhere a `DocumentElement` is expected.
- **ISP**: `IObservable`/`IObserver`, `IRenderer`, `IExportStrategy`, and
  `IDocumentVisitor` are each narrow, single-purpose interfaces rather than
  one bloated "document interface."
- **DIP**: `Document` depends on the abstractions `DocumentState` and
  `IExportStrategy`, not concrete state/strategy classes; `DocumentElement`
  depends on the abstract `IRenderer`, not `ConsoleRenderer` directly.
- Ownership is expressed with `std::unique_ptr` throughout the element tree
  (single owner, moved into place), while `std::shared_ptr` is used only
  where sharing is the actual intent (`CharacterFormat` flyweights). No raw
  `new`/`delete` appears anywhere in the codebase.

## Known Simplifications

- `FileManagerFacade::load()` reads the saved XML back as raw text rather
  than reconstructing a full `Document` object graph — a complete XML
  parser was out of scope for a patterns-focused exercise, but the Facade's
  contract (a trivial `.save()`/`.load()` call hiding real complexity) is
  still fully demonstrated.
- `ExportAsPDF` produces a simulated PDF-like text envelope rather than a
  real binary PDF, since real PDF generation needs a graphics/binary
  library unrelated to the pattern being demonstrated.
