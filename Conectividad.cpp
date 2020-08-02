#include "Conectividad.h"
#include "Persona.h"
#include "ConjuntoPersonas.h"

using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavPersona::Persona;
using UndavConectividad::Conexiones;

int ObtenerIndice(Conexiones* conexion,Persona* persona);
void Inicializar(int* elementos,int cantidad);

struct UndavConectividad::Conexiones{
    Persona** personas;
    int cantidadElementos;
    int* vectorPosiciones;
};

void Inicializar(int* elementos,int cantidad){

    for(int i = 0; i < cantidad; i++)
        elementos[i] = i;
}

Conexiones* UndavConectividad::Crear(ConjuntoPersonas* red){

    Conexiones* conexion = new Conexiones;
    conexion->cantidadElementos = CantidadPersonas(red);
    conexion->personas = UndavConjuntoPersonas::ConvertirAVector(red);
    conexion->vectorPosiciones = new int[conexion->cantidadElementos];
    Inicializar(conexion->vectorPosiciones,conexion->cantidadElementos);
    return conexion;
}

void UndavConectividad::Conectar(Conexiones* conexion,Persona* origen,Persona* destino){

    int indicePersonaDestino = ObtenerIndice(conexion,destino);
    int indicePersonaOrigen = ObtenerIndice(conexion,origen);
    int identificadorDestino = conexion->vectorPosiciones[indicePersonaDestino];
    int identificadorOrigen = conexion->vectorPosiciones[indicePersonaOrigen];

    for(int i =0;i< conexion->cantidadElementos;i++)
        if(conexion->vectorPosiciones[i] == identificadorDestino)
            conexion->vectorPosiciones[i] = identificadorOrigen;
}

int ObtenerIndice(Conexiones* conexion,Persona* persona){

    for(int i = 0; i < conexion->cantidadElementos; i++)
        if(UndavPersona::SonIguales(conexion->personas[i],persona))
            return i;

}

bool UndavConectividad::EstanConectados(Conexiones* conexion,Persona* origen,Persona* destino){

    int indicePersonaDestino = ObtenerIndice(conexion,destino);
    int indicePersonaOrigen = ObtenerIndice(conexion,origen);

    return conexion->vectorPosiciones[indicePersonaDestino]== conexion->vectorPosiciones[indicePersonaOrigen];
}

void UndavConectividad::Destruir(Conexiones* conexion){

    delete []conexion->personas;
    delete []conexion->vectorPosiciones;
    delete conexion;
}
