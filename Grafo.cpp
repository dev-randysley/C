#include "Grafo.h"
#include "ConjuntoPersonas.h"
#include <iostream>
#include <string>

using std::string;
using std::to_string;
using namespace std;
using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::IteradorConjuntoPersonas;

using UndavGrafoPersonas::UndavIteradorAdyacencias::IteradorAdyacencias;
using UndavGrafoPersonas::GrafoPersonas;
using UndavPersona::Persona;

string ObtenerFormato(GrafoPersonas* grafo,TipoFormatoGrafo formato);
string ObtenerFormatoMatriz(GrafoPersonas* grafo);
string ObtenerFormatoCorto(GrafoPersonas*  grafo);
string ObtenerFormatoLargo(GrafoPersonas* grafo);
string ConvertirAString(int* elementos,int cantidad);

struct NodoVertice{
	Persona* vertice;
	ConjuntoPersonas* adyacencias;
	NodoVertice* siguiente;
};
struct ListaVertices{
	NodoVertice* primero;
	NodoVertice* ultimo;
};

struct UndavGrafoPersonas::GrafoPersonas {
    ListaVertices* vertices;
    int cantidadPersonas;
    int cantidadAdyacencias;
};

//Auxiliar grafo
bool EstaEnGrafo(GrafoPersonas* grafo,Persona* vertice);
NodoVertice* ObtenerVertice(const GrafoPersonas* grafo,Persona* persona);
void AgregarVertices(ListaVertices* vertices,ConjuntoPersonas* personas);
void AgregarVertice(ListaVertices* vertices,Persona* persona);
NodoVertice* CrearUltimoNodoVertice(Persona* item);
bool Esfin(NodoVertice* nodo);
ListaVertices* CrearListaVacia();
void DestruirVerticesAdyacencias(GrafoPersonas* grafo);
void InicializarVector(int* elementos,int cantidad);


GrafoPersonas* UndavGrafoPersonas::CrearGrafo(ConjuntoPersonas* vertices){

    GrafoPersonas* grafo = new GrafoPersonas;
    grafo->cantidadPersonas = CantidadPersonas(vertices);
    grafo->vertices = CrearListaVacia();
    grafo->cantidadAdyacencias = 0;
    AgregarVertices(grafo->vertices,vertices);
    return grafo;
}

ListaVertices* CrearListaVacia(){

    ListaVertices* nueva = new ListaVertices;
    nueva->primero = nueva->ultimo = NULL;
    return nueva;
}

void AgregarVertices(ListaVertices* vertices,ConjuntoPersonas* personas){

    IteradorConjuntoPersonas* iterador = UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Comienzo(personas);

    while(!UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::EsFin(iterador)){
        AgregarVertice(vertices, UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::ObtenerItem(iterador));
        UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Siguiente(iterador);
    }

    UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Destruir(iterador);
}

void AgregarVertice(ListaVertices* vertices,Persona* persona){

    NodoVertice* nuevoUltimoVertice = CrearUltimoNodoVertice(persona);

	if (vertices->primero == NULL) {
		vertices->primero = vertices->ultimo = nuevoUltimoVertice;
	}else{
		NodoVertice* ultimoActual = vertices->ultimo;
		ultimoActual->siguiente = nuevoUltimoVertice;
		vertices->ultimo = nuevoUltimoVertice;
	}
}

string UndavGrafoPersonas::Serializar(GrafoPersonas* grafo, TipoFormatoGrafo formato){

    string serializado ="";

    if(formato == TipoFormatoGrafo::Corto || formato  == TipoFormatoGrafo::Largo)
        serializado += ObtenerFormato(grafo,formato);
    else
        serializado += ObtenerFormatoMatriz(grafo);

    return serializado;
}

string ObtenerFormato(GrafoPersonas* grafo,TipoFormatoGrafo formato){

    string serializado ="";
    serializado +="Cantidad Vertices: " +to_string(grafo->cantidadPersonas) +"\nCantidad Adyacencias: "+ to_string(grafo->cantidadAdyacencias)+ "\n";
    if(formato == TipoFormatoGrafo::Corto){
        serializado += ObtenerFormatoCorto(grafo);
    }
    else{
        serializado += ObtenerFormatoLargo(grafo);
    }
    return serializado;
}

