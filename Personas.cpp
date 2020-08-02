#include "Persona.h"
#include "TipoFormato.h"
#include "ConjuntoPersonas.h"
#include <string>
#include <iostream>
using std::string;
using std::to_string;
using UndavPersona::Persona;
using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::IteradorConjuntoPersonas;
int IDnuevo = 0;

struct UndavPersona::Persona{
    string nombre;
    string apellido;
    int iD;
    int cantidadAmigos;
    ConjuntoPersonas* amigos;
};

//Precondicion: -
//Postcondicion: Devuelve una cantidad incrementada del ID
int AsignarID();

string ObtenerAmigosCSV(ConjuntoPersonas* personas);

UndavPersona::Persona* UndavPersona::CrearPersona(string nombre, string apellido){

	Persona *nuevaPersona = new Persona;
	nuevaPersona->nombre = nombre;
	nuevaPersona->apellido = apellido;
	nuevaPersona->iD = AsignarID();
	nuevaPersona->cantidadAmigos = 0;
	nuevaPersona->amigos = UndavConjuntoPersonas::Crear();
	return nuevaPersona;
}

int AsignarID(){

    return IDnuevo++;
}

int UndavPersona::ObtenerId(const Persona* persona){

    return persona->iD;
}

string UndavPersona::ObtenerNombre(const Persona* persona){

	return persona->nombre;
}

void UndavPersona::CambiarNombre(Persona* persona, string nombre){

	persona->nombre = nombre;
}

string UndavPersona::ObtenerApellido(const Persona* persona){

	return persona->apellido;
}

void UndavPersona::CambiarApellido(Persona* persona, string apellido){

	persona->apellido = apellido;
}

void UndavPersona::AgregarAmigo(Persona* persona, Persona* amigo){

    UndavConjuntoPersonas::Agregar(persona->amigos,amigo);
}

void* UndavPersona::ObtenerAmigos(Persona* persona){

    return (void*)persona->amigos;
}

int UndavPersona::ObtenerCantidadAmigos(const Persona* persona){

    return UndavConjuntoPersonas::CantidadPersonas(persona->amigos);
}

bool UndavPersona::SonAmigos(const Persona* persona, Persona* otraPersona){

	return UndavConjuntoPersonas::Contiene(persona->amigos,otraPersona);
}

string UndavPersona::Serializar(const Persona* persona,TipoFormato formato){

    string serializado ="";
    string id = to_string(persona->iD);
    string cantidadAmigos = to_string(UndavConjuntoPersonas::CantidadPersonas(persona->amigos));
    string nombre = persona->nombre;
    string apellido = persona->apellido;
    string amigos = ObtenerAmigosCSV(persona->amigos);

    switch (formato){
        case TipoFormato::Expresivo:
            serializado += "["+id+"] "+nombre+" "+ apellido+" tiene amigos "+ cantidadAmigos;
            break;
        case TipoFormato::CSV:
              serializado += id+","+nombre+","+apellido+","+cantidadAmigos;
              break;
        case TipoFormato::Identificador:
            serializado += id;
            break;
        case TipoFormato::Json:
            serializado += "{id: "+ id+","+"nombre: "+nombre+","+"Apellido: "+apellido+","+"Amigos: "+amigos+"\n";
            break;
    }

	return serializado;
}

string ObtenerAmigosCSV(ConjuntoPersonas* personas){

    IteradorConjuntoPersonas* iterador = UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Comienzo(personas);
    IteradorConjuntoPersonas* siguiente = UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Comienzo(personas);
    UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Siguiente(siguiente);
    string palabraJSON= "";

    if(!UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::EsFin(iterador)){

        while(!UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::EsFin(siguiente)){

            Persona* persona = UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::ObtenerItem(iterador);

            palabraJSON = palabraJSON + to_string(persona->iD) +" , "+ persona->nombre +" , "+ persona->apellido +"\n";

            UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Siguiente(iterador);
            UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Siguiente(siguiente);
        }
        Persona* persona = UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::ObtenerItem(iterador);
        palabraJSON = palabraJSON + to_string(ObtenerId(persona)) +" , " +ObtenerNombre(persona) +" , "+ ObtenerApellido(persona);

        UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Destruir(iterador);
        return palabraJSON;
     }
}

bool UndavPersona::SonIguales(const Persona* persona,const Persona* otraPersona){

    return (persona->iD == otraPersona->iD);
}

void UndavPersona::Destruir(Persona* persona){

    UndavConjuntoPersonas::Destruir(persona->amigos);
	delete persona;
}
