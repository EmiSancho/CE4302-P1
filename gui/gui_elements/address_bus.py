from .figure import Figure
from .utils import Utils
import constants

class AddressBus(Figure):
    def __init__(self, canvas):
        super().__init__(canvas)
        self.addres_bus_coordinates = []
        self.addres_bus_to_cache = []
        self.addres_bus_to_memory = []
        self.memory_to_addres_bus = []


    def draw(self):
        self.addres_bus_coordinates = Utils.move_arrow(constants.HORIZONTAL_ARROW_POLYGON_CORDINATES, 0, 100)
        self.draw_address_bus_arrow("black")

        addres_bus_to_memory = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 315, 25)
        self.addres_bus_to_memory = Utils.increase_vertical_up_arrow_length(addres_bus_to_memory, 60)
        memory_to_addres_bus = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 315, 160)
        self.memory_to_addres_bus = Utils.increase_vertical_down_arrow_length(memory_to_addres_bus, 60)
        self.draw_memory_to_address_bus_arrow(2, "black")

        address_bus_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 55, 285)
        address_bus_to_cache_temp = Utils.increase_vertical_down_arrow_length(address_bus_to_cache_temp, 30)
        cache_to_address_bus_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 55, 180)
        cache_to_address_bus_temp = Utils.increase_vertical_up_arrow_length(cache_to_address_bus_temp, 30)

        self.addres_bus_to_cache.append([address_bus_to_cache_temp, cache_to_address_bus_temp])

        address_bus_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 455, 285)
        address_bus_to_cache_temp = Utils.increase_vertical_down_arrow_length(address_bus_to_cache_temp, 30)
        cache_to_address_bus_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 455, 180)
        cache_to_address_bus_temp = Utils.increase_vertical_up_arrow_length(cache_to_address_bus_temp, 30)

        self.addres_bus_to_cache.append([address_bus_to_cache_temp, cache_to_address_bus_temp])

        address_bus_to_cache_temp = Utils.move_arrow(constants.VERTICAL_DOWN_ARROW_POLYGON_CORDINATES, 855, 285)
        address_bus_to_cache_temp = Utils.increase_vertical_down_arrow_length(address_bus_to_cache_temp, 30)
        cache_to_address_bus_temp = Utils.move_arrow(constants.VERTICAL_UP_ARROW_POLYGON_CORDINATES, 855, 180)
        cache_to_address_bus_temp = Utils.increase_vertical_up_arrow_length(cache_to_address_bus_temp, 30)

        self.addres_bus_to_cache.append([address_bus_to_cache_temp, cache_to_address_bus_temp])

        self.draw_address_bus_to_cache_arrow(1, 2, "black")
        self.draw_address_bus_to_cache_arrow(2, 2, "black")
        self.draw_address_bus_to_cache_arrow(3, 2, "black")


    def draw_memory_to_address_bus_arrow(self, selector, color):
        if selector == 0:
            self.canvas.create_polygon(self.memory_to_addres_bus, fill="white", outline="white")
            self.canvas.create_polygon(self.addres_bus_to_memory, fill=color, outline=color)
        elif selector == 1:
            self.canvas.create_polygon(self.addres_bus_to_memory, fill="white", outline="white")
            self.canvas.create_polygon(self.memory_to_addres_bus, fill=color, outline=color)
        else:
            self.canvas.create_polygon(self.memory_to_addres_bus, fill=color, outline=color)
            self.canvas.create_polygon(self.addres_bus_to_memory, fill=color, outline=color)

    def draw_address_bus_to_cache_arrow(self, cache_number, selector, color):
        if selector == 0:
            self.canvas.create_polygon(self.addres_bus_to_cache[cache_number-1][0], fill="white", outline="white")
            self.canvas.create_polygon(self.addres_bus_to_cache[cache_number-1][1], fill=color, outline=color)            
        elif selector == 1:
            self.canvas.create_polygon(self.addres_bus_to_cache[cache_number-1][1], fill="white", outline="white")
            self.canvas.create_polygon(self.addres_bus_to_cache[cache_number-1][0], fill=color, outline=color) 
        else:
            self.canvas.create_polygon(self.addres_bus_to_cache[cache_number-1][0], fill=color, outline=color)
            self.canvas.create_polygon(self.addres_bus_to_cache[cache_number-1][1], fill=color, outline=color)  
                
    def draw_address_bus_arrow(self, color):
        self.canvas.create_polygon(self.addres_bus_coordinates, fill=color, outline="black")
        self.canvas.create_text(280, 410, text="Address Bus", font=self.figure_name_font)