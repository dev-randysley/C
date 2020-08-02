#ifndef CONECTIVIDAD_H_INCLUDED
#define CONECTIVIDAD_H_INCLUDED

#include "Persona.h"
#include "ConjuntoPersonas.h"

using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavPersona::Persona;

namespace UndavConectividad{

    struct Conexiones;

    Conexiones* Crear(ConjuntoPersonas* red);

    void Conectar(Conexiones* conexion,Persona* origen,Persona* destino);

    bool EstanConectados(Conexiones* conexion,Persona* primera,Persona* segunda);

    void Destruir(Conexiones* conexion);
}

#endif // CONECTIVIDAD_H_INCLUDED
