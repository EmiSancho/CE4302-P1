#include <iostream>
#include "../mem/main_mem.cpp"
#include "../pe/pe.cpp"

class Moesi{

private:
    logger& log = logger::getInstance();
    MainMemory& memory = MainMemory::getInstance(); //SINGLETON

    std::vector <int> metrics;
    int writeAccessMem = 0;
    int invalidations = 0;
    int readAccessMem = 0;

    // Invalida los estados de los caches externos cuando el local hace writeMESI de una direccion que comparten
    void invalidateCaches(std::string address, PE& peExternal1, PE& peExternal2){
        if (peExternal1.CACHE.exists(address)){
            peExternal1.CACHE.updateValue(peExternal1.CACHE.getEntry(address).getID(), StateEnum::Invalid, address, peExternal1.CACHE.getEntry(address).getData());
            invalidations +=1;
            log.logCacheUpdate(peExternal1.processor_id,address,"I");
        }     
        if (peExternal2.CACHE.exists(address)){
            peExternal2.CACHE.updateValue(peExternal2.CACHE.getEntry(address).getID(), StateEnum::Invalid, address, peExternal2.CACHE.getEntry(address).getData());
            invalidations +=1;
            log.logCacheUpdate(peExternal1.processor_id,address,"I");
        }
    }

    //Escribo en cache y memoria y estoy en E
    void writeThrough(std::string address, int data, PE& peLocal, PE& peExternal1, PE& peExternal2){
        //Paso al estado E y Escribo el valor de data en la cache local
        peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Modified, address, data);
        //Escribo el valor de data en memoria
        memory.write(address, peLocal.CACHE.getEntry(address).getData());
        writeAccessMem +=1;
        //Invalido los demas caches
        invalidateCaches(address, peExternal1, peExternal2);
    }
    
    //Escribo en memoria cuando estoy en M
    void writeBack(PE& peWB, std::string address){
        //Escribo el valor del cache en memoria
        memory.write(address, peWB.CACHE.getEntry(address).getData());
        writeAccessMem +=1;
        //Paso al estado a Owned
        peWB.CACHE.updateValue(peWB.CACHE.getEntry(address).getID(), StateEnum::Owned, address, peWB.CACHE.getEntry(address).getData());   
    }

