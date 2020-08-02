#include "Persona.h"
#include "ConjuntoPersonas.h"

using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavPersona::Persona;
using UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::IteradorConjuntoPersonas;

struct NodoPersona{
	Persona* item;
	NodoPersona* siguiente;
};

struct ListaPersonas{
	NodoPersona* primero;
	NodoPersona* ultimo;
};

struct UndavConjuntoPersonas::ConjuntoPersonas{
    ListaPersonas* personas ;
    int cantidadPersonas;
};

//funciones auxiliares
ListaPersonas* CrearListaPersonasVacia();
NodoPersona* CrearNodo(Persona* item,NodoPersona* siguiente);
NodoPersona* CrearUltimoNodoPersonas(Persona* item);
bool EstaVacia(ListaPersonas *lista);
void AgregarAlFinal(ListaPersonas* lista, Persona* item);
void EliminarNodoPosicion(ListaPersonas* lista,Persona* persona);
NodoPersona* ObtenerNodoAnterior(ListaPersonas*,Persona* persona);
void EliminarPrimerNodo(ListaPersonas* lista);
void EliminarUltimoNodo(ListaPersonas* lista);

ConjuntoPersonas* UndavConjuntoPersonas::Crear(){
    ConjuntoPersonas* conjunto = new ConjuntoPersonas;
    conjunto->personas = CrearListaPersonasVacia();
    conjunto->cantidadPersonas = 0;
    return conjunto;
}

void UndavConjuntoPersonas::Agregar(ConjuntoPersonas* conjunto, Persona* persona){

    if(!Contiene(conjunto,persona))
    {
        AgregarAlFinal(conjunto->personas,persona);
        conjunto->cantidadPersonas++;
    }
}

void UndavConjuntoPersonas::Quitar(ConjuntoPersonas* conjunto, Persona* persona){

    if(conjunto->personas->primero != NULL){
        Persona* primeraDeLista = conjunto->personas->primero->item;
        Persona* ultimaDelista = conjunto->personas->ultimo->item;
        if(Contiene(conjunto,persona)){
            if(SonIguales(primeraDeLista,persona))
                EliminarPrimerNodo(conjunto->personas);
            else if(SonIguales(ultimaDelista,persona))
                EliminarUltimoNodo(conjunto->personas);
            else
                EliminarNodoPosicion(conjunto->personas,persona);
            conjunto->cantidadPersonas--;
        }
    }
}

bool UndavConjuntoPersonas::Contiene(const ConjuntoPersonas* conjunto, const Persona* persona){

    bool contiene = false;
    for(NodoPersona* iterador = conjunto->personas->primero;iterador!= NULL && !contiene; iterador = iterador->siguiente)
        contiene = SonIguales(iterador->item,persona);
    return contiene;
}

int UndavConjuntoPersonas::CantidadPersonas(const ConjuntoPersonas* conjunto){

    return conjunto->cantidadPersonas;
}

UndavPersona::Persona** UndavConjuntoPersonas::ConvertirAVector(ConjuntoPersonas* conjunto){

    Persona** vectorPersonas = NULL;

    if(!EstaVacia(conjunto->personas)){
        vectorPersonas= new Persona*[conjunto->cantidadPersonas];
        NodoPersona* iterador = conjunto->personas->primero;
        for(int i = 0;iterador != NULL;i++){
            vectorPersonas[i]=iterador->item;
            iterador = iterador->siguiente;
        }
    }
    return vectorPersonas;
}

void UndavConjuntoPersonas::Destruir(ConjuntoPersonas* conjunto){

    NodoPersona* iterador = conjunto->personas->primero;
    while(iterador!=NULL){
        NodoPersona* auxiliar = iterador;
        iterador = iterador->siguiente;
        delete auxiliar;
    }
    delete conjunto;
}

NodoPersona* CrearUltimoNodoPersonas(Persona* item){
	return CrearNodo(item, NULL);
}

NodoPersona* CrearNodo(Persona* item,NodoPersona* siguiente){

    NodoPersona* nodo = new NodoPersona;
    nodo->item = item;
    nodo->siguiente = siguiente;
    return nodo;
}

ListaPersonas* CrearListaPersonasVacia(){
	ListaPersonas* lista = new ListaPersonas;
	lista->primero = lista->ultimo = NULL;
	return lista;
}

bool EstaVacia(ListaPersonas* lista){
	return lista->primero ==NULL;
}

void AgregarAlFinal(ListaPersonas* lista,Persona* item){

	NodoPersona* nuevoUltimoNodo = CrearUltimoNodoPersonas(item);
	if (EstaVacia(lista)) {
		lista->primero = lista->ultimo = nuevoUltimoNodo;
	}else{
		NodoPersona* ultimoActual = lista->ultimo;
		ultimoActual->siguiente = nuevoUltimoNodo;
		lista->ultimo = nuevoUltimoNodo;
	}
}

void EliminarPrimerNodo(ListaPersonas* lista){

    NodoPersona* primerNodo = lista->primero;
    lista->primero = primerNodo->siguiente;
    if(primerNodo == lista->ultimo){
        lista->ultimo =lista->primero = NULL;
    }

    delete primerNodo;
}

void EliminarUltimoNodo(ListaPersonas* lista){

    NodoPersona* aEliminar = lista->ultimo;
    NodoPersona* anterior = ObtenerNodoAnterior(lista,lista->ultimo->item);
    lista->ultimo = anterior;
    anterior->siguiente = NULL;
    delete aEliminar;
}

void EliminarNodoPosicion(ListaPersonas* lista,Persona* persona){

    NodoPersona* NodoAnterior = ObtenerNodoAnterior(lista,persona);
    NodoPersona* aEliminar= NodoAnterior->siguiente;
    NodoAnterior ->siguiente = aEliminar->siguiente;
    delete aEliminar;
    }

NodoPersona* ObtenerNodoAnterior(ListaPersonas* lista,Persona* persona){

    NodoPersona* iterador = lista->primero;
    NodoPersona* anterior = NULL;

    while(iterador!=NULL){
        if(SonIguales(iterador->item,persona))
            break;
        anterior = iterador;
        iterador = iterador->siguiente;
    }
    return anterior;
}

struct UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::IteradorConjuntoPersonas{
    NodoPersona* nodoActual;
};

IteradorConjuntoPersonas* UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Comienzo(ConjuntoPersonas* conjunto){
   IteradorConjuntoPersonas* iterador = new IteradorConjuntoPersonas;
   iterador->nodoActual = conjunto->personas->primero;
   return iterador;
}

bool UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::EsFin(const IteradorConjuntoPersonas* iterador){
    return iterador->nodoActual == NULL;
}

Persona* UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::ObtenerItem(IteradorConjuntoPersonas* iterador){
    if(iterador->nodoActual != NULL)
        return iterador->nodoActual->item;
    return NULL;
}

void UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Siguiente(IteradorConjuntoPersonas* iterador){

    if(iterador->nodoActual != NULL)
        iterador->nodoActual = iterador->nodoActual->siguiente;
}

void UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Destruir(IteradorConjuntoPersonas* iterador){

    delete iterador;
}
