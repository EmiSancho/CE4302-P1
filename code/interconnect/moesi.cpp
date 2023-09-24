#include <iostream>
#include "../pe+mem/cache-mem.cpp"
#include "../mem/main_mem.cpp"
#include "../pe+mem/pe.cpp"

// Estados del MOESI
enum CacheState { Modified, Owned, Exclusive, Shared, Invalid };
// Acciones de la cache
enum CacheEvent { WriteHit, ReadHit, WriteMiss, ReadMiss};



class Moesi{
public:
    Cache cache;

    Moesi(MainMemory memory, PE pe1, PE pe2, PE pe3){
    }

    // Método para leer un dato de la caché
    /*
    void read(int address) {
        if (lines.find(address) == lines.end() || lines[address].state == CacheState::Invalid) {
            // Cache read miss
            cache_event = CacheEvent::ReadMiss;
            return -1;  // Indica que no se encuentra en la caché
        } else {
            // Cache read hit
            cache_event = CacheEvent::ReadHit;
            return lines[address].data;
        }
    }

    // Método para escribir un dato en la caché
    void write(int address, int data, CacheState new_state) {
        if (lines.find(address) == lines.end()) {
            // La línea no existe en la cache, la creamos
            // Cache write miss
            cache_event = CacheEvent::WriteMiss;
            lines[address] = CacheLine();
            lines[address].data = data;
            lines[address].state = new_state;
        }else{
            // La linea existe en la cache y se puede actualizar
            // Cache write hit
            lines[address].data = data;
            lines[address].state = new_state;
            cache_event = CacheEvent::WriteHit;
        }
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
    */

};