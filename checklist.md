# Checklist for Final Project — Structured Document Editor Framework

Repository: Non-Spk/document-editor

สิ่งที่ต้องทำตามโจทย์ (Checklist) และสถานะปัจจุบัน

---

## หมวดที่ 1: Creational Patterns

- [x] Singleton: ApplicationSettings
  - สถานะ: Done
  - ไฟล์: include/ApplicationSettings.h
  - หมายเหตุ: ใช้ Meyers singleton (static local) เพื่อให้มี instance เดียว

- [x] Builder: DocumentBuilder
  - สถานะ: Done
  - ไฟล์: include/Builder.h
  - หมายเหตุ: DocumentBuilder ช่วยกำหนด header/footer และสร้าง Document

- [x] Factory Method: ElementFactory
  - สถานะ: Done
  - ไฟล์: include/ElementFactory.h
  - หมายเหตุ: สร้าง Paragraph, Image, Table, Section ผ่าน ElementFactory::create

- [x] Prototype: clone บน DocumentElement
  - สถานะ: Done
  - ไฟล์: include/DocumentElement.h, include/Elements.h
  - หมายเหตุ: ทุก Element มีเมธอด clone() เพื่อรองรับ copy/paste

---

## หมวดที่ 2: Structural Patterns

- [x] Composite: Section (สามารถมี children)
  - สถานะ: Done
  - ไฟล์: include/Elements.h

- [x] Decorator: BoldDecorator, ItalicDecorator
  - สถานะ: Done
  - ไฟล์: include/Decorator.h
  - หมายเหตุ: Decorator ห่อหุ้ม DocumentElement (text-like)

- [x] Flyweight: FontFactory
  - สถานะ: Done
  - ไฟล์: include/Flyweight.h
  - หมายเหตุ: แชร์ Font instance ตาม key (name|size|color)

- [x] Proxy: ImageProxy (virtual proxy)
  - สถานะ: Done
  - ไฟล์: include/ImageProxy.h
  - หมายเหตุ: lazy-load RealImage เมื่อ render/draw ถูกเรียก

- [x] Bridge: IRenderer, ConsoleRenderer, HTMLRenderer
  - สถานะ: Done
  - ไฟล์: include/IRenderer.h
  - หมายเหตุ: แยก model (DocumentElement) ออกจาก renderer

- [x] Facade: FileManagerFacade
  - สถานะ: Done (basic)
  - ไฟล์: include/FileManagerFacade.h
  - หมายเหตุ: มี .save() และ .load() และ Document::deserialize ถูก implement แล้ว

- [x] Adapter: LegacyShapeDrawer Adapter
  - สถานะ: Done
  - ไฟล์: include/Adapter.h
  - หมายเหตุ: ShapeDrawerAdapter adapts LegacyShapeDrawer to IRenderer

---

## หมวดที่ 3: Behavioral Patterns

- [x] Command & Memento: ICommand, AddElementCommand, Memento via serialize string
  - สถานะ: Done
  - ไฟล์: include/Command.h, include/CommandImpl.h, include/Builder.h (memento methods)
  - หมายเหตุ: Command เก็บ memento เป็น string; CommandManager logic ถูกปรับปรุง

- [x] Observer: StatusBar observes Document
  - สถานะ: Done
  - ไฟล์: include/Observer.h
  - หมายเหตุ: Document::attach/notify มีอยู่แล้ว (observer เก็บเป็น raw pointer เพื่อความเรียบง่าย)

- [x] State: DraftState, ReviewState, PublishedState
  - สถานะ: Done
  - ไฟล์: include/State.h
  - หมายเหตุ: Document::canEdit() ขึ้นกับ state; Document::setState ใช้ unique_ptr

- [x] Strategy: IExportStrategy (ExportAsMarkdown, ExportAsPlainText)
  - สถานะ: Done
  - ไฟล์: include/Strategy.h
  - หมายเหตุ: Document::setExportStrategy และ exportDocument มีอยู่แล้ว

- [x] Iterator: dedicated iterator for Composite
  - สถานะ: Done
  - ไฟล์: include/Iterator.h
  - หมายเหตุ: DocumentIterator ทำ DFS flattening ขององค์ประกอบ

- [x] Visitor: IDocumentVisitor, WordCountVisitor
  - สถานะ: Done
  - ไฟล์: include/IteratorVisitor.h
  - หมายเหตุ: Visitor ถูกใช้เพื่อคำนวณ word count และสามารถขยายเป็น XMLExportVisitor

- [x] Chain of Responsibility (Event handling)
  - สถานะ: Done
  - ไฟล์: include/Chain.h
  - หมายเหตุ: ตัวอย่าง ClickParagraphHandler และ ClickImageHandler ที่เชื่อมต่อกันเป็น chain

- [x] Mediator (UI)
  - สถานะ: Done (basic)
  - ไฟล์: include/Mediator.h
  - หมายเหตุ: UIMediator ช่วยจัดการการกระทำระหว่าง StatusBar และ Document (simple)

- [x] Template Method: DocumentValidator base class
  - สถานะ: Done
  - ไฟล์: include/Validator.h
  - หมายเหตุ: SimpleValidator เป็น subclass ที่ implement checks

- [x] Interpreter (Macro system)
  - สถานะ: Done (basic)
  - ไฟล์: include/Interpreter.h
  - หมายเหตุ: MacroInterpreter รองรับคำสั่งแบบง่าย เช่น "BOLD ALL HEADINGS"

---

## สถานะรวม

ตอนนี้โค้ดสามารถทำงานได้ตามเงื่อนไขใน checklist ทั้งหมดในรูปแบบพื้นฐาน (prototype/demo-ready).  

## วิธี build & run (ซ้ำ)

Requirements: CMake, C++17

Commands:

mkdir build && cd build
cmake ..
cmake --build .
./document-editor
