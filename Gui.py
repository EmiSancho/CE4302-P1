import tkinter as tk

class Figure:
    def __init__(self, canvas):
        self.canvas = canvas

class Memory(Figure):
    def __init__(self, canvas, x1, y1):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1

    def draw(self):
        section_width = 300
        section_height = 120 // 4
        labels = ["a1", "a2", "a3", "a4"]

        for i in range(4):
            y1 = self.y1 + i * section_height
            y2 = y1 + section_height
            self.canvas.create_rectangle(self.x1, y1, self.x1 + section_width, y2, fill="white")
            center_x = (self.x1 + self.x1 + section_width) // 2
            center_y = (y1 + y2) // 2
            self.canvas.create_text(center_x, center_y, text=labels[i])

class ProcessingElement(Figure):
    def __init__(self, canvas, x1, y1, pu_Name):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.pu_Name = pu_Name

    def draw(self):
        section_width = 300
        section_height = 200
        y2 = self.y1 + section_height
        self.canvas.create_rectangle(self.x1, self.y1, self.x1 + section_width, y2, fill="white")
        center_x = (self.x1 + self.x1 + section_width) // 2
        center_y = (self.y1 + y2) // 2
        self.canvas.create_text(self.x1 + section_width, self.y1 , text=self.pu_Name)

class Cache(Figure):
    def __init__(self, canvas, x1, y1, cache_name):
        super().__init__(canvas)
        self.x1 = x1
        self.y1 = y1
        self.cache_name = cache_name

    def draw(self):
        section_width = 300
        section_height = 100
        y2 = self.y1 + section_height
        self.canvas.create_rectangle(self.x1, self.y1, self.x1 + section_width, y2, fill="white")
        center_x = (self.x1 + self.x1 + section_width) // 2
        center_y = (self.y1 + y2) // 2
        self.canvas.create_text(center_x, center_y, text=self.cache_name)


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
    PE1 = ProcessingElement(canvas, 200,600, "PE1")
    PE1.draw()
    PE2 = ProcessingElement(canvas, 600,600, "PE2")
    PE2.draw()
    PE3 = ProcessingElement(canvas, 1000,600, "PE3")
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