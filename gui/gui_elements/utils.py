class Utils:

    def move_arrow(coordinates, x_offset, y_offset):
        offset_coordinates = [x + x_offset if i % 2 == 0 else x + y_offset for i, x in enumerate(coordinates)]
        return offset_coordinates

    def increase_vertical_down_arrow_length(coordinates, lenght):
        coordinates[7] -= lenght
        coordinates[9] -= lenght

        return coordinates
    
    def increase_vertical_up_arrow_length(coordinates, lenght):
        coordinates[7] += lenght
        coordinates[9] += lenght

        return coordinates