from .figure import Figure
from .utils import Utils
import constants

class DataBus(Figure):
    def __init__(self, canvas):
        super().__init__(canvas)
        self.data_bus_arrow = []    

        self.data_bus_to_memory_arrow = []
        self.memory_to_data_bus_arrow = []
        
        self.data_bus_to_cache = []

    def draw(self):
        self.data_bus_arrow = Utils.move_arrow(constants.HORIZONTAL_ARROW_POLYGON_CORDINATES, 0, 40)
        self.draw_data_bus_arrow("black")
        
        self.data_bus_to_memory_arrow = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 690, 25)
        self.memory_to_data_bus_arrow = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 690, 100)
        self.draw_memory_to_data_bus_arrow(-1)

        data_bus_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 183, 285)
        data_bus_to_cache_temp = Utils.increase_vertical_down_arrow_length(data_bus_to_cache_temp, 90)
        cache_to_data_bus_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 183, 120)
        cache_to_data_bus_temp = Utils.increase_vertical_up_arrow_length(cache_to_data_bus_temp, 90)

        self.data_bus_to_cache.append([data_bus_to_cache_temp, cache_to_data_bus_temp])

        data_bus_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 583, 285)
        data_bus_to_cache_temp = Utils.increase_vertical_down_arrow_length(data_bus_to_cache_temp, 90)
        cache_to_data_bus_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 583, 120)
        cache_to_data_bus_temp = Utils.increase_vertical_up_arrow_length(cache_to_data_bus_temp, 90)

        self.data_bus_to_cache.append([data_bus_to_cache_temp, cache_to_data_bus_temp])

        data_bus_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 983, 285)
        data_bus_to_cache_temp = Utils.increase_vertical_down_arrow_length(data_bus_to_cache_temp, 90)
        cache_to_data_bus_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 983, 120)
        cache_to_data_bus_temp = Utils.increase_vertical_up_arrow_length(cache_to_data_bus_temp, 90)

        self.data_bus_to_cache.append([data_bus_to_cache_temp, cache_to_data_bus_temp])

        self.draw_data_bus_to_cache_arrow(1, -1, "black")
        self.draw_data_bus_to_cache_arrow(2, -1, "black")
        self.draw_data_bus_to_cache_arrow(3, -1, "black")

        self.canvas.create_text(260, 350, text="Data Bus", font=self.figure_name_font)

    def draw_data_bus_to_cache_arrow(self, cache_number, selector, color):
        if selector == 0:
            self.canvas.create_polygon(self.data_bus_to_cache[cache_number-1][0], fill="white", outline="white")
            self.canvas.create_polygon(self.data_bus_to_cache[cache_number-1][1], fill=color, outline=color)            
        elif selector == 1:
            self.canvas.create_polygon(self.data_bus_to_cache[cache_number-1][1], fill="white", outline="white")
            self.canvas.create_polygon(self.data_bus_to_cache[cache_number-1][0], fill=color, outline=color) 
        else:
            self.canvas.create_polygon(self.data_bus_to_cache[cache_number-1][0], fill=color, outline=color)
            self.canvas.create_polygon(self.data_bus_to_cache[cache_number-1][1], fill=color, outline=color)  
        
    def draw_data_bus_arrow(self, color):
        self.canvas.create_polygon(self.data_bus_arrow, fill=color, outline="black")

    def draw_memory_to_data_bus_arrow(self, selector):
        if selector == 0:
            self.canvas.create_polygon(self.memory_to_data_bus_arrow, fill="white", outline="white")
            self.canvas.create_polygon(self.data_bus_to_memory_arrow, fill="black", outline="black")
        elif selector == 1:
            self.canvas.create_polygon(self.data_bus_to_memory_arrow, fill="white", outline="white")
            self.canvas.create_polygon(self.memory_to_data_bus_arrow, fill="black", outline="black")
        else:
            self.canvas.create_polygon(self.data_bus_to_memory_arrow, fill="black", outline="black")
            self.canvas.create_polygon(self.memory_to_data_bus_arrow, fill="black", outline="black")

