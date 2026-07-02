Final Project: สร้าง Framework สำหรับแอปพลิเคชันแก้ไขเอกสารเชิงโครงสร้าง (A Framework for a Structured Document Editor)
เป้าหมายสูงสุด:

สร้าง Core Framework สำหรับโปรแกรมแก้ไขเอกสาร ซึ่งเป็นไลบรารีที่สามารถนำไปต่อยอดเป็นแอปพลิเคชันเต็มรูปแบบได้ (เช่น แอปบน Console, GUI, หรือ Web) โดยหัวใจหลักคือการออกแบบสถาปัตยกรรมภายในด้วย Design Patterns และหลักการ SOLID อย่างครบถ้วน

ความต้องการของ Framework (Framework Requirements)
Framework ของคุณจะต้องมีองค์ประกอบและความสามารถดังต่อไปนี้ โดยแต่ละข้อถูกออกแบบมาเพื่อทดสอบความเข้าใจใน Design Pattern ที่เฉพาะเจาะจง:

หมวดที่ 1: Creational Patterns - การสร้างอ็อบเจกต์

Singleton: สร้างคลาส ApplicationSettings สำหรับเก็บการตั้งค่าส่วนกลาง (เช่น ชื่อฟอนต์เริ่มต้น, ขนาดกระดาษ) โดยใช้ Singleton Pattern เพื่อให้แน่ใจว่ามีการตั้งค่าเพียงชุดเดียวในโปรแกรม

Builder: สร้าง DocumentBuilder สำหรับการสร้างอ็อบเจกต์ Document ที่มีความซับซ้อน เช่น การกำหนดขนาดหน้า, ระยะขอบ, และหัวกระดาษ/ท้ายกระดาษ (Header/Footer) ตั้งแต่เริ่มต้น (ใช้ Builder Pattern)

Factory Method: สร้าง ElementFactory ที่มีเมธอดสำหรับสร้างองค์ประกอบเอกสาร (DocumentElement) ชนิดต่างๆ เช่น Paragraph, Image, Table เพื่อให้ง่ายต่อการเพิ่มองค์ประกอบชนิดใหม่ในอนาคต (ใช้ Factory Method Pattern)

Prototype: องค์ประกอบเอกสารทุกชิ้นจะต้องสามารถ "คัดลอก" ตัวเองได้ (Clonable) เพื่อรองรับฟังก์ชัน Copy/Paste ในอนาคต (ใช้ Prototype Pattern)

หมวดที่ 2: Structural Patterns - การจัดโครงสร้าง

Composite: เอกสารต้องรองรับโครงสร้างแบบต้นไม้ โดยมี Section ที่สามารถบรรจุองค์ประกอบอื่นๆ (รวมถึง Section ย่อย) ได้ ทำให้สามารถจัดการองค์ประกอบเดี่ยวและกลุ่มองค์ประกอบในลักษณะเดียวกัน (ใช้ Composite Pattern)

Decorator: สร้าง Decorator สำหรับ "ตกแต่ง" องค์ประกอบที่เป็นข้อความ เช่น BoldDecorator, ItalicDecorator เพื่อเพิ่มการจัดรูปแบบได้แบบไดนามิก (ใช้ Decorator Pattern)

Flyweight: สำหรับการจัดรูปแบบตัวอักษร (Character-level formatting) ให้ใช้ Flyweight Pattern เพื่อแชร์คุณสมบัติที่ซ้ำกัน (เช่น Font, Size, Color) และลดการใช้หน่วยความจำ

Proxy: สร้าง ImageProxy ซึ่งเป็น Virtual Proxy สำหรับอ็อบเจกต์ Image โดยจะยังไม่โหลดไฟล์รูปภาพจริงๆ จนกว่าจะมีการเรียกใช้เมธอด .draw() เพื่อเพิ่มประสิทธิภาพ

Bridge: แยกส่วนของ "โมเดล" เอกสาร (DocumentElement) ออกจาก "วิธีการแสดงผล" (Renderer) โดยสิ้นเชิง สร้าง Interface IRenderer และคลาสลูกเช่น ConsoleRenderer และ HTMLRenderer (ใช้ Bridge Pattern)

Facade: สร้าง FileManagerFacade ที่มี Interface ง่ายๆ เช่น .save(document, path) และ .load(path) เพื่อซ่อนความซับซ้อนของกระบวนการ Serialization (เช่น การแปลงเป็น JSON/XML) และการจัดการไฟล์

