from .figure import Figure

class ProcessingElement(Figure):
    def __init__(self, canvas, x1, y1, pu_Name):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.pu_Name = pu_Name

    def draw(self):
        section_width = 300
        section_height = 100
        y2 = self.y1 + section_height
        self.canvas.create_rectangle(self.x1, self.y1, self.x1 + section_width, y2, fill="white")
        center_x = (self.x1 + self.x1 + section_width) // 2
        center_y = (self.y1 + y2) // 2
        self.canvas.create_text(center_x, center_y, text=self.pu_Name, font=self.font)
