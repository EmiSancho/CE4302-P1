from .figure import Figure
from .utils import Utils
import constants

class ProcessingElement(Figure):
    def __init__(self, canvas, x1, y1, pu_Name):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.pu_Name = pu_Name
        self.arrows_to_cache = []

    def draw(self):
        section_width = 300
        section_height = 90
        y2 = self.y1 + section_height
        self.canvas.create_rectangle(self.x1, self.y1, self.x1 + section_width, y2, fill="white")
        center_x = (self.x1 + self.x1 + section_width) // 2
        center_y = (self.y1 + y2) // 2
        self.canvas.create_text(center_x, center_y, text=self.pu_Name, font=self.figure_name_font)

        arrow_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, center_x - 250, 515)
        arrow_to_cache_temp = Utils.increase_vertical_down_arrow_length(arrow_to_cache_temp, -20)
        cache_to_pe_arrow = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, center_x - 250, 460)
        cache_to_pe_arrow = Utils.increase_vertical_up_arrow_length(cache_to_pe_arrow, -20)

        self.arrows_to_cache.append([arrow_to_cache_temp, cache_to_pe_arrow])
        self.draw_arrows_to_cache(2, "black")


    def draw_arrows_to_cache(self, selector, color):
        if selector == 0:
            self.canvas.create_polygon(self.arrows_to_cache[0][0], fill="white", outline="white")
            self.canvas.create_polygon(self.arrows_to_cache[0][1], fill=color, outline=color)            
        elif selector == 1:
            self.canvas.create_polygon(self.arrows_to_cache[0][1], fill="white", outline="white")
            self.canvas.create_polygon(self.arrows_to_cache[0][0], fill=color, outline=color) 
        else:
            self.canvas.create_polygon(self.arrows_to_cache[0][0], fill=color, outline=color)
            self.canvas.create_polygon(self.arrows_to_cache[0][1], fill=color, outline=color)  


