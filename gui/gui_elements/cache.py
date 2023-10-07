from .figure import Figure

class Cache(Figure):
    def __init__(self, canvas, x1, y1, cache_name):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.cache_name = cache_name
        self.cell_positions = list(range(0,4))

    def draw(self):
        section_width = 300
        section_height = 160 // 4

        for i in range(4):
            y1 = self.y1 + section_height*i
            x2 = self.x1 + section_width
            y2 = self.y1+section_height*(i+1)
            self.cell_positions[i] = [self.x1, y1, x2, y2]

            self.canvas.create_rectangle(self.x1, y1, x2, y2, fill="white")

            center_y = (y1 + y2) // 2
            center_x = (self.x1+5 + self.x1 + 40) // 2
            self.canvas.create_rectangle(self.x1+5, y1+5, self.x1+40, y2-5, fill="white")
            self.canvas.create_text(center_x, center_y, text="--", font=self.cell_font)

            center_x = (self.x1+45 + self.x1+167) // 2
            self.canvas.create_rectangle(self.x1+45, y1+5, self.x1+167, y2-5, fill="white")
            self.canvas.create_text(center_x, center_y, text="--", font=self.cell_font)

            center_x = (self.x1+172 + self.x1+295) // 2
            self.canvas.create_rectangle(self.x1+172, y1+5, self.x1+295, y2-5, fill="white")
            self.canvas.create_text(center_x, center_y, text="--", font=self.cell_font)
            
            
        text_pos_x = self.x1 + section_width + 40
        text_pos_y = self.y1 - 20
        self.canvas.create_text(text_pos_x, text_pos_y, text=self.cache_name, font=self.figure_name_font)
           
    def paint_cell(self, cellNum, color, val1, val2, val3):
        cell = self.cell_positions[cellNum]
        x1 = cell[0]
        y1 = cell[1]
        y2 = cell[3]
        
        center_y = (y1 + y2) // 2
        center_x = (x1+5 + x1 + 40) // 2
        self.canvas.create_rectangle(x1+5, y1+5, x1+40, y2-5, fill=color)
        self.canvas.create_text(center_x, center_y, text=val1, font=self.cell_font)

        center_x = (x1+45 + x1+167) // 2
        self.canvas.create_rectangle(x1+45, y1+5, x1+167, y2-5, fill=color)
        self.canvas.create_text(center_x, center_y, text=val2, font=self.cell_font)

        center_x = (x1+172 + x1+295) // 2
        self.canvas.create_rectangle(x1+172, y1+5, x1+295, y2-5, fill=color)
        self.canvas.create_text(center_x, center_y, text=val3, font=self.cell_font)
            
        