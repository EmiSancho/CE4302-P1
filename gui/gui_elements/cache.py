from .figure import Figure

class Cache(Figure):
    def __init__(self, canvas, x1, y1, cache_name):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.cache_name = cache_name

    def draw(self):
        section_width = 300
        section_height = 160 // 4

        for i in range(4):
            self.canvas.create_rectangle(self.x1, self.y1 + section_height*i, self.x1 + section_width, self.y1+section_height*(i+1), fill="white")

        text_pos_x = self.x1 + section_width + 40
        text_pos_y = self.y1 - 20
        self.canvas.create_text(text_pos_x, text_pos_y, text=self.cache_name, font=self.figure_name_font)
           
            
        