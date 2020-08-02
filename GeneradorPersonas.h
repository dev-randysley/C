#ifndef GENERADORPERSONAS_H_
#define GENERADORPERSONAS_H_

#include "ConjuntoPersonas.h"
#include "Persona.h"

using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavPersona::Persona;

namespace UndavGeneradorPersonas{
	struct GeneradorPersonas;

	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve una instancia unica de ConjuntoPersonas.
	 */
	GeneradorPersonas* Crear();

	/*
	 * Precondicion: @generador es una instancia valida
	 * Postcondicion: Devuelve un conjunto de personas random, de cantiad de personas igual a @cantidad
	 */
	ConjuntoPersonas* GenerarPersonasRandom(GeneradorPersonas* generador, int cantidad);

	/*
	 * Precondicion: @generador es una instancia valida
	 * Postcondicion: Crea y devuelve una nueva instancia valida de persona que es aleatoria (nombre y apellido random) La persona creada no tiene amigos
	 */
	Persona* GenerarPersonaRandom(GeneradorPersonas* generador);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @grafo
	 */
	void Destruir(GeneradorPersonas* generador);
}

#endif
