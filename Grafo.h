#ifndef GRAFO_H_
#define GRAFO_H_

#include <string>
#include "Persona.h"
#include "ConjuntoPersonas.h"
#include "TipoFormato.h"
using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavPersona::Persona;
using std::string;

namespace UndavGrafoPersonas{
	struct GrafoPersonas;
	/*
	 * Precondicion: @cantdidadPersonas es mayor a cero
	 * Postcondicion: Devuelve un grafo dirigido de cantidad de vertices igual a @cantidadPersonas
	 */
	GrafoPersonas* CrearGrafo(ConjuntoPersonas* vertices);

	/*
	 * Precondicion: @grafo es una instancia valida
	 * Postcondicion: Se agrega una relacion de adyacencia conmutativa entre @verticeOrigen y @verticeDestino (@verticeOrigen es adyacente a @verticeDestino y viceversa).
	 * Si @verticeOrigen o @verticeDestino no pertenece al grafo no realiza ninguna accion
	 */
	void Conectar(GrafoPersonas* grafo, Persona* verticeOrigen, Persona* verticeDestino);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve true si @verticeOrigen es adyacente a @verticeDestino. Caso contrario devuelve false
	 */
	bool SonAdyacentes(const GrafoPersonas* grafo, Persona* verticeOrigen, Persona* verticeDestino);

	/*
	 * Precondicion: @grafo y @persona son instancias validas. @vertice es un vertice del grafo
	 * Postcondicion: Devuelve el grado de @vertice (cantidad de vertices adyacentes a @vertice)
	 */
	int ObtenerGrado(GrafoPersonas* grafo, Persona* vertice);


    /*
	 * Precondicion: @grafo es una instancia valida
	 * Postcondicion:
	 * Si @formato es Corto o Largo entonces obtiene la representacion del grafo en el siguiente formato
	 * - En la primer linea (primer registro) la cantidad de vertices (cardinalidad del conjunto V)
	 * - En la segunda linea (segundo registro) la cantidad de adyacencias (cardinalidad del conjunto V)
	 * - En las siguientes lineas el conjunto de adyacencias segun el siguiente
	 *  s v
	 *  donde s es el vertice origen y v el vertice destino. Estan separados por espacio y cada adyacencia esta en una nueva linea
	 *  El formato que se utiliza para mostrar el vertice es
	 *  - Corto significa que hay utilizar el formato Identificador en el Serializar de Persona
	 *  - Largo significa que hay que utlizar el formato Expresivo en el Serializar de Persona
	 *
	 *  Si @formato es MatrizAdyacencia devuelve un string que es una matriz cuadrada (de ceros y uno, separadas por coma y cada fila separada por una nueva linea)
	 *  que representa la matriz de adyacencia del grafo. La diagonal principal de esta matriz deberia ser cero, ya que una persona no es amiga de uno mismo
	 */
	string Serializar(GrafoPersonas* grafo, TipoFormatoGrafo formato);

	namespace UndavIteradorAdyacencias{
		struct IteradorAdyacencias;
		IteradorAdyacencias* Comienzo(GrafoPersonas* grafo, Persona* verticeOrigen);
		bool EsFin(const IteradorAdyacencias* iterador);
		Persona* ObtenerItem(IteradorAdyacencias* iterador);
		void Siguiente(IteradorAdyacencias* iterador);
		void Destruir(IteradorAdyacencias* iterador);
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @grafo
	 */
	void Destruir(GrafoPersonas* grafo);
}

#endif
