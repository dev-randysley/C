#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GeneradorPersonas.h"
#include "RedSocial.h"
#include "TipoFormato.h"
#include "Persona.h"
#include <cstring>

using namespace std;
using namespace UndavGeneradorPersonas;
using namespace UndavRedSocial;
using namespace UndavGrafoPersonas;

enum TipoMostrar{Red, RedYBosque, Bosque};
RedSocial* CrearRedSocial(int cantidadVertices,int CantidadAristas);
void RealizarConexiones(RedSocial* redSocial, ConjuntoPersonas* personas,int cantidadConexiones,int cantidadAristas,int cantidadVertices);

//auxiliares
void MostrarAyuda();
int ConvertirEntero(char* cadena);
TipoFormatoGrafo ObtenerFormato(char* formato);
void MostrarFormato(RedSocial* redSocial,TipoFormatoGrafo formato,TipoMostrar formatoMostrar);
TipoMostrar ObtenerFormatoMostrar(char* formato);
void MostrarAmbos(RedSocial* redSocial,TipoFormatoGrafo formato);
void MostrarRed(GrafoPersonas* grafo,TipoFormatoGrafo formato);

int main(int argc,char **argv) {
    if(argc !=5 ){
        MostrarAyuda();
    }
    else{
        int cantidadVertices = ConvertirEntero(argv[1]);
        int cantidadAristas =ConvertirEntero(argv[2]);
        TipoFormatoGrafo formato = ObtenerFormato(argv[3]);
        TipoMostrar formatoAMostrar = ObtenerFormatoMostrar(argv[4]);
        RedSocial* redSocial = CrearRedSocial(cantidadVertices,cantidadAristas);
        MostrarFormato(redSocial,formato,formatoAMostrar);
	}
	return 0;
}

int ConvertirEntero(char* cadena){
    return atoi(cadena);
}

TipoFormatoGrafo ObtenerFormato(char* formato){
    if(strcmp(formato,"Corto")==0)
        return TipoFormatoGrafo::Corto;
    else if(strcmp(formato,"Largo")== 0)
        return TipoFormatoGrafo::Largo;
    else
        return TipoFormatoGrafo::MatrizAdyacencia;
}

TipoMostrar ObtenerFormatoMostrar(char* formato){
    if(strcmp(formato,"Red")==0)
        return TipoMostrar::Red;
    else if(strcmp(formato,"Bosque")==0)
        return TipoMostrar::Bosque;
    else
        return TipoMostrar::RedYBosque;
}

void MostrarAyuda(){
    cout<< "Para uso ingrese en el siguiente orden \n[CantidadVertices] [CantidadAristas] [FormatoSerializado] [FormatoAMostrar]"<<endl;
    cout<<"FormatoSerializado: indica el formato para mostrar el grafo, las opciones son: "<<endl;
    cout<<"\t Corto"<<endl;
    cout<<"\t Largo"<<endl;
    cout<<"\t Matriz"<<endl;
    cout<<"FormatoAMostrar: indica si se quiere visualizar el grafo, bosque o ambas, las opciones son: "<<endl;
    cout<<"\t Red"<<endl;
    cout<<"\t Bosque"<<endl;
    cout<<"\t RedYBosque"<<endl;
}

void MostrarFormato(RedSocial* redSocial,TipoFormatoGrafo formato,TipoMostrar formatoMostrar){

    if(formatoMostrar == TipoMostrar::Red){
        cout<<"Red Social: "<<endl;
        MostrarRed(ObtenerRed(redSocial),formato);
    }
    else if (formatoMostrar == TipoMostrar::Bosque){
        cout<<"Bosque expansion de la red social: "<<endl;
        MostrarRed(ObtenerBosqueExpansion(redSocial),formato);
    }
    else
        MostrarAmbos(redSocial,formato);
}

void MostrarRed(GrafoPersonas* grafo,TipoFormatoGrafo formato){
    cout<<endl;
    if(formato == TipoFormatoGrafo::Largo){
        cout<<Serializar(grafo,formato)<<endl;
    }
    else if(formato == TipoFormatoGrafo::Corto){
        cout<<Serializar(grafo,formato)<<endl;
    }
    else{
        cout<<Serializar(grafo,formato)<<endl;
    }
}

void MostrarAmbos(RedSocial* redSocial,TipoFormatoGrafo formato){
    cout<<"Red Social: "<<endl;
    MostrarRed(ObtenerRed(redSocial),formato);
    cout<<endl;
    cout<<"Bosque expansion de la red social: "<<endl;
    MostrarRed(ObtenerBosqueExpansion(redSocial),formato);
}

RedSocial* CrearRedSocial(int cantidadVertices,int cantidadAristas){
	GeneradorPersonas* generador = Crear();
	ConjuntoPersonas* personas = GenerarPersonasRandom(generador, cantidadVertices);
	RedSocial* redSocial = CrearRedSocial(personas);
	RealizarConexiones(redSocial, personas,cantidadAristas,cantidadAristas,cantidadVertices);
	Destruir(generador);
	Destruir(personas);
	return redSocial;
}
void RealizarConexiones(RedSocial* redSocial, ConjuntoPersonas* conjunto,int cantidadConexiones,int cantidadAristas,int cantidadVertices){
	Persona** personas = UndavConjuntoPersonas::ConvertirAVector(conjunto);
	for(int conexionesRealizadas = 0; conexionesRealizadas < cantidadAristas; ){
		Persona* unaPersona = personas[rand()%cantidadVertices];
		Persona* otraPersona = personas[rand()%cantidadVertices];
		if(unaPersona != otraPersona && !UndavPersona::SonAmigos(unaPersona, otraPersona)){
			Conectar(redSocial, unaPersona, otraPersona);
			conexionesRealizadas++;
		}
	}
	delete []personas;
}
