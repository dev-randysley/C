#include "GeneradorPersonas.h"
#include "Persona.h"
#include "ConjuntoPersonas.h"
#include<stdlib.h>
#include<time.h>

using UndavConjuntoPersonas::ConjuntoPersonas;
using UndavPersona::Persona;

using UndavGeneradorPersonas::GeneradorPersonas;

const string nombres[]={"randy","belen","jony","mario","astrid","maria","pedro","jose","juan","ignacio","javier","enrique","jean","fushimi","pablo","ramon","fede","alberto","enzo","bernardo"};
const string apellidos[]={"mendoza","velasquez","rodriguez","aponte","medina","aroca","rodriguez","chacon","zambrano","mamani","gonzales","pozo","perales","martinez","lopez","flores","hernandez","fernandez","castro","contreras"};
const int cantidadPersonas = 20;

struct UndavGeneradorPersonas::GeneradorPersonas{
};

GeneradorPersonas* UndavGeneradorPersonas::Crear(){

    GeneradorPersonas* generador = new GeneradorPersonas;
    srand(time(NULL));
    return generador;
}

ConjuntoPersonas* UndavGeneradorPersonas::GenerarPersonasRandom(GeneradorPersonas* generador, int cantidad){

    ConjuntoPersonas* personas = UndavConjuntoPersonas::Crear();
    for(int i= 0; i < cantidad;i++)
        UndavConjuntoPersonas::Agregar(personas,GenerarPersonaRandom(generador));
    return personas;
}

Persona* UndavGeneradorPersonas::GenerarPersonaRandom(GeneradorPersonas* generador){

    Persona* random = UndavPersona::CrearPersona(nombres[rand()%(cantidadPersonas)],apellidos[rand()%(cantidadPersonas)]);
    return random;
}

void UndavGeneradorPersonas::Destruir(GeneradorPersonas* generador){

    delete generador;
}
