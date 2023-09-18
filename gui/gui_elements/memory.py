from .figure import Figure

class Memory(Figure):
    def __init__(self, canvas, x1, y1):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.memory_cell_positions = list(range(0,16))
        self.entries = ["a0","a1", "a2", "a3", "a4","a5", "a6", "a7", "a8","a9", "a10", "a11", "a12","a13", "a14", "a15"]

    def draw(self):
        section_width = 300
        section_height = 120 // 4

        for i in range(16):
            y1 = self.y1 + i * section_height
            y2 = y1 + section_height
            self.canvas.create_rectangle(self.x1, y1, self.x1 + section_width, y2, fill="white")
            self.memory_cell_positions[i] = [self.x1, y1, self.x1 + section_width, y2]
            center_x = (self.x1 + self.x1 + section_width) // 2
            center_y = (y1 + y2) // 2
            self.canvas.create_text(center_x, center_y, text=self.entries[i], font=self.font)

    def paint_cell(self, cellNum, color):
        cell = self.memory_cell_positions[cellNum]
        self.canvas.create_rectangle(cell[0], cell[1], cell[2], cell[3], fill="#C0FFC0")
        # Dibujar el texto en la celda
        center_x = (cell[0] + cell[2]) / 2
        center_y = (cell[1] + cell[3]) / 2
        self.canvas.create_text(center_x, center_y, text=self.entries[cellNum], font=self.font)