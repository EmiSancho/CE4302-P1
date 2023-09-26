#include <iostream>
#include "../pe+mem/cache-mem.cpp"
#include "../mem/main_mem.cpp"
#include "../pe+mem/pe.cpp"

// Estados del MOESI
enum CacheState { Modified, Owned, Exclusive, Shared, Invalid };
// Acciones de la cache
enum CacheEvent { WriteHit, ReadHit, WriteMiss, ReadMiss};



class Moesi{
private:

    MainMemory memory;
    PE pe1, pe2, pe3;
    PE peLocal, peExternal1, peExternal2;

    void assignCacheID(int processor_id){
        if (processor_id == pe1.processor_id){
            peLocal = pe1;
            peExternal1 = pe2;
            peExternal2 = pe3;
        }else if(processor_id == pe2.processor_id){
            peLocal = pe2;
            peExternal1 = pe1;
            peExternal2 = pe3;
        }else if(processor_id == pe3.processor_id){
            peLocal = pe3;
            peExternal1 = pe1;
            peExternal2 = pe2;
        }else{
            std::cout << "Invalid processor id" << std::endl;
        }

    }

public:

    //Verificar que los cambios se mantengan en el interconnect
    Moesi(MainMemory memory, PE pe1, PE pe2, PE pe3){
        this->memory = memory;
        this->pe1 = pe1;
        this->pe2 = pe2;
        this->pe3 = pe3;
    }

    // Método para leer un dato de la cach
    void read(int origen_id, std::string address) {
        //Asignamos los id de las caches
        assignCacheID(origen_id);

        //verifico si existe en el cache local
            // Si devuelve true, verificar estado
                // Obtener cual entry tiene el address
                // Obtener estado entry
                    //Si esta en M, E, S entonces devuelvo el valor local

                    //Si esta en I, tengo que buscar el valor en las otras caches
                        //Alguna de las caches externas tiene que tener el address con estado M o E
                            //Si esta en estado E, paso los estados de las caches a S y tomo el dato de memoria
                            //Si esta en estado M, escribo en memoria en el address y luego paso los estados de las caches a S y tomo el dato de memoria
            // Si devuelve false
                //Verifico si la direccion existe en las caches externas
                    //Si existe, verifico el estado
                        //Si el estado esta en E
                            //Cambio el estado a S en ambas caches y leo el dato de memoria
                        //Si el estado enta en M
                            //Escribo en memoria en el address y luego paso los estados de ambas caches a S y tomo el dato de memoria
                        //Si el estado esta en S
                            //Leo el dato address directamente de memoria
                //Si la direccion no existe en las caches externas
                    // Leo el dato en memoria y paso al estado E
        
        if (peLocal.CACHE.exists(address)){
            switch (peLocal.CACHE.getEntry(address).getStatus()) {
                case StateEnum::Modified:
                case StateEnum::Exclusive: 
                case StateEnum::Shared:
                // Devolver valor local
                    peLocal.CACHE.getEntry(address).getData();
                    break;
                case StateEnum::Invalid:
                    if (peExternal1.CACHE.exists(address)){
                        switch (peExternal1.CACHE.getEntry(address).getStatus()) {
                            case StateEnum::Exclusive:
                                peLocal.CACHE.loadValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                peExternal1.CACHE.getEntry(address).setStatus(StateEnum::Shared);
                                
                                break;
                            case StateEnum::Modified:

                                break;
                        }   
                    }else if(peExternal2.CACHE.exists(address)){

                    }else{

                    }
                    break;
            }
           

        }
        // Caso cache externo
        // Caso Memoria
         
        
    }

    // Método para escribir un dato en la caché
    void write(int origen_id, std::string address, ) {

    }

    void changeState(int processor_id, int address){

        if (cache.lines[address].state == CacheState::Modified){
            switch (cache.cache_event){
                case (CacheEvent::WriteHit):

                    break;

                case (CacheEvent::ReadHit):

                    break;

                case (CacheEvent::WriteMiss):

                    break;
                case (CacheEvent::ReadMiss):

                    break;
                default:
                    break;
            }
        } else if (cache.lines[address].state == CacheState::Owned){
            switch (cache.cache_event){
                case (CacheEvent::WriteHit):

                    break;

                case (CacheEvent::ReadHit):

                    break;

                case (CacheEvent::WriteMiss):

                    break;
                case (CacheEvent::ReadMiss):

                    break;
                default:
                    break;
            }
        }else if (cache.lines[address].state == CacheState::Exclusive){
            switch (cache.cache_event){
                case (CacheEvent::WriteHit):

                    break;

                case (CacheEvent::ReadHit):

                    break;

                case (CacheEvent::WriteMiss):

                    break;
                case (CacheEvent::ReadMiss):

                    break;
                default:
                    break;
            }
        }else if (cache.lines[address].state == CacheState::Shared){
            switch (cache.cache_event){
                case (CacheEvent::WriteHit):

                    break;

                case (CacheEvent::ReadHit):

                    break;

                case (CacheEvent::WriteMiss):

                    break;
                case (CacheEvent::ReadMiss):

                    break;
                default:
                    break;
            }
        }else if (cache.lines[address].state == CacheState::Invalid){
            switch (cache.cache_event){
                case (CacheEvent::WriteHit):

                    break;

                case (CacheEvent::ReadHit):

                    break;

                case (CacheEvent::WriteMiss):

                    break;
                case (CacheEvent::ReadMiss):

                    break;
                default:
                    break;
            }
        }else{

        }

    }

};