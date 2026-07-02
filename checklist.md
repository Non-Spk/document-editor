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
  - หมายเหตุ: มี .save() และ .load() แต่การ deserialize ยังเป็น placeholder ต้องปรับปรุง

- [ ] Adapter: LegacyShapeDrawer Adapter (placeholder)
  - สถานะ: Not implemented (placeholder note in README)
  - ไฟล์: (ยังไม่มี)
  - แผน: เพิ่มคลาส adapter สำหรับสมมติ LegacyShapeDrawer (จะทำตามต้องการ)

---

## หมวดที่ 3: Behavioral Patterns

- [x] Command & Memento: ICommand, AddElementCommand, Memento via serialize string
  - สถานะ: Partially Done
  - ไฟล์: include/Command.h, include/Builder.h (memento methods)
  - หมายเหตุ: Command ห่อการเปลี่ยนแปลงและเก็บ memento เป็น string; แต่ undo/redo logic และการจัดการ snapshot ที่ปลอดภัยอาจต้องปรับให้แข็งแรงขึ้น (ปัจจุบันใช้ serialization string เป็น snapshot)

- [x] Observer: StatusBar observes Document
  - สถานะ: Done
  - ไฟล์: include/Observer.h
  - หมายเหตุ: Document::attach/notify มีอยู่แล้ว แต่ observer เก็บเป็น raw pointer — ควรปรับเป็น weak_ptr/registrar ในการปรับปรุง

- [x] State: DraftState, ReviewState, PublishedState
  - สถานะ: Done
  - ไฟล์: include/State.h
  - หมายเหตุ: Document::canEdit() ขึ้นกับ state; Document::setState ใช้ unique_ptr

- [x] Strategy: IExportStrategy (ExportAsMarkdown, ExportAsPlainText)
  - สถานะ: Done
  - ไฟล์: include/Strategy.h
  - หมายเหตุ: Document::setExportStrategy และ exportDocument มีอยู่แล้ว

- [ ] Iterator: dedicated iterator for Composite
  - สถานะ: Not implemented (สามารถ traverse ด้วย loops แต่ยังไม่มี iterator class)
  - ไฟล์: (ยังไม่มี)
  - แผน: เพิ่ม iterator class (เช่น DocumentIterator) ที่รองรับ DFS/BFS traversal

- [x] Visitor: IDocumentVisitor, WordCountVisitor
  - สถานะ: Done
  - ไฟล์: include/IteratorVisitor.h
  - หมายเหตุ: Visitor ถูกใช้เพื่อคำนวณ word count และสามารถขยายเป็น XMLExportVisitor

- [ ] Chain of Responsibility (Event handling)
  - สถานะ: Not implemented
  - แผน: สร้าง chain ของ EventHandler ที่ส่ง event ตามลำดับชั้นขององค์ประกอบ

- [ ] Mediator (UI) — Optional
  - สถานะ: Not implemented

- [ ] Template Method: DocumentValidator base class
  - สถานะ: Not implemented
  - แผน: สร้าง DocumentValidator::validate() ที่เรียก checkSpelling(), checkGrammar() (ให้ subclass implement)

- [ ] Interpreter (Macro system) — Optional/Advanced
  - สถานะ: Not implemented
  - แผน: เพิ่ม parser แบบง่ายที่แปลงคำสั่งเช่น "BOLD ALL HEADINGS" เป็น AST และ execute

---

## สถานะรวมและข้อเสนอแนะสำหรับลำดับถัดไป

สิ่งที่ทำเสร็จแล้ว (major features):
- Singleton, Builder, Factory Method, Prototype
- Composite, Decorator, Flyweight, Proxy, Bridge, Facade (basic)
- Command (basic), Memento (serialization snapshot), Observer, State, Strategy, Visitor

สิ่งที่ควรทำต่อเป็นลำดับแรก (แนะนำ):
1. ปรับปรุง Serialization/Deserialization ให้สมบูรณ์ (JSON) — เพื่อให้ save/load เป็นไปอย่างถูกต้อง (แนะนำใช้ nlohmann::json) — estimated 3–5 ชั่วโมง
2. ปรับปรุง Undo/Redo (Command + Memento) — ให้ Command เก็บ snapshot ของตนเองหรือเก็บ memento ที่ปลอดภัยกว่า และแก้ logic ของ CommandManager — estimated 2–4 ชั่วโมง
3. เพิ่ม Iterator แบบเป็นทางการสำหรับ Document traversal — estimated 1–2 ชั่วโมง
4. (เลือก) Implement Adapter สำหรับ LegacyShapeDrawer และ Template Method (DocumentValidator) — estimated 1–3 ชั่วโมง

---

## วิธี build & run (ซ้ำ)

Requirements: CMake, C++17

Commands:

mkdir build && cd build
cmake ..
cmake --build .
./document-editor

---

หากคุณอนุญาต ผมจะเริ่มงานต่อโดย: 1) เพิ่มไฟล์ checklist.md (ไฟล์นี้) — เสร็จแล้ว 2) เริ่ม implement การทำ Serialization/Deserialization เป็น JSON และปรับปรุง undo/redo ตามที่แนะนำ (รวมเป็น PR หรือ push ตรงไปยัง main ตามที่คุณต้องการ)

โปรดระบุว่าต้องการให้ผมเริ่มจากงานใด (เช่น "เริ่มที่ Serialization + Undo/Redo") หรือถ้าต้องการลำดับอื่นบอกมาได้เลยครับ
