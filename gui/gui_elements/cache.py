from .figure import Figure

class Cache(Figure):
    def __init__(self, canvas, x1, y1, cache_name):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.cache_name = cache_name

    def draw(self):
        section_width = 300
        section_height = 100
        y2 = self.y1 + section_height
        self.canvas.create_rectangle(self.x1, self.y1, self.x1 + section_width, y2, fill="white")
        center_x = (self.x1 + self.x1 + section_width) // 2
        center_y = (self.y1 + y2) // 2
        self.canvas.create_text(center_x, center_y, text=self.cache_name, font=self.font)