string ObtenerFormatoLargo(GrafoPersonas* grafo){

    string serializado ="";

    NodoVertice* iteradorVertice = grafo->vertices->primero;
    NodoVertice* iteradorVerticeSiguiente ;
    if(iteradorVertice!= NULL)
        iteradorVerticeSiguiente = iteradorVertice->siguiente;
    while(iteradorVertice != NULL ){
        while(iteradorVerticeSiguiente != NULL){
            if(SonAdyacentes(grafo,iteradorVertice->vertice,iteradorVerticeSiguiente->vertice)){
                serializado += Serializar(iteradorVertice->vertice,TipoFormato::Expresivo) +" "+ Serializar(iteradorVerticeSiguiente->vertice,TipoFormato::Expresivo) +"\n";
            }
            iteradorVerticeSiguiente = iteradorVerticeSiguiente->siguiente;
        }
        iteradorVertice = iteradorVertice->siguiente;
        if(iteradorVertice != NULL){
            iteradorVerticeSiguiente = iteradorVertice->siguiente;
        }

    }
    return serializado;
}

string ObtenerFormatoCorto(GrafoPersonas*  grafo){

    string serializado ="";


    NodoVertice* iteradorVertice = grafo->vertices->primero;
    NodoVertice* iteradorVerticeSiguiente ;
    if(iteradorVertice!= NULL)
        iteradorVerticeSiguiente = iteradorVertice->siguiente;
    while(iteradorVertice != NULL ){
        while(iteradorVerticeSiguiente != NULL){
            if(SonAdyacentes(grafo,iteradorVertice->vertice,iteradorVerticeSiguiente->vertice)){
                serializado += Serializar(iteradorVertice->vertice,TipoFormato::Identificador) +" "+ Serializar(iteradorVerticeSiguiente->vertice,TipoFormato::Identificador) +"\n";
            }
            iteradorVerticeSiguiente = iteradorVerticeSiguiente->siguiente;
        }
        iteradorVertice = iteradorVertice->siguiente;
        if(iteradorVertice != NULL){
            iteradorVerticeSiguiente = iteradorVertice->siguiente;
        }

    }
    return serializado;
}

string ObtenerFormatoMatriz(GrafoPersonas* grafo){

    string serializado ="";
    int elementos[grafo->cantidadPersonas];
    InicializarVector(elementos,grafo->cantidadPersonas);

    NodoVertice* iteradorVerticeOrigen = grafo->vertices->primero;
    UndavGrafoPersonas::UndavIteradorAdyacencias::IteradorAdyacencias* iteradorVerticeDestino = UndavGrafoPersonas::UndavIteradorAdyacencias::Comienzo(grafo,iteradorVerticeOrigen->vertice);

    while(iteradorVerticeOrigen != NULL){
        while(!UndavGrafoPersonas::UndavIteradorAdyacencias::EsFin(iteradorVerticeDestino)){
            elementos[ObtenerId(UndavGrafoPersonas::UndavIteradorAdyacencias::ObtenerItem(iteradorVerticeDestino))]= true;
            UndavGrafoPersonas::UndavIteradorAdyacencias::Siguiente(iteradorVerticeDestino);
        }
        iteradorVerticeOrigen = iteradorVerticeOrigen->siguiente;
        if(iteradorVerticeOrigen != NULL)
            iteradorVerticeDestino = UndavGrafoPersonas::UndavIteradorAdyacencias::Comienzo(grafo,iteradorVerticeOrigen->vertice);
        serializado += ConvertirAString(elementos,grafo->cantidadPersonas);
        InicializarVector(elementos,grafo->cantidadPersonas);
    }

    return serializado;
}

void InicializarVector(int* elementos,int cantidad){

    for(int i = 0; i < cantidad; i++)
        elementos[i]= 0;

}

string ConvertirAString(int* elementos,int cantidad){

    string convertido ="";

    for(int i = 0; i < cantidad -1;i++)
        convertido += to_string(elementos[i]) + " , ";
    convertido +=to_string(elementos[cantidad -1]) +"\n";

    return convertido;
}
NodoVertice* CrearUltimoNodoVertice(Persona* item){

    NodoVertice* nodo = new NodoVertice;
    nodo->siguiente = NULL;
    nodo->vertice = item;
    nodo->adyacencias = UndavConjuntoPersonas::Crear();
    return nodo;
}

