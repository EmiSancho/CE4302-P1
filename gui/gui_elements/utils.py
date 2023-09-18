class Utils:

    def move_arrow(coordinates, x_offset, y_offset):
        offset_coordinates = [x + x_offset if i % 2 == 0 else x + y_offset for i, x in enumerate(coordinates)]
        return offset_coordinates