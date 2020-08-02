#include "ConjuntoPersonas.h"
#include "Persona.h"
#include "Grafo.h"
#include "RedSocial.h"
#include "Conectividad.h"

using UndavConectividad::Conexiones;
using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavGrafoPersonas::GrafoPersonas;
using UndavPersona::Persona;
using UndavRedSocial::RedSocial;

struct UndavRedSocial::RedSocial{
    GrafoPersonas* red;
    GrafoPersonas* bosqueExpansion;
    Conexiones* conexion;
};

RedSocial* UndavRedSocial::CrearRedSocial(ConjuntoPersonas* personas){

    RedSocial* redSocial = new RedSocial;
    redSocial->red = UndavGrafoPersonas::CrearGrafo(personas);
    redSocial->bosqueExpansion = UndavGrafoPersonas::CrearGrafo(personas);
    redSocial->conexion= UndavConectividad::Crear(personas);

    return redSocial;
}

void UndavRedSocial::Conectar(RedSocial* redSocial,Persona* persona,Persona* otraPersona){

    UndavGrafoPersonas::Conectar(redSocial->red,persona,otraPersona);
    if(!EstanConectados(redSocial->conexion,persona,otraPersona)){
        Conectar(redSocial->conexion,persona,otraPersona);
        UndavGrafoPersonas::Conectar(redSocial->bosqueExpansion,persona,otraPersona);

    }
}

GrafoPersonas* UndavRedSocial::ObtenerRed(RedSocial* redSocial){

    return redSocial->red;
}

GrafoPersonas* UndavRedSocial::ObtenerBosqueExpansion(RedSocial* redSocial){

    return redSocial->bosqueExpansion;
}

void UndavRedSocial::Destruir(RedSocial* redSocial){

    UndavGrafoPersonas::Destruir(redSocial->bosqueExpansion);
    UndavGrafoPersonas::Destruir(redSocial->red);
    Destruir(redSocial->conexion);
    delete redSocial;
}
