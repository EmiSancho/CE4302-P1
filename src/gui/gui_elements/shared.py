from .figure import Figure
from .utils import Utils
import constants

class Shared(Figure):
    def __init__(self, canvas):
        super().__init__(canvas)
        self.shared_coordinates = []
        self.shared_to_cache = []

    def draw(self):
        self.shared_coordinates = Utils.move_arrow(constants.HORIZONTAL_ARROW_POLYGON_CORDINATES, -20, 160)
        self.draw_shared_arrow("black")

        shared_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, -27, 285)
        shared_to_cache_temp = Utils.increase_vertical_down_arrow_length(shared_to_cache_temp, -30)
        cache_to_shared_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, -27, 240)
        cache_to_shared_temp = Utils.increase_vertical_up_arrow_length(cache_to_shared_temp, -30)

        self.shared_to_cache.append([shared_to_cache_temp, cache_to_shared_temp])

        shared_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 371, 285)
        shared_to_cache_temp = Utils.increase_vertical_down_arrow_length(shared_to_cache_temp, -30)
        cache_to_shared_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 371, 240)
        cache_to_shared_temp = Utils.increase_vertical_up_arrow_length(cache_to_shared_temp, -30)

        self.shared_to_cache.append([shared_to_cache_temp, cache_to_shared_temp])

        shared_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 771, 285)
        shared_to_cache_temp = Utils.increase_vertical_down_arrow_length(shared_to_cache_temp, -30)
        cache_to_shared_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 771, 240)
        cache_to_shared_temp = Utils.increase_vertical_up_arrow_length(cache_to_shared_temp, -30)

        self.shared_to_cache.append([shared_to_cache_temp, cache_to_shared_temp])

        self.draw_shared_to_cache_arrow(1,2,"black")
        self.draw_shared_to_cache_arrow(2,2,"black")
        self.draw_shared_to_cache_arrow(3,2,"black")

    def draw_shared_arrow(self, color):
        self.canvas.create_polygon(self.shared_coordinates, fill=color, outline="black")
        self.canvas.create_text(255, 470, text="Shared", font=self.figure_name_font)

    def draw_shared_to_cache_arrow(self, cache_number, selector, color):
        if selector == 0:
            self.canvas.create_polygon(self.shared_to_cache[cache_number-1][0], fill="white", outline="white")
            self.canvas.create_polygon(self.shared_to_cache[cache_number-1][1], fill=color, outline=color)            
        elif selector == 1:
            self.canvas.create_polygon(self.shared_to_cache[cache_number-1][1], fill="white", outline="white")
            self.canvas.create_polygon(self.shared_to_cache[cache_number-1][0], fill=color, outline=color) 
        else:
            self.canvas.create_polygon(self.shared_to_cache[cache_number-1][0], fill=color, outline=color)
            self.canvas.create_polygon(self.shared_to_cache[cache_number-1][1], fill=color, outline=color)  
        
