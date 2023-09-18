from .figure import Figure
from .utils import Utils
import constants

class AddressBus(Figure):
    def __init__(self, canvas):
        super().__init__(canvas)

    def draw(self):
        offset_coordinates = Utils.move_arrow(constants.HORIZONTAL_ARROW_POLYGON_CORDINATES, 0, 100)
        # Dibujar la flecha en el canvas
        self.canvas.create_polygon(offset_coordinates, fill="black", outline="black")