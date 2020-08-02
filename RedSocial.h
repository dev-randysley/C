#ifndef REDSOCIAL_H_
#define REDSOCIAL_H_

#include "ConjuntoPersonas.h"
#include "Persona.h"
#include "Grafo.h"

using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavGrafoPersonas::GrafoPersonas;
using UndavPersona::Persona;

namespace UndavRedSocial{
	struct RedSocial;

	/*
	 * Precondicion: @personas es una instancia valida de ConjuntoPersonas
	 * Postcondicion: Devuelve una instancia valida de RedSocial que contiene a @personas como unicos miembros
	 */
	RedSocial* CrearRedSocial(ConjuntoPersonas* personas);

	/*
	 * Precondicion: @redSocial, @persona y @otraPersona son instancias validas
	 * Postcondicion: @persona es amiga de @otraPersona (y @otraPersona es amiga de @persona)
	 */
	void Conectar(RedSocial* redSocial,Persona* persona,Persona* otraPersona);

	/*
	 * Precondicion: @redSocial es una instancia valida
	 * Postcondicion: Obtiene un grafo no dirigido donde:
	 * - Los vertices son las personas que pertencen a @redSocial
	 * - Las aristas representa representa la relacion: son amigos
	 */
	GrafoPersonas* ObtenerRed(RedSocial* redSocial);

	/*
	 * Precondicion: @redSocial es una instancia valida
	 * Postcondicion: Obtiene uno de los posibles boques de expansion de @redSocial
	 */
	GrafoPersonas* ObtenerBosqueExpansion(RedSocial* redSocial);

	/*
	 * Precondiciones: @redSocial es una instancia valida
	 * Postcondiciones: Libera todos los recursos asociados a @redSocial
	 */
	void Destruir(RedSocial* redSocial);
}

#endif
