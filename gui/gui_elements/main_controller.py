from gui_elements.address_bus import AddressBus
from gui_elements.data_bus import DataBus
from gui_elements.cache import Cache
from gui_elements.shared import Shared
from gui_elements.memory import Memory
from gui_elements.processing_element import ProcessingElement
import constants

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
    def start_button(self, protocol):   
        self.canvas.create_rectangle(50, 20, 250, 120, fill="white", outline="white")
        # Etiqueta con el título   
        self.canvas.create_text(150, 50, text=protocol, font=constants.TITLE_FONT)
        self.actual = 0

        # Abre el archivo en modo lectura
        with open('./log.txt', 'r') as archivo:
            # Lee las líneas del archivo y elimina el carácter de nueva línea
            self.actual_log = [linea.strip() for linea in archivo.readlines()]
    
    def step_button(self):
        print(self.actual_log[self.actual])
        self.actual+=1
    