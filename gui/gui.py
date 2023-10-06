import tkinter as tk
import constants
from gui_elements.main_controller import MainController

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

    #Instancia el controlador
    main_controller = MainController(canvas)

    # Etiqueta con el título   
    canvas.create_text(150, 50, text="MESI", font=constants.TITLE_FONT)

    # Crear un botón "Start"
    start_button = tk.Button(canvas, text="Start", command=main_controller.start_button_click, width=6, height=1, font=(12), bg="white")
    start_button.place(x=1200, y=50)

    # Crear un botón "Step"
    start_button = tk.Button(canvas, text="Step", command=main_controller.start_button_click, width=6, height=1, font=(12), bg="white")
    start_button.place(x=1275, y=50)

    #Iniciar la aplicación
    window.mainloop()

if __name__ == "__main__":
    main()