void UndavGrafoPersonas::Conectar(GrafoPersonas* grafo, Persona* verticeOrigen, Persona* verticeDestino){

    NodoVertice* nodoOrigen = ObtenerVertice(grafo,verticeOrigen);
    NodoVertice* nodoDestino = ObtenerVertice(grafo,verticeDestino);
    if(nodoOrigen != NULL && nodoDestino!= NULL){
        UndavConjuntoPersonas::Agregar(nodoOrigen->adyacencias,verticeDestino);
        UndavConjuntoPersonas::Agregar(nodoDestino->adyacencias,verticeOrigen);
        grafo->cantidadAdyacencias++;

    }
    AgregarAmigo(verticeOrigen,verticeDestino);
    AgregarAmigo(verticeDestino,verticeOrigen);
}

bool UndavGrafoPersonas::SonAdyacentes(const GrafoPersonas* grafo, Persona* verticeOrigen, Persona* verticeDestino){
    NodoVertice* personaOrigen = ObtenerVertice(grafo,verticeOrigen);
    return personaOrigen == NULL ? false : UndavConjuntoPersonas::Contiene(personaOrigen->adyacencias,verticeDestino);
}

int UndavGrafoPersonas::ObtenerGrado(GrafoPersonas* grafo,Persona* vertice){

    int grado = 0;
    NodoVertice* nodo= ObtenerVertice(grafo,vertice);
    if(nodo != NULL){
        grado = UndavConjuntoPersonas::CantidadPersonas(nodo->adyacencias);
    }
    return grado;
}

void UndavGrafoPersonas::Destruir(GrafoPersonas* grafo){

    DestruirVerticesAdyacencias(grafo);
    delete grafo;
}

void DestruirVerticesAdyacencias(GrafoPersonas* grafo){

    NodoVertice* iterador = grafo->vertices->primero;
    NodoVertice* auxiliar;
    while(iterador != NULL){
        Destruir(iterador->adyacencias);
        auxiliar = iterador;
        iterador = iterador->siguiente;
        delete auxiliar;
    }
}

bool EstaEnGrafo(GrafoPersonas* grafo,Persona* vertice){

    return ObtenerVertice(grafo,vertice) != NULL;

}

NodoVertice* ObtenerVertice(const GrafoPersonas* grafo,Persona* persona){

    NodoVertice* iterador = grafo->vertices->primero;

    while(iterador != NULL){
        if(SonIguales(iterador->vertice,persona))
            return iterador;
        iterador = iterador->siguiente;
    }

    return NULL;
}

struct UndavGrafoPersonas::UndavIteradorAdyacencias::IteradorAdyacencias{
    UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::IteradorConjuntoPersonas* nodoActual;
};

IteradorAdyacencias* UndavGrafoPersonas::UndavIteradorAdyacencias::Comienzo(GrafoPersonas* grafo, Persona* verticeOrigen){

    IteradorAdyacencias* iterador = new IteradorAdyacencias;
    NodoVertice* nodo = ObtenerVertice(grafo,verticeOrigen);
    iterador->nodoActual = UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Comienzo(nodo->adyacencias);
    return iterador;
}

bool UndavGrafoPersonas::UndavIteradorAdyacencias::EsFin(const IteradorAdyacencias* iterador){

    return UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::EsFin(iterador->nodoActual);
}

Persona* UndavGrafoPersonas::UndavIteradorAdyacencias::ObtenerItem(IteradorAdyacencias* iterador){

    return UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::ObtenerItem(iterador->nodoActual);
}

void UndavGrafoPersonas::UndavIteradorAdyacencias::Siguiente(IteradorAdyacencias* iterador){

    UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Siguiente(iterador->nodoActual);
}

void UndavGrafoPersonas::UndavIteradorAdyacencias::Destruir(IteradorAdyacencias* iterador){

    UndavConjuntoPersonas::UndavIteradorConjuntoPersonas::Destruir(iterador->nodoActual);
    delete iterador;
}


