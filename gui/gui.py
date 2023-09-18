import tkinter as tk
from gui_elements.cache import Cache
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
    canvas = tk.Canvas(window, width=canvas_width, height=canvas_height)
    canvas.pack()

    #Dibujar la memoria compartida
    memory = Memory(canvas, 600,50)
    memory.draw()
    #Dibujar las PUs
    PE1 = ProcessingElement(canvas, 200,700, "PE1")
    PE1.draw()
    PE2 = ProcessingElement(canvas, 600,700, "PE2")
    PE2.draw()
    PE3 = ProcessingElement(canvas, 1000,700, "PE3")
    PE3.draw()
    #Dibujar las Caches
    Cache1 = Cache(canvas, 200,400, "Cache 1")
    Cache1.draw()
    Cache2 = Cache(canvas, 600,400, "Cache 2")
    Cache2.draw()
    Cache3 = Cache(canvas, 1000,400, "Cache 3")
    Cache3.draw()
    #Iniciar la aplicación
    window.mainloop()

if __name__ == "__main__":
    main()