public:

    //Verificar que los cambios se mantengan en el interconnect
    Moesi() {
    }

    // Metodo para leer un dato de la cache
    int readMOESI(std::string address, PE& peLocal, PE& peExternal1, PE& peExternal2) {
        //verifico si existe en el cache local
        if (peLocal.CACHE.exists(address)){
            // Si devuelve true, verificar estado del entry que tiene el address
            switch (peLocal.CACHE.getEntry(address).getStatus()) {
                //Si el estado esta en M, E, S entonces devuelvo el valor local
                case StateEnum::Modified:
                case StateEnum::Owned:
                case StateEnum::Exclusive: 
                case StateEnum::Shared:
                    // Devolver valor local
                    return peLocal.CACHE.getEntry(address).getData();
                    break;
                //Si esta en I, tengo que buscar el valor en las otras caches
                case StateEnum::Invalid:
                    //Si la cache externa 1 tiene el address con estado M o E
                    if (peExternal1.CACHE.exists(address)){
                        switch (peExternal1.CACHE.getEntry(address).getStatus()) {

                            //Si esta en estado E
                            case StateEnum::Exclusive:
                                //Actualizo el valor del cache local por el valor en memoria y cambio el estado a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Cambio el estado del cache externo a S
                                peExternal1.CACHE.updateValue(peExternal1.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal1.CACHE.getEntry(address).getData());
                                //Tomo el dato del cache local
                                return peLocal.CACHE.getEntry(address).getData();
                                break;
                            //Si esta en estado M
                            case StateEnum::Modified:
                                // Escribo en memoria en el address y paso el estado de Cache External a O
                                writeBack(peExternal1, address);
                                // Escribir en cache local el valor actualizado y cambiar su estado a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                // Tomo el dato de cache local que se ha actualizado
                                return peLocal.CACHE.getEntry(address).getData();
                                break;
                            //Si esta en estado O
                            case StateEnum::Owned:
                                // Escribo en memoria en el address y paso el estado de Cache External a O
                                writeBack(peExternal1, address);
                                // Escribir en cache local el valor actualizado y cambiar su estado a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                // Tomo el dato de cache local que se ha actualizado
                                return peLocal.CACHE.getEntry(address).getData();
                                break;
                        }
                    }
                    //Si la cache externa 2 tiene el address con estado M o E
                    else if(peExternal2.CACHE.exists(address)){
                        switch (peExternal2.CACHE.getEntry(address).getStatus()) {
                            //Si esta en estado E
                            case StateEnum::Exclusive:
                                //Actualizo el valor del cache local por el valor en memoria y cambio el estado a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Cambio el estado del cache externo a S
                                peExternal2.CACHE.updateValue(peExternal2.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal2.CACHE.getEntry(address).getData());
                                //Tomo el dato del cache local
                                return peLocal.CACHE.getEntry(address).getData();
                                break;
                            //Si esta en estado M
                            case StateEnum::Modified:
                                // Escribo en memoria en el address y paso el estado de Cache External a S
                                writeBack(peExternal2, address);
                                // Escribir en cache local el valor actualizado y cambiar su estado a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                // Tomo el dato de cache local que se ha actualizado
                                return peLocal.CACHE.getEntry(address).getData();
                                break;
                            //Si esta en estado O
                            case StateEnum::Owned:
                                // Escribo en memoria en el address y paso el estado de Cache External a O
                                writeBack(peExternal2, address);
                                // Escribir en cache local el valor actualizado y cambiar su estado a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                // Tomo el dato de cache local que se ha actualizado
                                return peLocal.CACHE.getEntry(address).getData();
                                break;
                        }
                    }else{
                        //Tomar el valor de memoria, luego escribo en cache local el valor y paso al estado E
                        peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Exclusive, address, memory.read(address));
                        readAccessMem +=1;
                        return peLocal.CACHE.getEntry(address).getData();
                        break;
                    } 
            }
        }
        // Si no existe en cache local
        else{
            // Verifico si la direccion existe en la cache externa 1
            if (peExternal1.CACHE.exists(address)){
                switch (peExternal1.CACHE.getEntry(address).getStatus()) {
                    case StateEnum::Modified:
                        // Escribo en memoria en el address y paso el estado de Cache External a S
                        writeBack(peExternal1, address);
                        // Escribir en cache local el valor actualizado y cambiar su estado a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        // Tomo el dato de cache local que se ha actualizado
                        return peLocal.CACHE.getEntry(address).getData();
                        break;
 
                    //Si el estado esta en E
                    case StateEnum::Exclusive:
                        //Asigno en un entry local el valor en memoria y cambio el estado a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Cambio el estado del cache externo a S
                        peExternal1.CACHE.updateValue(peExternal1.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal1.CACHE.getEntry(address).getData());
                        //Tomo el dato del cache local
                        return peLocal.CACHE.getEntry(address).getData();
                        break;

                    //Si el estado esta en S
                    case StateEnum::Shared:
                        //Asigno en un entry local el valor en memoria y cambio el estado a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Tomo el dato del cache local
                        return peLocal.CACHE.getEntry(address).getData();
                        break;
                }
            }
            //Verifico si la direccion existe en la cache externa 2
            if (peExternal2.CACHE.exists(address)){
                switch (peExternal2.CACHE.getEntry(address).getStatus()) {
                    case StateEnum::Modified:
                        // Escribo en memoria en el address y paso el estado de Cache External a S
                        writeBack(peExternal2, address);
                        // Escribir en cache local el valor actualizado y cambiar su estado a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        // Tomo el dato de cache local que se ha actualizado
                        return peLocal.CACHE.getEntry(address).getData();
                        break;
                        
                    //Si el estado esta en E
                    case StateEnum::Exclusive:
                        //Asigno en un entry local el valor en memoria y cambio el estado a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Cambio el estado del cache externo a S
                        peExternal2.CACHE.updateValue(peExternal2.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal2.CACHE.getEntry(address).getData());
                        //Tomo el dato del cache local
                        return peLocal.CACHE.getEntry(address).getData();
                        break;

                    //Si el estado esta en E
                    case StateEnum::Shared:
                        //Asigno en un entry local el valor en memoria y cambio el estado a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Tomo el dato del cache local
                        return peLocal.CACHE.getEntry(address).getData();
                        break;
                }
            }
            //Existe solo en memoria
            else{
                // Buscar el dato de la direccion directamente en memoria
                peLocal.CACHE.loadValue(StateEnum::Exclusive, address, memory.read(address)); 
                readAccessMem +=1;
                return peLocal.CACHE.getEntry(address).getData();
            }
        }
        return 0;
    }

    // Metodo para escribir un dato en la cache
    void writeMOESI(std::string address, int data, PE& peLocal, PE& peExternal1, PE& peExternal2) {
        // Si existe el address en el cache local
        if(peLocal.CACHE.exists(address)){
            // Verifico el estado del entry
            switch (peLocal.CACHE.getEntry(address).getStatus()) {
                //Si el estado es M
                case StateEnum::Modified:
                    //Escribo en cache local
                    peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Modified, address, data);
                    invalidateCaches(address, peExternal1, peExternal2);
                    break;
                //Si el estado es O
                case StateEnum::Owned:
                    //Escribo en cache local
                    peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Modified, address, data);
                    invalidateCaches(address, peExternal1, peExternal2);
                    break;
                //Si el estado es E
                case StateEnum::Exclusive:
                    //Escribo en cache local y paso al estado M
                    peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Modified, address, data);
                    invalidateCaches(address, peExternal1, peExternal2);
                    break;
                //Si el estado es S
                case StateEnum::Shared:
                    //Escribo directamente a memoria (WriteThrough), invalido los demas caches que tengan esa direccion y me asigno estado E
                    writeThrough(address, data, peLocal, peExternal1, peExternal2);
                    break;
                case StateEnum::Invalid:
                    if (peExternal1.CACHE.exists(address)){
                        //Verifico el estado del cache externo 1
                        switch (peExternal1.CACHE.getEntry(address).getStatus()) {
                            //Si el estado es M
                            case StateEnum::Modified:
                                //La cache externa debe escribir en memoria (WriteBack) y paso al estado S
                                writeBack(peExternal1, address);
                                //Leo el dato desde memoria y paso estado del cache local S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;
                            case StateEnum::Owned:
                                //La cache externa debe escribir en memoria (WriteBack) y paso al estado S
                                writeBack(peExternal1, address);
                                //Leo el dato desde memoria y paso estado del cache local S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;
                            //Si el estado esta en E
                            case StateEnum::Exclusive:
                                //Paso el estado del cache externo a S
                                peExternal1.CACHE.updateValue(peExternal1.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal1.CACHE.getEntry(address).getData());
                                //Leo el dato desde memoria y paso al estado del cache local S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;

                            //Si el estado esta en S
                            case StateEnum::Shared:
                                //Leo el dato desde memoria y paso al estado del cache local a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;
                        }
                    }
                    else if (peExternal2.CACHE.exists(address)){
                        //Verifico el estado del cache externo 2
                        switch (peExternal2.CACHE.getEntry(address).getStatus()) {
                            //Si el estado es M
                            case StateEnum::Modified:
                                //La cache externa debe escribir en memoria (WriteBack) y paso al estado S
                                writeBack(peExternal2, address);
                                //Leo el dato desde memoria y paso estado del cache local S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;

                            //Si el estado es O
                            case StateEnum::Owned:
                                //La cache externa debe escribir en memoria (WriteBack) y paso al estado S
                                writeBack(peExternal2, address);
                                //Leo el dato desde memoria y paso estado del cache local S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;

                            //Si el estado esta en E
                            case StateEnum::Exclusive:
                                //Paso el estado del cache externo a S
                                peExternal2.CACHE.updateValue(peExternal2.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal2.CACHE.getEntry(address).getData());
                                //Leo el dato desde memoria y paso al estado del cache local S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;

                            //Si el estado esta en S
                            case StateEnum::Shared:
                                //Leo el dato desde memoria y paso al estado del cache local a S
                                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                                readAccessMem +=1;
                                //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                                //...Paso el entry del cache local a estado E
                                writeThrough(address, data, peLocal, peExternal1, peExternal2);
                                break;
                        }
                    }else{
                        //Tomar el valor de memoria, luego escribo en cache local el valor y paso al estado M
                        peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Modified, address, data);
                        break;
                    }     
            }

        }else {
            //Verifico cache externo 1
            if(peExternal1.CACHE.exists(address)){
                //Verifico el estado del cache externo 1
                switch (peExternal1.CACHE.getEntry(address).getStatus()) {
                    //Si el estado es M
                    case StateEnum::Modified:
                        //La cache externa debe escribir en memoria (WriteBack) y paso al estado O
                        writeBack(peExternal1, address);
                        //Leo el dato desde memoria y paso estado del cache local S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;

                    //Si el estado es O
                    case StateEnum::Owned:
                        //La cache externa debe escribir en memoria (WriteBack) y paso al estado O
                        writeBack(peExternal1, address);
                        //Leo el dato desde memoria y paso estado del cache local S
                        peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;
                        
                    //Si el estado esta en E
                    case StateEnum::Exclusive:
                        //Paso el estado del cache externo a S
                        peExternal1.CACHE.updateValue(peExternal1.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal1.CACHE.getEntry(address).getData());
                        //Leo el dato desde memoria y paso al estado del cache local S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;

                    //Si el estado esta en S
                    case StateEnum::Shared:
                        //Leo el dato desde memoria y paso al estado del cache local a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;
                }
            }
            //Existe en cache externo 2
            else if(peExternal2.CACHE.exists(address)){
                //Verifico el estado del cache externo 2
                switch (peExternal2.CACHE.getEntry(address).getStatus()) {
                    //Si el estado es M
                    case StateEnum::Modified:
                        //La cache externa debe escribir en memoria (WriteBack) y paso al estado S
                        writeBack(peExternal2, address);
                        //Leo el dato desde memoria y paso estado del cache local S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;
                    //Si el estado es O
                    case StateEnum::Owned:
                        //La cache externa debe escribir en memoria (WriteBack) y paso al estado O
                        writeBack(peExternal2, address);
                        //Leo el dato desde memoria y paso estado del cache local S
                        peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;
                        
                    //Si el estado esta en E
                    case StateEnum::Exclusive:
                        //Paso el estado del cache externo a S
                        peExternal2.CACHE.updateValue(peExternal2.CACHE.getEntry(address).getID(), StateEnum::Shared, address, peExternal2.CACHE.getEntry(address).getData());
                        //Leo el dato desde memoria y paso al estado del cache local S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;

                    //Si el estado esta en S
                    case StateEnum::Shared:
                        //Leo el dato desde memoria y paso al estado del cache local a S
                        peLocal.CACHE.loadValue(StateEnum::Shared, address, memory.read(address));
                        readAccessMem +=1;
                        //Escribo el valor de la cache local directamente a memoria (WriteThrough) e invalido los caches que tenian la direccion...
                        //...Paso el entry del cache local a estado E
                        writeThrough(address, data, peLocal, peExternal1, peExternal2);
                        break;
                }
            }
            //Existe solo en memoria
            else{
                //Tomar el valor de memoria, paso el estado a E y luego escribo en cache local el valor y paso al estado M
                peLocal.CACHE.loadValue(StateEnum::Exclusive, address, memory.read(address));
                readAccessMem +=1;
                peLocal.CACHE.updateValue(peLocal.CACHE.getEntry(address).getID(), StateEnum::Modified, address, data);
            }
        }
    }

    void incrementMOESI(std::string address, PE& peLocal, PE& peExternal1, PE& peExternal2) {
        int data = readMOESI(address, peLocal, peExternal1, peExternal2);
        writeMOESI(address, data+1, peLocal, peExternal1, peExternal2);
    }

    std::vector<int> returnMetrics(){
        metrics.push_back(writeAccessMem);
        metrics.push_back(readAccessMem);
        metrics.push_back(invalidations);
        return metrics;
    }

};