Adapter: สมมติว่ามีไลบรารีภายนอกสำหรับวาดรูปทรงเรขาคณิต (LegacyShapeDrawer) ที่มี Interface ไม่เข้ากัน ให้สร้าง Adapter เพื่อให้ไลบรารีนี้สามารถวาดรูปทรงในระบบของคุณได้

หมวดที่ 3: Behavioral Patterns - การจัดการพฤติกรรม

Command & Memento: ทุกการกระทำที่แก้ไขเอกสารต้องถูกห่อหุ้มด้วย Command Pattern และใช้ Memento Pattern เพื่อบันทึกสถานะ ทำให้สามารถ Undo/Redo ได้

Observer: สร้าง StatusBar ที่เป็น Observer คอยสังเกตการณ์ Document (Observable) เพื่ออัปเดตข้อมูลเช่น จำนวนคำ หรือจำนวนหน้า โดยอัตโนมัติเมื่อเอกสารเปลี่ยนแปลง

State: ตัว Document เองต้องมีสถานะเช่น DraftState, ReviewState, PublishedState ซึ่งจะเปลี่ยนพฤติกรรมของเมธอดบางอย่าง (เช่น .edit() อาจทำงานได้เฉพาะในสถานะ Draft) โดยใช้ State Pattern

Strategy: สร้างกลยุทธ์การ Export ที่แตกต่างกัน (IExportStrategy) เช่น ExportAsPDF, ExportAsMarkdown ซึ่ง Client สามารถเลือกสับเปลี่ยนได้ตอนรันไทม์ (ใช้ Strategy Pattern)

Iterator: Implement Iterator เพื่อให้สามารถวนลูปดูองค์ประกอบทั้งหมดในโครงสร้าง Composite ของเอกสารได้

Visitor: สร้าง IDocumentVisitor เช่น WordCountVisitor หรือ XMLExportVisitor เพื่อทำการประมวลผลที่ซับซ้อนกับองค์ประกอบทุกชิ้นในเอกสาร

Chain of Responsibility: (ส่วนเสริม) สร้างสายโซ่ของการประมวลผล Event เช่น การคลิกเมาส์ ที่จะถูกส่งต่อไปตามลำดับชั้นขององค์ประกอบจนกว่าจะมีผู้จัดการ Event นั้น

Mediator: (ส่วนเสริม) หากมีการสร้าง UI พื้นฐาน ให้ใช้ Mediator เพื่อจัดการการสื่อสารที่ซับซ้อนระหว่างปุ่ม, เมนู, และพื้นที่แสดงผล

Template Method: สร้าง Base Class DocumentValidator ที่มีขั้นตอนการตรวจสอบเป็นลำดับ (validate()) แต่เปิดให้ Subclass implement รายละเอียดของแต่ละขั้นตอน (เช่น checkSpelling(), checkGrammar())

Interpreter: (ส่วนเสริมขั้นสูง) สร้างระบบ Macro ง่ายๆ ที่ผู้ใช้สามารถพิมพ์คำสั่ง เช่น "BOLD ALL HEADINGS" แล้วโปรแกรมจะแปลและทำงานตามนั้น

 

สิ่งที่ต้องส่ง
Source Code: โปรเจกต์ C++ ทั้งหมด

เอกสารประกอบ (README.md):

อธิบายการออกแบบ: อธิบายสั้นๆ ว่าคุณนำ Design Pattern แต่ละตัวไปใช้แก้ปัญหาในส่วนไหนของโปรเจกต์และเพราะอะไร

Class Diagram: (ไม่บังคับแต่แนะนำ) แผนภาพคลาสอย่างง่ายเพื่อแสดงโครงสร้างโดยรวม

วิธีคอมไพล์และรัน: คำสั่งพื้นฐานในการใช้งานโปรแกรม

เกณฑ์การให้คะแนน (100 คะแนน)
70% - การประยุกต์ใช้ Design Patterns:

ความถูกต้องในการ implement Patterns ที่เป็น แกนหลัก (บังคับ) (50 คะแนน)

การผสมผสาน Patterns ต่างๆ ให้ทำงานร่วมกันได้อย่างลงตัว (20 คะแนน)

20% - การออกแบบและคุณภาพโค้ด:

การปฏิบัติตามหลักการ SOLID

การใช้ Modern C++ features อย่างเหมาะสม (Smart Pointers, STL, etc.)

ความสะอาดและความเป็นระเบียบของโค้ด

10% - ความสมบูรณ์และเอกสารประกอบ:

โปรแกรมทำงานได้ครบตามฟังก์ชันหลักที่กำหนด

เอกสาร README.md อธิบายการออกแบบได้ชัดเจนและครบถ้วน