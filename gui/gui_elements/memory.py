from .figure import Figure

class Memory(Figure):
    def __init__(self, canvas, x1, y1):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.memory_cell_positions = list(range(0, 16))
        self.entries = ["a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10", "a11", "a12", "a13", "a14", "a15"]
        self.columns = 2  
        self.column1_entries = self.entries[:8]
        self.column2_entries = self.entries[8:]

    def draw(self):
        section_width = 350
        section_height = 120 // 4

        self.canvas.create_rectangle(self.x1 - 10, self.y1 - 10, self.x1 + 30 + section_width * self.columns, self.y1 + 10 + section_height * 8, outline="black")

        for i in range(16):
            column = i // 8  
            row = i % 8  
            x1 = self.x1 + column * section_width + column * 20  
            x2 = x1 + section_width
            y1 = self.y1 + row * section_height
            y2 = y1 + section_height

            self.canvas.create_rectangle(x1, y1, x2, y2, fill="white")
            self.memory_cell_positions[i] = [x1, y1, x2, y2]
            center_x = (x1 + x2) // 2
            center_y = (y1 + y2) // 2

            if column == 0:
                entry = self.column1_entries[row]
            else:
                entry = self.column2_entries[row]

            self.canvas.create_text(center_x, center_y, text=entry, font=self.font)


    def paint_cell(self, cellNum, color):
        cell = self.memory_cell_positions[cellNum]
        self.canvas.create_rectangle(cell[0], cell[1], cell[2], cell[3], fill="#C0FFC0")
        center_x = (cell[0] + cell[2]) / 2
        center_y = (cell[1] + cell[3]) / 2
        self.canvas.create_text(center_x, center_y, text=self.entries[cellNum], font=self.font)