from gui_elements.address_bus import AddressBus
from gui_elements.data_bus import DataBus
from gui_elements.cache import Cache
from gui_elements.shared import Shared
from gui_elements.memory import Memory
from gui_elements.processing_element import ProcessingElement
import constants
import os

class MainController:
    
    _instance = None  # Almacena la instancia única

    def __new__(cls, canvas):
        # Verifica si ya hay una instancia creada
        if cls._instance is None:
            cls._instance = super(MainController, cls).__new__(cls)
            cls._instance.init_controller(canvas)
        return cls._instance

    def init_controller(self, canvas):
        self.canvas = canvas
        self.caches = []
        self.pes = []
        self.memory = None
        self.data_bus = None
        self.address_bus = None
        self.shared = None
        self.actual = 0
        self.actual_log = []
        self.initialize()


    def initialize(self):
        #Dibujar la memoria compartida
        self.memory = Memory(self.canvas, 390,30)
        self.memory.draw()

        #Dibujar las Caches
        Cache1 = Cache(self.canvas, 200,550, "Cache 1")
        Cache1.draw()
        Cache2 = Cache(self.canvas, 600,550, "Cache 2")
        Cache2.draw()
        Cache3 = Cache(self.canvas, 1000,550, "Cache 3")
        Cache3.draw()
        self.caches = [Cache1, Cache2, Cache3]

        #Dibujar Data Bus
        self.data_bus = DataBus(self.canvas)
        self.data_bus.draw()
        
        #Dibujar las PEs
        PE1 = ProcessingElement(self.canvas, 200,780, "PE1")
        PE1.draw()
        PE2 = ProcessingElement(self.canvas, 600,780, "PE2")
        PE2.draw()
        PE3 = ProcessingElement(self.canvas, 1000,780, "PE3")
        PE3.draw()
        self.pes = [PE1, PE2, PE3]

        #Dibujar Address Bus
        self.address_bus = AddressBus(self.canvas)
        self.address_bus.draw()

        #Dibujar Data Bus
        self.shared = Shared(self.canvas)
        self.shared.draw()
        
        self.canvas.create_rectangle(50, 20, 250, 120, fill="white", outline="white")

        # Etiqueta con el título   
        self.canvas.create_text(150, 50, text="----", font=constants.TITLE_FONT)

    # Función que se ejecutará cuando se haga clic en el botón "Start"
    def start_button(self):   
        self.canvas.create_rectangle(50, 20, 250, 120, fill="white", outline="white")
        # Etiqueta con el título   
        self.canvas.create_text(150, 50, text="protocol", font=constants.TITLE_FONT)
        self.actual = 0
        
        self.load_data()
    
    def load_data(self):
        #Abre el archivo en modo lectura
        with open('./results/log.txt', 'r') as file:
            #Lee las líneas del archivo y elimina el carácter de nueva línea
            self.actual_log = [line.strip() for line in file.readlines()]
            
        update_pos = 0
        for line in self.actual_log:
            elements = line.split('|')
            elements = [element.strip() for element in elements]
            self.actual_log[update_pos] = elements
            update_pos = update_pos + 1
        self.step_button()        
    
    def step_button(self):
        actual_data = self.actual_log[self.actual]
        print(actual_data)
        len_data = len(self.actual_log[self.actual])
        if len_data == 1:
            self.actual+=1
            self.step_button()
        elif len_data == 3:
            if actual_data[0] == "r":
                self.memory.paint_cell_with_data(actual_data[1],constants.PALE_GREEN, actual_data[2])
            elif actual_data[0] == "w":
                self.memory.paint_cell_with_data(actual_data[1],constants.PALE_GREEN, actual_data[2])
            else:
                pass
        elif len_data == 6:
            pe = actual_data[0]
            pe_num = pe.replace("PE", "")
            entry = actual_data[4]
            entry_pos = entry.replace("Entry", "")
            self.caches[int(pe_num) - 1].paint_cell(int(entry_pos) - 1, "WHITE", actual_data[2], actual_data[3], actual_data[5])

        else:
            pass  

        self.actual+=1