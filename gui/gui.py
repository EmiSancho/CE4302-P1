import tkinter as tk
import constants
from gui_elements.address_bus import AddressBus
from gui_elements.data_bus import DataBus
from gui_elements.cache import Cache
from gui_elements.shared import Shared
from gui_elements.memory import Memory
from gui_elements.processing_element import ProcessingElement

def main():
    # Crear la ventana principal
    window = tk.Tk()
    window.resizable(False, False)
    window.title("Proyecto 1 Arquitectura de Computadores 2")

    # Tamaño del canvas
    canvas_width = 1600
    canvas_height = 900

    #Canvas en la ventana
    canvas = tk.Canvas(window, width=canvas_width, height=canvas_height, bg="white")
    canvas.pack()

    # Etiqueta con el título llamativo    
    canvas.create_text(150, 50, text="MESI", font=constants.TITLE_FONT)

    #Dibujar la memoria compartida
    memory = Memory(canvas, 390,30)
    memory.draw()
    memory.paint_cell(2, constants.PALE_BLUE)
    #Dibujar las PEs
    PE1 = ProcessingElement(canvas, 200,750, "PE1")
    PE1.draw()
    PE2 = ProcessingElement(canvas, 600,750, "PE2")
    PE2.draw()
    PE3 = ProcessingElement(canvas, 1000,750, "PE3")
    PE3.draw()
    #Dibujar las Caches
    Cache1 = Cache(canvas, 200,550, "Cache 1")
    Cache1.draw()
    Cache2 = Cache(canvas, 600,550, "Cache 2")
    Cache2.draw()
    Cache2.paint_cell(2, constants.PALE_RED, "val1", "val2", "val3")
    Cache1.paint_cell(3, constants.PALE_GREEN, "val1", "val2", "val3")
    Cache3 = Cache(canvas, 1000,550, "Cache 3")
    Cache3.draw()
    #Dibujar Data Bus
    dataBus = DataBus(canvas)
    dataBus.draw()

    #Dibujar Address Bus
    add = AddressBus(canvas)
    add.draw()

    #Dibujar Data Bus
    shared = Shared(canvas)
    shared.draw()

    #Iniciar la aplicación
    window.mainloop()



if __name__ == "__main__":
    main()